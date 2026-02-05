#include "config.h"

Config gc{};

// GLOBAL FRAME SO THAT I CAN USE LATER
namespace Game
{
	float frameTime = 0.0f;
}

void Game::updateFrame()
{
	frameTime = GetFrameTime();
}
