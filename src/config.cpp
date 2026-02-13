#include "config.h"

const char* toText(int num)
{
	static std::string buf;
	buf = std::to_string(num);
	return buf.c_str();
}

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
