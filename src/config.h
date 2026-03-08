#pragma once

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <raylib.h>

// Window minimum size
inline constexpr int screenHeight{ 720 };
inline constexpr int screenWidth{ 1280 };

// Fonts
inline constexpr float fontSizeLarge{ 70.0f };
inline constexpr float fontSizeSmall{ 30.0f };
inline constexpr float fontSpacing{ 2.0f };

inline float getScaledFont(float gsw, float gsh)
{
	// Can be used anywhere but the highest detail is the base font, not the scaledFont
	float scaleX = gsw / screenWidth;
	float scaleY = gsh / screenHeight;
	float scale = std::min(scaleX, scaleY);
	float scaledFont = fontSizeSmall * scale;	// Base font size: 30.0f

	return scaledFont;
}

// Paths
inline constexpr const char* FONT_PATH = "Resources/Font/The Bomb Sound.ttf";
inline constexpr const char* FILTER[] = { "*.png", "*.jpg", "*.bpm" };

// Extra settings
enum class Scene {
	MENU_SCENE,						// Display menu (Play, Exit)
	CHOOSE_IMAGE_SCENE,				// Show scene on choosing image (built-in, custom)
	CROP_SLICE_IMAGE_SCENE,			// Square, Portrait, Landscape (3x3, 4x4, 5x5, ... 3x4, 3x5, 3x6, ... etc)
	BEGIN_PLAY_SCENE,				// Begin playing the puzzle 
	PAUSE_SCENE,					// Menu and Resume
	WIN_SCENE,						// Solved puzzle scene

	MAX_SCENES
};

enum ImageType {
	IMAGE_AS_BG,
	IMAGE_AS_BG_OVERLAY,
	IMAGE_AS_TITLE,
	IMAGE_AS_ICON,
	IMAGE_AS_PUZZLE
};

enum DrawType {
	TEXT,
	TEXTURE,
	RECTANGLE
};

enum Levels {
	PUZ_1,
	PUZ_2,
	PUZ_3,

	MAX_PUZ
};

enum StarRate {
	STAR_0,
	BLANK_1,
	BLANK_2,
	STAR_3,
	STAR_4,
	STAR_5,
	STAR_6,
	STAR_7,
	STAR_8,
	STAR_9,
	STAR_10,

	MAX_RATE
};

// Other config
const char* toText(int num);
const char* floatToText(float num);

struct Config {
	// For updating window size
	int currentWindowWidth;
	int currentWindowHeight;

	// For updating scene
	Scene currentScene;

	// For relative font scaling
	float fontScaled;

	// For draw if hovered
	bool puz1hover;
	bool puz2hover;
	bool puz3hover;
	// Confirm if selected
	bool puz1selected;
	bool puz2selected;
	bool puz3selected;

	// For mouse position every frame
	Vector2 clickLocation;

	// For guide
	bool draw_guide;
};

namespace Game
{
	inline bool exited;
	inline bool isExited() { return exited; }
	extern float frameTime;
	void updateFrame();
	inline float getFrame() { return frameTime; }
}

extern Config gc;