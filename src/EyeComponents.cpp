#include "EyeComponents.h"

// --- EyeTransition ---
EyeTransition::EyeTransition() : Animation(500){}
void EyeTransition::Update() { Apply(Animation.GetValue()); }
void EyeTransition::Apply(float t) {
	Origin->OffsetX = Origin->OffsetX * (1.0 - t) + Destin.OffsetX * t;
	Origin->OffsetY = Origin->OffsetY * (1.0 - t) + Destin.OffsetY * t;
	Origin->Height = Origin->Height * (1.0 - t) + Destin.Height * t;
	Origin->Width = Origin->Width * (1.0 - t) + Destin.Width * t;
	Origin->Slope_Top = Origin->Slope_Top * (1.0 - t) + Destin.Slope_Top * t;
	Origin->Slope_Bottom = Origin->Slope_Bottom * (1.0 - t) + Destin.Slope_Bottom * t;
	Origin->Radius_Top = Origin->Radius_Top * (1.0 - t) + Destin.Radius_Top * t;
	Origin->Radius_Bottom = Origin->Radius_Bottom * (1.0 - t) + Destin.Radius_Bottom * t;
	Origin->Inverse_Radius_Top = Origin->Inverse_Radius_Top * (1.0 - t) + Destin.Inverse_Radius_Top * t;
	Origin->Inverse_Radius_Bottom = Origin->Inverse_Radius_Bottom * (1.0 - t) + Destin.Inverse_Radius_Bottom * t;
	Origin->Inverse_Offset_Top = Origin->Inverse_Offset_Top * (1.0 - t) + Destin.Inverse_Offset_Top * t;
	Origin->Inverse_Offset_Bottom = Origin->Inverse_Offset_Bottom * (1.0 - t) + Destin.Inverse_Offset_Bottom * t;
}

// --- EyeTransformation ---
EyeTransformation::EyeTransformation() : Animation(200) {}
void EyeTransformation::Update() {
	auto t = Animation.GetValue();
	Current.MoveX = (Destin.MoveX - Origin.MoveX) * t + Origin.MoveX;
	Current.MoveY = (Destin.MoveY - Origin.MoveY) * t + Origin.MoveY;
	Current.ScaleX = (Destin.ScaleX - Origin.ScaleX) * t + Origin.ScaleX;
	Current.ScaleY = (Destin.ScaleY - Origin.ScaleY) * t + Origin.ScaleY;
	Apply();
}
void EyeTransformation::Apply()
{
	Output.OffsetX = Input->OffsetX + Current.MoveX;
	Output.OffsetY = Input->OffsetY - Current.MoveY;
	Output.Width = Input->Width * Current.ScaleX;
	Output.Height = Input->Height * Current.ScaleY;

	Output.Slope_Top = Input->Slope_Top;
	Output.Slope_Bottom = Input->Slope_Bottom;
	Output.Radius_Top = Input->Radius_Top;
	Output.Radius_Bottom = Input->Radius_Bottom;
	Output.Inverse_Radius_Top = Input->Inverse_Radius_Top;
	Output.Inverse_Radius_Bottom = Input->Inverse_Radius_Bottom;
	Output.Inverse_Offset_Top = Input->Inverse_Offset_Top;
	Output.Inverse_Offset_Bottom = Input->Inverse_Offset_Bottom;
}
void EyeTransformation::SetDestin(Transformation trans) {
	Origin = Current; Destin = trans;
}

// --- EyeVariation ---
EyeVariation::EyeVariation() : Animation(0, 1000, 0, 1000, 0){}
void EyeVariation::Clear() { memset(&Values, 0, sizeof(EyeConfig)); }
void EyeVariation::Update() { Apply(2.0 * Animation.GetValue() - 1.0); }
void EyeVariation::Apply(float t) {
	Output.OffsetX = Input->OffsetX + Values.OffsetX * t;
	Output.OffsetY = Input->OffsetY + Values.OffsetY * t;
	Output.Height = Input->Height + Values.Height * t;;
	Output.Width = Input->Width + Values.Width * t;
	Output.Slope_Top = Input->Slope_Top + Values.Slope_Top * t;
	Output.Slope_Bottom = Input->Slope_Bottom + Values.Slope_Bottom * t;
	Output.Radius_Top = Input->Radius_Top + Values.Radius_Top * t;
	Output.Radius_Bottom = Input->Radius_Bottom + Values.Radius_Bottom * t;
	Output.Inverse_Radius_Top = Input->Inverse_Radius_Top + Values.Inverse_Radius_Top * t;
	Output.Inverse_Radius_Bottom = Input->Inverse_Radius_Bottom + Values.Inverse_Radius_Bottom * t;
	Output.Inverse_Offset_Top = Input->Inverse_Offset_Top + Values.Inverse_Offset_Top * t;
	Output.Inverse_Offset_Bottom = Input->Inverse_Offset_Bottom + Values.Inverse_Offset_Bottom * t;;
}

// --- EyeBlink ---
EyeBlink::EyeBlink() : Animation(40, 100, 40) {}
void EyeBlink::Update() {
	auto t = Animation.GetValue();
	if(Animation.GetElapsed() > Animation.Interval) t = 0.0;
	Apply(t * t);
}
void EyeBlink::Apply(float t) {
	Output = *Input;
	Output.Width = (BlinkWidth - Input->Width) * t + Input->Width;
	Output.Height = (BlinkHeight - Input->Height) * t + Input->Height;
    // 闭眼时半径和斜率消失
	Output.Slope_Top *= (1.0 - t); Output.Slope_Bottom *= (1.0 - t);
	Output.Radius_Top *= (1.0 - t); Output.Radius_Bottom *= (1.0 - t);
}