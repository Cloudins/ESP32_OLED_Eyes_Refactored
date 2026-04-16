#include "Face.h"
#include "EyeDrawer.h"

Face::Face(uint16_t screenWidth, uint16_t screenHeight, uint16_t eyeSize) 
	: LeftEye(*this), RightEye(*this), Blink(*this), Look(*this), Behavior(*this), Expression(*this) {
	Width = screenWidth;
	Height = screenHeight;
	EyeSize = eyeSize;
	CenterX = Width / 2;
	CenterY = Height / 2;
	LeftEye.IsMirrored = true;
    Behavior.Clear();
	Behavior.Timer.Start();
}

void Face::LookFront() { Look.LookAt(0.0, 0.0); }
void Face::LookRight() { Look.LookAt(-1.0, 0.0); }
void Face::LookLeft() { Look.LookAt(1.0, 0.0); }
void Face::LookTop() { Look.LookAt(0.0, 1.0); }
void Face::LookBottom() { Look.LookAt(0.0, -1.0); }

void Face::Wait(unsigned long milliseconds) {
	unsigned long start = millis();
	while (millis() - start < milliseconds) {
		Draw();
	}
}

void Face::DoBlink() { Blink.Blink(); }

void Face::Update() {
	if(RandomBehavior) Behavior.Update();
	if(RandomLook) Look.Update();
	if(RandomBlink)	Blink.Update();
	Draw();
}

void Face::Draw() {
    u8g2.clearBuffer();
    u8g2.setDrawColor(1);

    LeftEye.CenterX = CenterX - EyeSize / 2 - EyeInterDistance;
    LeftEye.CenterY = CenterY;
    LeftEye.Draw();

    RightEye.CenterX = CenterX + EyeSize / 2 + EyeInterDistance;
    RightEye.CenterY = CenterY;
    RightEye.Draw();

    u8g2.sendBuffer();
}