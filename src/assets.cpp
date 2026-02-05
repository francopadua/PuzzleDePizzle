#include "assets.h"
#include "Button.h"
#include "transform.h"
#include <iostream>

Assets ga{};

namespace gA {
	// Menu Scene
	Button playButton;
	Button exitButton;
	ToggleButton musicButton;
	ToggleButton soundButton;

	// Choose Image Scene
	Button backButton;
	Button folderButton;

	// Slice Image Scene
	Button plusButton;
	Button subButton;
	Button startButton;

	// Begin Play Scene
	Button pauseButton;
	ToggleButton hint1;

	// Pause Scene
	Button resumeButton;
	Button menuButton;

	// Win Scene
	Button retryButton;
}

void LoadAssets()
{
	// From Config
	gc.currentScene = Scene::MENU_SCENE;
	gc.puz1hover = false;
	gc.puz2hover = false;
	gc.puz3hover = false;

	// Backgrounds
	ga.myBgImage = LoadImage("Resources/Images/bg.png");
	ga.myBgTexture = LoadTextureFromImage(ga.myBgImage);
	ga.myBgImageOverlay = LoadImage("Resources/Images/bgOverlay.png");
	ga.myBgTextureOverlay = LoadTextureFromImage(ga.myBgImageOverlay);
	ga.myBgBorder[0] = LoadImage("Resources/Images/wood_border.png");
	ga.myBgBorder[1] = LoadImage("Resources/Images/wood_border.png");
	ImageRotateCW(&ga.myBgBorder[1]);
	ga.myBgBorderTexture[0] = LoadTextureFromImage(ga.myBgBorder[0]);
	ga.myBgBorderTexture[1] = LoadTextureFromImage(ga.myBgBorder[1]);
	ga.myTitle = LoadImage("Resources/Images/title.png");
	ga.myTitleTexture = LoadTextureFromImage(ga.myTitle);

	// Built-in puzzle image
	ga.puzzleImage1 = LoadImage("Resources/Images/bertface.png");
	ga.puzzleImage1Texture = LoadTextureFromImage(ga.puzzleImage1);
	ga.puzzleImage2 = LoadImage("Resources/Images/jerry.jpg");
	ga.puzzleImage2Texture = LoadTextureFromImage(ga.puzzleImage2);
	ga.puzzleImage3 = LoadImage("Resources/Images/mayon.jpg");
	ga.puzzleImage3Texture = LoadTextureFromImage(ga.puzzleImage3);

	// Font
	ga.myFontLarge = LoadFontEx("Resources/Font/The Bomb Sound.ttf", fontSizeLarge, nullptr, 0);
	ga.myFontSmall = LoadFontEx("Resources/Font/The Bomb Sound.ttf", fontSizeSmall, nullptr, 0);

	// Text to Image
	// Choose Image Scene
	ga.txt_ChooseImage = ImageTextEx(ga.myFontLarge, "Choose Image", fontSizeLarge, fontSpacing, BLACK);
	ga.txt_ChooseImage_texture = LoadTextureFromImage(ga.txt_ChooseImage);
	ga.puzImg1Txt = ImageTextEx(ga.myFontLarge, "Bert Face", fontSizeLarge, fontSpacing, BLACK);
	ga.puzImg1Txt_texture = LoadTextureFromImage(ga.puzImg1Txt);
	ga.puzImg2Txt = ImageTextEx(ga.myFontLarge, "High Jerry", fontSizeLarge, fontSpacing, BLACK);
	ga.puzImg2Txt_texture = LoadTextureFromImage(ga.puzImg2Txt);
	ga.puzImg3Txt = ImageTextEx(ga.myFontLarge, "Mayon", fontSizeLarge, fontSpacing, BLACK);
	ga.puzImg3Txt_texture = LoadTextureFromImage(ga.puzImg3Txt);

	// Slice Image Scene
	ga.txt_SliceImage = ImageTextEx(ga.myFontLarge, "Slice Image", fontSizeLarge, fontSpacing, BLACK);
	ga.txt_SliceImage_texture = LoadTextureFromImage(ga.txt_SliceImage);

	// Pause Scene
	ga.txt_Paused = ImageTextEx(ga.myFontLarge, "Paused", fontSizeLarge, fontSpacing, BLACK);
	ga.txt_Paused_texture = LoadTextureFromImage(ga.txt_Paused);

	// THE IMAGE PUZZLE
	ga.myPuzzleImage;
	ga.myPuzzleTexture;

	// ================================================================================

	// Audio
	ga.menuMusic = LoadMusicStream("Resources/Audio/music1.mp3");
	ga.playMusic = LoadMusicStream("Resources/Audio/music2.mp3");
	ga.solvedSound = LoadSound("Resources/Audio/sound1.mp3");
	ga.slideSound = LoadSound("Resources/Audio/sound2.mp3");
}

