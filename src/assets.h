#pragma once

#include "config.h"
#include "Button.h"
#include "ToggleButton.h"

struct Assets {
	// Backgrounds
	Image myBgImage;
	Texture2D myBgTexture;
	Image myBgImageOverlay;
	Texture2D myBgTextureOverlay;
	Image myBgBorder[2];
	Texture2D myBgBorderTexture[2];
	Image myTitle;
	Texture2D myTitleTexture;

	// Built-in puzzle image
	Image puzzleImage1;
	Texture2D puzzleImage1Texture;
	Image puzzleImage2;
	Texture2D puzzleImage2Texture;
	Image puzzleImage3;
	Texture2D puzzleImage3Texture;

	// THE IMAGE PUZZLE
	Image myPuzzleImage;
	Texture2D myPuzzleTexture;

	// Font
	Font myFontLarge;
	Font myFontSmall;

	// Text to Image
	// Choose Image Scene
	Image txt_ChooseImage;
	Texture2D txt_ChooseImage_texture;
	Image puzImg1Txt;
	Texture2D puzImg1Txt_texture;
	Image puzImg2Txt;
	Texture2D puzImg2Txt_texture;
	Image puzImg3Txt;
	Texture2D puzImg3Txt_texture;

	// Slice Image Scene
	Image txt_SliceImage;
	Texture2D txt_SliceImage_texture;

	// Pause Scene
	Image txt_Paused;
	Texture2D txt_Paused_texture;

	// ================================================================================

	// Audio
	Music menuMusic;
	Music playMusic;
	Sound solvedSound;
	Sound slideSound;
	Sound selectSound;
};

extern Assets ga;

void LoadAssets();
void UnloadAssets();

namespace gA {
	// Menu Scene
	extern Button playButton;
	extern Button exitButton;
	extern ToggleButton musicButton;
	extern ToggleButton soundButton;

	// Choose Image Scene
	extern Button backButton;
	extern Button folderButton;

	// Slice Image Scene
	extern Button plusButton;
	extern Button subButton;
	extern Button startButton;

	// Begin Play Scene
	extern Button pauseButton;
	extern ToggleButton hint1;
	extern ToggleButton hint2;

	// Pause Scene
	extern Button resumeButton;
	extern Button menuButton;

	// Win Scene
	extern Button retryButton;

	void LoadClassedAssets();
}