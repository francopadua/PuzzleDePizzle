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
	float alphaOutText = 1.0f;
	float alphaOutTexture = 0.9f;
	float alphaOutRec = 1.0f;
	float fadeSpeed = 1.0f;
}

void Delay::Update()
{
	timeTarget += delaySpeed * Game::getFrame();
	if (timeTarget > 4.0f) timeTarget = 4.0f;
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
void FadeState::Out(int seconds, DrawType drawType)
{
	if (drawType == TEXT) {
		if (seconds <= 0)	return;
		alphaOutText -= (fadeSpeed / seconds) * Game::getFrame();
		if (alphaOutText < 0.0f) alphaOutText = 0.0f;
	}

	if (drawType == TEXTURE) {
		if (seconds <= 0)	return;
		alphaOutTexture -= (fadeSpeed / seconds) * Game::getFrame();
		if (alphaOutTexture < 0.0f) alphaOutTexture = 0.0f;
	}

	if (drawType == RECTANGLE) {
		if (seconds <= 0)	return;
		alphaOutRec -= (fadeSpeed / seconds) * Game::getFrame();
		if (alphaOutRec < 0.0f) alphaOutRec = 0.0f;
	}
}
void FadeState::Reset()
{
	alpha = 0.0f;
	alphaOutText = 1.0f;
	alphaOutTexture = 0.9f;
}

Color FadeState::getTint(Color tint)
{
	tint.a = (unsigned char)(alpha * 255);
	return tint;
}

Color FadeState::tintOut(Color tint, DrawType drawType)
{
	if (drawType == TEXT)
		tint.a = (unsigned char)(alphaOutText * 255);
	if (drawType == TEXTURE)
		tint.a = (unsigned char)(alphaOutTexture * 255);
	if (drawType == RECTANGLE)
		tint.a = (unsigned char)(alphaOutRec * 255);

	return tint;
}