void gA::LoadClassedAssets()
{
	// Menu Scene
	playButton.load(LoadImage("Resources/Images/play_button_up.png"), LoadImage("Resources/Images/play_button_down.png"), MEDIUM);
	exitButton.load(LoadImage("Resources/Images/exit_button_up.png"), LoadImage("Resources/Images/exit_button_down.png"), MEDIUM);
	musicButton.load(LoadImage("Resources/Images/tog_music_up.png"), LoadImage("Resources/Images/tog_music_down.png"), LoadImage("Resources/Images/tog_music_disabled.png"), MEDIUM);
	soundButton.load(LoadImage("Resources/Images/tog_aud_up.png"), LoadImage("Resources/Images/tog_aud_down.png"), LoadImage("Resources/Images/tog_aud_disabled.png"), MEDIUM);

	// Choose Image Scene
	backButton.load(LoadImage("Resources/Images/back_button_up.png"), LoadImage("Resources/Images/back_button_down.png"), MEDIUM);
	folderButton.load(LoadImage("Resources/Images/folder_up.png"), LoadImage("Resources/Images/folder_down.png"), MEDIUM);

	// Slice Image Scene
	plusButton.load(LoadImage("Resources/Images/plus_up.png"), LoadImage("Resources/Images/plus_down.png"), MEDIUM);
	subButton.load(LoadImage("Resources/Images/sub_up.png"), LoadImage("Resources/Images/sub_down.png"), MEDIUM);
	startButton.load(LoadImage("Resources/Images/start_button_up.png"), LoadImage("Resources/Images/start_button_down.png"), MEDIUM);

	// Begin Play Scene
	pauseButton.load(LoadImage("Resources/Images/pause_button_up.png"), LoadImage("Resources/Images/pause_button_down.png"), MEDIUM);
	hint1.load(LoadImage("Resources/Images/tog_h1_up.png"), LoadImage("Resources/Images/tog_h1_down.png"), LoadImage("Resources/Images/tog_h1_disabled.png"), MEDIUM, true, 60.0f);

	// Pause Scene
	resumeButton.load(LoadImage("Resources/Images/res_button_up.png"), LoadImage("Resources/Images/res_button_down.png"), MEDIUM);
	menuButton.load(LoadImage("Resources/Images/menu_button_up.png"), LoadImage("Resources/Images/menu_button_down.png"), MEDIUM);

	// Win Scene
	retryButton.load(LoadImage("Resources/Images/retry_button_up.png"), LoadImage("Resources/Images/retry_button_down.png"), MEDIUM);
}

void UnloadAssets()
{
	// Bg and Bg overlay
	UnloadImage(ga.myBgImage);
	UnloadTexture(ga.myBgTexture);
	UnloadImage(ga.myBgImageOverlay);
	UnloadTexture(ga.myBgTextureOverlay);
	UnloadImage(ga.myBgBorder[0]);
	UnloadImage(ga.myBgBorder[1]);
	UnloadTexture(ga.myBgBorderTexture[0]);
	UnloadTexture(ga.myBgBorderTexture[1]);
	UnloadImage(ga.myTitle);
	UnloadTexture(ga.myTitleTexture);

	// Built-in Puzzle image icons
	UnloadImage(ga.puzzleImage1);
	UnloadTexture(ga.puzzleImage1Texture);
	UnloadImage(ga.puzzleImage2);
	UnloadTexture(ga.puzzleImage2Texture);
	UnloadImage(ga.puzzleImage3);
	UnloadTexture(ga.puzzleImage3Texture);

	// The Image Puzzle
	if (ga.myPuzzleImage.data != nullptr)
		UnloadImage(ga.myPuzzleImage);
	if (ga.myPuzzleTexture.id != 0)
		UnloadTexture(ga.myPuzzleTexture);

	// Texts
	// Choose Image Scene
	UnloadImage(ga.txt_ChooseImage);
	UnloadTexture(ga.txt_ChooseImage_texture);
	UnloadImage(ga.puzImg1Txt);
	UnloadTexture(ga.puzImg1Txt_texture);
	UnloadImage(ga.puzImg2Txt);
	UnloadTexture(ga.puzImg2Txt_texture);
	UnloadImage(ga.puzImg3Txt);
	UnloadTexture(ga.puzImg3Txt_texture);

	// Slice Image Scene
	UnloadImage(ga.txt_SliceImage);
	UnloadTexture(ga.txt_SliceImage_texture);

	// Pause Scene
	UnloadImage(ga.txt_Paused);
	UnloadTexture(ga.txt_Paused_texture);

	// Font
	UnloadFont(ga.myFontLarge);
	UnloadFont(ga.myFontSmall);

	// Audio
	UnloadMusicStream(ga.menuMusic);
	UnloadMusicStream(ga.playMusic);
	UnloadSound(ga.solvedSound);
	UnloadSound(ga.slideSound);


	// ==================================================


	// Classed Assets
	// Menu Scene
	gA::playButton.unloadImage();
	gA::playButton.unloadTexture();
	gA::exitButton.unloadImage();
	gA::exitButton.unloadTexture();
	gA::musicButton.unloadImage();
	gA::musicButton.unloadTexture();
	gA::soundButton.unloadImage();
	gA::soundButton.unloadTexture();

	// Choose Image Scene
	gA::backButton.unloadImage();
	gA::backButton.unloadTexture();
	gA::folderButton.unloadImage();
	gA::folderButton.unloadTexture();

	// Slice Image Scene
	gA::plusButton.unloadImage();
	gA::plusButton.unloadTexture();
	gA::subButton.unloadImage();
	gA::subButton.unloadTexture();
	gA::startButton.unloadImage();
	gA::startButton.unloadTexture();

	// Begin Play Scene
	gA::pauseButton.unloadImage();
	gA::pauseButton.unloadTexture();
	gA::hint1.unloadImage();
	gA::hint1.unloadTexture();

	// Pause Scene
	gA::resumeButton.unloadImage();
	gA::resumeButton.unloadTexture();
	gA::menuButton.unloadImage();
	gA::menuButton.unloadTexture();

	// Win Scene
	gA::retryButton.unloadImage();
	gA::retryButton.unloadTexture();
}