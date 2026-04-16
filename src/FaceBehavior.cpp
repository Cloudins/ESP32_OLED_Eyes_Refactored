#include "FaceBehavior.h"
#include "Face.h"

FaceBehavior::FaceBehavior(Face& face) : _face(face), Timer(500) {
	Timer.Start();
	Clear();
	Emotions[(int)eEmotions::Normal] = 1.0;
}

void FaceBehavior::SetEmotion(eEmotions emotion, float value) { Emotions[emotion] = value; }
float FaceBehavior::GetEmotion(eEmotions emotion) { return Emotions[emotion]; }

void FaceBehavior::Clear() {
	for (int emotion = 0; emotion < eEmotions::EMOTIONS_COUNT; emotion++) {
		Emotions[emotion] = 0.0;
	}
}

eEmotions FaceBehavior::GetRandomEmotion() {
	float sum_of_weight = 0;
	for (int emotion = 0; emotion < eEmotions::EMOTIONS_COUNT; emotion++) {
		sum_of_weight += Emotions[emotion];
	}
	if (sum_of_weight == 0) return eEmotions::Normal;

	float rand_val = random(0, 1000 * sum_of_weight) / 1000.0;
	float acc = 0;
	for (int emotion = 0; emotion < eEmotions::EMOTIONS_COUNT; emotion++) {
		if (Emotions[emotion] == 0) continue;
		acc += Emotions[emotion];
		if (rand_val <= acc) return (eEmotions)emotion;
	}
	return eEmotions::Normal;
}

void FaceBehavior::Update() {
	Timer.Update();
	if (Timer.IsExpired()) {
		Timer.Reset();
		eEmotions newEmotion = GetRandomEmotion();
		if (CurrentEmotion != newEmotion) {
			GoToEmotion(newEmotion);
		}
	}
}

void FaceBehavior::GoToEmotion(eEmotions emotion) {
	CurrentEmotion = emotion;
	switch (CurrentEmotion) {
        case eEmotions::Normal: _face.Expression.GoTo_Normal(); break;
        case eEmotions::Angry: _face.Expression.GoTo_Angry(); break;
        case eEmotions::Glee: _face.Expression.GoTo_Glee(); break;
        case eEmotions::Happy: _face.Expression.GoTo_Happy(); break;
        case eEmotions::Sad: _face.Expression.GoTo_Sad(); break;
        case eEmotions::Worried: _face.Expression.GoTo_Worried(); break;
        case eEmotions::Focused: _face.Expression.GoTo_Focused(); break;
        case eEmotions::Annoyed: _face.Expression.GoTo_Annoyed(); break;
        case eEmotions::Surprised: _face.Expression.GoTo_Surprised(); break;
        case eEmotions::Skeptic: _face.Expression.GoTo_Skeptic(); break;
        case eEmotions::Frustrated: _face.Expression.GoTo_Frustrated(); break;
        case eEmotions::Unimpressed: _face.Expression.GoTo_Unimpressed(); break;
        case eEmotions::Sleepy: _face.Expression.GoTo_Sleepy(); break;
        case eEmotions::Suspicious: _face.Expression.GoTo_Suspicious(); break;
        case eEmotions::Squint: _face.Expression.GoTo_Squint(); break;
        case eEmotions::Furious: _face.Expression.GoTo_Furious(); break;
        case eEmotions::Scared: _face.Expression.GoTo_Scared(); break;
        case eEmotions::Awe: _face.Expression.GoTo_Awe(); break;
        case eEmotions::Confused: _face.Expression.GoTo_Confused(); break; 
        default: break;
	}
}