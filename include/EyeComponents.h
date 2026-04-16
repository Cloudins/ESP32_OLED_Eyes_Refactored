#ifndef _EYECOMPONENTS_h
#define _EYECOMPONENTS_h

#include <Arduino.h>
#include "EyeConfig.h"
#include "Animations.h"

// --- Transition ---
class EyeTransition {
public:
	EyeTransition();
	EyeConfig* Origin;
	EyeConfig Destin;
	RampAnimation Animation;
	void Update();
	void Apply(float t);
};

// --- Transformation ---
struct Transformation {
	float MoveX = 0.0; float MoveY = 0.0;
	float ScaleX = 1.0; float ScaleY = 1.0;
};

class EyeTransformation {
public:
	EyeTransformation();
	EyeConfig* Input;
	EyeConfig Output;
	Transformation Origin;
	Transformation Current;
	Transformation Destin;
	RampAnimation Animation;
	void Update();
	void Apply();
	void SetDestin(Transformation transformation);
};

// --- Variation ---
class EyeVariation {
public:
	EyeVariation();
	EyeConfig* Input;
	EyeConfig Output;
	TrapeziumPulseAnimation Animation;
	EyeConfig Values;
	void Clear();
	void SetInterval(uint16_t t0, uint16_t t1, uint16_t t2, uint16_t t3, uint16_t t4);
	void Update();
	void Apply(float t);
};

// --- Blink ---
class EyeBlink {
public:
	EyeBlink();
	EyeConfig* Input;
	EyeConfig Output;
	TrapeziumAnimation Animation;
	int32_t BlinkWidth = 60;
	int32_t BlinkHeight = 2;
	void Update();
	void Apply(float t);
};

#endif