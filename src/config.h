#pragma once

#include <string>
#include <raylib.h>

// Window minimum size
inline constexpr int screenHeight{ 720 };
inline constexpr int screenWidth{ 1280 };

// Fonts
inline constexpr float fontSizeLarge{ 70.0f };
inline constexpr float fontSizeSmall{ 30.0f };
inline constexpr float fontSpacing{ 2.0f };

// Paths
inline constexpr const char* FONT_PATH = "Resources/Font/The Bomb Sound.ttf";
inline constexpr const char* FILTER[] = { "*.png", "*.jpg", "*.bpm" };

// Extra settings
enum class Scene {
	LOADING_SCENE,
	MENU_SCENE,						// Display menu (Play, Exit)
	BEGIN_PLAY_SCENE,				// Begin playing the puzzle 
	CHOOSE_IMAGE_SCENE,				// Show scene on choosing image (built-in, custom)
	CROP_SLICE_IMAGE_SCENE,			// Square, Portrait, Landscape (3x3, 4x4, 5x5, ... 3x4, 3x5, 3x6, ... etc)
	PAUSE_SCENE,					// Menu and Resume
	WIN_SCENE						// Solved puzzle scene
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

// Other config
const char* toText(int num);

struct Config {
	// For updating window size
	int currentWindowWidth;
	int currentWindowHeight;

	// For updating scene
	Scene currentScene;

	// For draw if hovered
	bool puz1hover;
	bool puz2hover;
	bool puz3hover;

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