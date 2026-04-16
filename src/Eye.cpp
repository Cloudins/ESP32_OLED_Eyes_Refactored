#include "Eye.h"
#include "Face.h"

Eye::Eye(Face& face) : _face(face) {
	this->IsMirrored = false;
	ChainOperators();
    // 初始化默认 Variation 动画时间
	Variation1.Animation.SetInterval(200, 200, 200, 200, 0);
	Variation2.Animation.SetInterval(0, 200, 200, 200, 200);
}

void Eye::ChainOperators() {
	Transition.Origin = &Config;
	Transformation.Input = &Config;
	Variation1.Input = &(Transformation.Output);
	Variation2.Input = &(Variation1.Output);
	BlinkTransformation.Input = &(Variation2.Output);
	FinalConfig = &(BlinkTransformation.Output);
}

void Eye::Update() {
	Transition.Update();
	Transformation.Update();
	Variation1.Update();
	Variation2.Update();
	BlinkTransformation.Update();
}

void Eye::Draw() {
	Update();
	EyeDrawer::Draw(CenterX, CenterY, FinalConfig);
}

void Eye::TransitionTo(const EyeConfig config) {
	Transition.Destin.OffsetX = IsMirrored ? -config.OffsetX : config.OffsetX;
	Transition.Destin.OffsetY = -config.OffsetY;
	Transition.Destin.Height = config.Height;
	Transition.Destin.Width = config.Width;
	Transition.Destin.Slope_Top = IsMirrored ? config.Slope_Top : -config.Slope_Top;
	Transition.Destin.Slope_Bottom = IsMirrored ? config.Slope_Bottom : -config.Slope_Bottom;
	Transition.Destin.Radius_Top = config.Radius_Top;
	Transition.Destin.Radius_Bottom = config.Radius_Bottom;
	Transition.Animation.Restart();
}

void Eye::ApplyPreset(const EyeConfig config) {
    // 立即应用不带过度
    Config = config; 
    if(IsMirrored) { Config.OffsetX *= -1; Config.Slope_Top *= -1; }
}