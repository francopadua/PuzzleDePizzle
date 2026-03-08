#include "config.h"

const char* toText(int num)
{
	static std::string buf;
	buf = std::to_string(num);
	return buf.c_str();
}

const char* floatToText(float num)
{
	int tenths = static_cast<int>(std::round(num * 10)) % 10;
	static std::string buf;
	std::stringstream ss;

	// Percent with decimal places
	if (tenths == 0)
		ss << static_cast<int>(num);
	else
		ss << std::fixed << std::setprecision(1) << num;

	//buf = std::to_string(num);
	buf = ss.str();

	if (num == 0.0f)
		return TextFormat("0%%");
	if (num < 3.0f)
		return TextFormat("<3%%");
	return TextFormat("%s%%", buf.c_str());
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
