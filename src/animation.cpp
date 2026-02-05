#include "animation.h"

// Named use cases, I'll fix the readability later
namespace Audio
{
	bool winSound = true;
}
namespace Delay
{
	float timeTarget = 0.0f;
	float delaySpeed = 1.0f;
}
namespace FadeState
{
	float alpha = 0.0f;
	float alphaOut = 1.0f;
	float fadeSpeed = 1.0f;
}

void Delay::Update()
{
	timeTarget += delaySpeed * Game::getFrame();
	if (timeTarget > 3.0f) timeTarget = 3.0f;
}
void Delay::Reset()
{
	timeTarget = 0.0f;
}

void FadeState::Update()
{
	alpha += fadeSpeed * Game::getFrame();
	if (alpha > 1.0f) alpha = 1.0f;
}
void FadeState::Out()
{
	alphaOut -= (fadeSpeed / 14) * Game::getFrame();
	if (alphaOut < 0.0f) alphaOut = 0.0f;
}
void FadeState::Reset()
{
	alpha = 0.0f;
	alphaOut = 1.0f;
}

Color FadeState::getTint(Color tint)
{
	tint.a = (unsigned char)(alpha * 255);
	return tint;
}

Color FadeState::tintOut(Color tint)
{
	tint.a = (unsigned char)(alphaOut * 255);
	return tint;
}