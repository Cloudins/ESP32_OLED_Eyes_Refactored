#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Face.h"

// 1. 硬件与全局对象定义
// 使用 SSD1306 驱动，SDA=21, SCL=22
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

Face* gFace = nullptr;
WebServer server(80);
uint32_t lastFrameMs = 0;
const uint16_t EYES_FRAME_MS = 33; // 约 30 FPS

// 2. 辅助函数：解析表情名称或索引 [cite: 256-262]
static bool parseEmotion(const String& s, eEmotions &out) {
    String t = s; t.trim();
    if (t.length() == 0) return false;
    
    // 如果输入是数字索引
    bool isNum = true;
    for (size_t i = 0; i < t.length(); i++) {
        if (!isDigit(t[i])) { isNum = false; break; }
    }
    if (isNum) {
        int v = t.toInt();
        if (v >= 0 && v < (int)eEmotions::EMOTIONS_COUNT) {
            out = (eEmotions)v;
            return true;
        }
        return false;
    }

    // 如果输入是字符串名称
    t.toLowerCase();
    struct Pair { const char* name; eEmotions e; };
    static const Pair map[] = {
        {"normal", eEmotions::Normal}, {"angry", eEmotions::Angry}, {"glee", eEmotions::Glee},
        {"happy", eEmotions::Happy}, {"sad", eEmotions::Sad}, {"worried", eEmotions::Worried},
        {"focused", eEmotions::Focused}, {"annoyed", eEmotions::Annoyed}, {"surprised", eEmotions::Surprised},
        {"skeptic", eEmotions::Skeptic}, {"frustrated", eEmotions::Frustrated}, {"unimpressed", eEmotions::Unimpressed},
        {"sleepy", eEmotions::Sleepy}, {"suspicious", eEmotions::Suspicious}, {"squint", eEmotions::Squint},
        {"furious", eEmotions::Furious}, {"scared", eEmotions::Scared}, {"awe", eEmotions::Awe},
        {"confused", eEmotions::Confused} // 你新增的表情
    };
    for (auto &p : map) {
        if (t == p.name) { out = p.e; return true; }
    }
    return false;
}

// 3. 网页 HTML 源码 [cite: 262-269]
static const char INDEX_HTML[] PROGMEM = R"HTML(
<!doctype html><html><head><meta charset="utf-8"/><meta name="viewport" content="width=device-width,initial-scale=1"/>
<title>ESP32 Eyes Control</title>
<style>
  body{font-family:system-ui; margin:16px; max-width:600px; background:#f4f4f9}
  .grid{display:grid; grid-template-columns:repeat(3,1fr); gap:10px}
  button{padding:12px; border:1px solid #ccc; border-radius:8px; background:#fff; cursor:pointer}
  button:active{background:#eee; transform:scale(0.98)}
  .card{background:#fff; border-radius:12px; padding:16px; margin-bottom:16px; box-shadow:0 2px 5px rgba(0,0,0,0.1)}
  h3{margin-top:0}
</style></head>
<body>
  <h2>ESP32 交互表情控制台</h2>
  <div class="card">
    <h3>情绪选择</h3>
    <div id="emoGrid" class="grid"></div>
  </div>
  <div class="card">
    <h3>动作控制</h3>
    <button onclick="q('/api?blink=1')">手动眨眼</button>
    <button onclick="q('/api?auto=1')">开启随机行为</button>
    <button onclick="q('/api?auto=0')">停止随机行为</button>
  </div>
<script>
  const EMOS = ["Normal","Angry","Glee","Happy","Sad","Worried","Focused","Annoyed","Surprised","Skeptic","Frustrated","Unimpressed","Sleepy","Suspicious","Squint","Furious","Scared","Awe","Confused"];
  const grid = document.getElementById('emoGrid');
  EMOS.forEach(e => {
    const b = document.createElement('button');
    b.textContent = e;
    b.onclick = () => q('/api?emo=' + e.toLowerCase());
    grid.appendChild(b);
  });
  function q(url){ fetch(url).then(r => r.json()).then(j => console.log(j)); }
</script></body></html>
)HTML";

// 4. API 逻辑处理 [cite: 269-278]
static String statusJson() {
    if (!gFace) return "{}";
    String s = "{\"ok\":true";
    s += ",\"emotion\":" + String((int)gFace->Behavior.CurrentEmotion);
    s += ",\"auto\":" + String(gFace->RandomBehavior ? "true":"false");
    s += "}";
    return s;
}

static void handleApi() {
    if (!gFace) { server.send(500, "text/plain", "Face not ready"); return; }

    if (server.hasArg("auto")) {
        bool on = server.arg("auto").toInt() != 0;
        gFace->RandomBehavior = gFace->RandomLook = gFace->RandomBlink = on;
    }
    if (server.hasArg("blink")) { gFace->DoBlink(); }
    if (server.hasArg("emo")) {
        eEmotions e;
        if (parseEmotion(server.arg("emo"), e)) {
            gFace->RandomBehavior = false; // 切换到手动模式
            gFace->Behavior.GoToEmotion(e);
        }
    }
    if (server.hasArg("lookx") || server.hasArg("looky")) {
        float x = server.arg("lookx").toFloat();
        float y = server.arg("looky").toFloat();
        gFace->RandomLook = false;
        gFace->Look.LookAt(x, y);
    }
    server.send(200, "application/json", statusJson());
}

// 5. WiFi AP 模式启动 [cite: 279-280]
void wifiStartAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32-EYES", "12345678");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
}

// 6. 标准入口 [cite: 281-285]
void setup() {
    Serial.begin(115200);
    delay(500);

    // I2C 与 OLED 初始化
    Wire.begin(21, 22);
    u8g2.begin();
    u8g2.setBusClock(400000);

    // 创建脸部对象 (128x64 屏幕, 眼睛大小 40)
    gFace = new Face(128, 64, 40);
    gFace->Behavior.GoToEmotion(eEmotions::Normal);

    // 启动服务器
    wifiStartAP();
    server.on("/", []() { server.send_P(200, "text/html", INDEX_HTML); });
    server.on("/api", handleApi);
    server.begin();
    
    Serial.println("系统就绪，访问 http://192.168.4.1/");
}

void loop() {
    server.handleClient();

    uint32_t now = millis();
    // 限制刷新频率，保证动画平滑 [cite: 285]
    if (gFace && (uint32_t)(now - lastFrameMs) >= EYES_FRAME_MS) {
        gFace->Update();
        lastFrameMs = now;
    }
}