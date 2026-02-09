#pragma once

#include "config.h"
#include <iostream>
#include <raylib.h>

namespace Audio
{
	extern bool winSound;
}
namespace Delay
{
	extern int countdown;
	extern float timeTarget;
	extern float delaySpeed;

	void Update();
	void Reset();
}
namespace FadeState
{
	extern float alpha;
	extern float alphaOutText;
	extern float alphaOutTexture;
	extern float alphaOutRec;
	extern float fadeSpeed;
	extern float fadeOutSpeed;

	void Update();
	void Out(int seconds, DrawType drawType);
	void Reset();

	Color getTint(Color tint);
	Color tintOut(Color tint, DrawType drawType);
}
