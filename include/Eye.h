#ifndef _EYE_h
#define _EYE_h

#include <Arduino.h>
#include "EyeConfig.h"
#include "EyeComponents.h"
#include "EyeDrawer.h"

class Face; // 前置声明

class Eye {
protected:
    Face& _face;
    void ChainOperators();

public:
    Eye(Face& face);
    void Update();

    uint16_t CenterX;
    uint16_t CenterY;
    bool IsMirrored = false;

    EyeConfig Config;
    EyeConfig* FinalConfig;

    EyeTransition Transition;
    EyeTransformation Transformation;
    EyeVariation Variation1;
    EyeVariation Variation2;
    EyeBlink BlinkTransformation;

    void ApplyPreset(const EyeConfig preset);
    void TransitionTo(const EyeConfig preset);
    void Draw();
};
#endif