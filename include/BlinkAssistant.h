#ifndef _BLINKASSISTANT_h
#define _BLINKASSISTANT_h

#include <Arduino.h>
#include "AsyncTimer.h"

class Face; // 前置声明

class BlinkAssistant {
protected:
	Face&  _face;
public:
	BlinkAssistant(Face& face);
	AsyncTimer Timer;
	void Update();
	void Blink();
};
#endif