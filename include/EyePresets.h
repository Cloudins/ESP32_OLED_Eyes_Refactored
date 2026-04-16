#ifndef _EYEPRESETS_h
#define _EYEPRESETS_h

#include <Arduino.h>
#include "EyeConfig.h"

// 声明原作者所有的表情参数组合（注意有些表情左右眼不对称，带 _Alt 后缀）
extern const EyeConfig Preset_Normal;
extern const EyeConfig Preset_Happy;
extern const EyeConfig Preset_Glee;
extern const EyeConfig Preset_Sad;
extern const EyeConfig Preset_Worried;
extern const EyeConfig Preset_Worried_Alt;
extern const EyeConfig Preset_Focused;
extern const EyeConfig Preset_Annoyed;
extern const EyeConfig Preset_Annoyed_Alt;
extern const EyeConfig Preset_Surprised;
extern const EyeConfig Preset_Skeptic;
extern const EyeConfig Preset_Skeptic_Alt;
extern const EyeConfig Preset_Frustrated;
extern const EyeConfig Preset_Unimpressed;
extern const EyeConfig Preset_Unimpressed_Alt;
extern const EyeConfig Preset_Sleepy;
extern const EyeConfig Preset_Sleepy_Alt;
extern const EyeConfig Preset_Suspicious;
extern const EyeConfig Preset_Suspicious_Alt;
extern const EyeConfig Preset_Squint;
extern const EyeConfig Preset_Squint_Alt;
extern const EyeConfig Preset_Angry;
extern const EyeConfig Preset_Furious;
extern const EyeConfig Preset_Scared;
extern const EyeConfig Preset_Awe;

// 声明你之前新增的疑惑表情（大小眼）
extern const EyeConfig Preset_Confused_Right;
extern const EyeConfig Preset_Confused_Left;

#endif