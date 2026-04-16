#ifndef _LOOKASSISTANT_h
#define _LOOKASSISTANT_h

#include <Arduino.h>
#include "AsyncTimer.h"
#include "EyeComponents.h"

class Face; // 前置声明

class LookAssistant {
protected:
	Face&  _face;
public:
	LookAssistant(Face& face);
	Transformation transformation;
	AsyncTimer Timer;
	void LookAt(float x, float y);
	void Update();
};
#endif