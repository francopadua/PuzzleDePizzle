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
	ToggleButton hint2;

	// Pause Scene
	Button resumeButton;
	Button menuButton;

	// Win Scene
	Button retryButton;

	// Level Results
	LevelResult puz[MAX_PUZ];
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
	ga.myBgBlankImage = LoadImage("Resources/Images/bg_blank.png");
	ga.myBgBlankTexture = LoadTextureFromImage(ga.myBgBlankImage);

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
	ga.puzzleImage1 = LoadImage("Resources/Images/Icons/icon1.png");
	ga.puzzleImage1Texture = LoadTextureFromImage(ga.puzzleImage1);
	ga.puzzleImage2 = LoadImage("Resources/Images/Icons/icon2.png");
	ga.puzzleImage2Texture = LoadTextureFromImage(ga.puzzleImage2);
	ga.puzzleImage3 = LoadImage("Resources/Images/Icons/icon3.png");
	ga.puzzleImage3Texture = LoadTextureFromImage(ga.puzzleImage3);
	// Stars
	ga.starImage[STAR_0] = LoadImage("Resources/Images/Rate/0.png");
	ga.starImage[STAR_3] = LoadImage("Resources/Images/Rate/3.png");
	ga.starImage[STAR_4] = LoadImage("Resources/Images/Rate/4.png");
	ga.starImage[STAR_5] = LoadImage("Resources/Images/Rate/5.png");
	ga.starImage[STAR_6] = LoadImage("Resources/Images/Rate/6.png");
	ga.starImage[STAR_7] = LoadImage("Resources/Images/Rate/7.png");
	ga.starImage[STAR_8] = LoadImage("Resources/Images/Rate/8.png");
	ga.starImage[STAR_9] = LoadImage("Resources/Images/Rate/9.png");
	ga.starImage[STAR_10] = LoadImage("Resources/Images/Rate/10.png");
	ga.starTexture[STAR_0] = LoadTextureFromImage(ga.starImage[STAR_0]);
	ga.starTexture[STAR_3] = LoadTextureFromImage(ga.starImage[STAR_3]);
	ga.starTexture[STAR_4] = LoadTextureFromImage(ga.starImage[STAR_4]);
	ga.starTexture[STAR_5] = LoadTextureFromImage(ga.starImage[STAR_5]);
	ga.starTexture[STAR_6] = LoadTextureFromImage(ga.starImage[STAR_6]);
	ga.starTexture[STAR_7] = LoadTextureFromImage(ga.starImage[STAR_7]);
	ga.starTexture[STAR_8] = LoadTextureFromImage(ga.starImage[STAR_8]);
	ga.starTexture[STAR_9] = LoadTextureFromImage(ga.starImage[STAR_9]);
	ga.starTexture[STAR_10] = LoadTextureFromImage(ga.starImage[STAR_10]);

	// THE IMAGE PUZZLE
	ga.myPuzzleImage;
	ga.myPuzzleTexture;

	// Font
	ga.myFontLarge = LoadFontEx("Resources/Font/The Bomb Sound.ttf", fontSizeLarge, nullptr, 0);
	ga.myFontSmall = LoadFontEx("Resources/Font/The Bomb Sound.ttf", fontSizeSmall, nullptr, 0);

	// Text to Image
	// Choose Image Scene
	ga.icon1 = "";
	ga.icon2 = "";
	ga.icon3 = "";

	ga.txt_ChooseImage = ImageTextEx(ga.myFontLarge, "Choose Image", fontSizeLarge, fontSpacing, BLACK);
	ga.txt_ChooseImage_texture = LoadTextureFromImage(ga.txt_ChooseImage);
	ga.puzImg1Txt = ImageTextEx(ga.myFontLarge, "Ray of Colors", fontSizeLarge, fontSpacing, BLACK);
	ga.puzImg1Txt_texture = LoadTextureFromImage(ga.puzImg1Txt);
	ga.puzImg2Txt = ImageTextEx(ga.myFontLarge, "Rubber Tangle", fontSizeLarge, fontSpacing, BLACK);
	ga.puzImg2Txt_texture = LoadTextureFromImage(ga.puzImg2Txt);
	ga.puzImg3Txt = ImageTextEx(ga.myFontLarge, "Inline Pipes", fontSizeLarge, fontSpacing, BLACK);
	ga.puzImg3Txt_texture = LoadTextureFromImage(ga.puzImg3Txt);

	// Slice Image Scene
	ga.txt_SliceImage = ImageTextEx(ga.myFontLarge, "Slice Image", fontSizeLarge, fontSpacing, BLACK);
	ga.txt_SliceImage_texture = LoadTextureFromImage(ga.txt_SliceImage);

	// Pause Scene
	ga.txt_Paused = ImageTextEx(ga.myFontLarge, "Paused", fontSizeLarge, fontSpacing, BLACK);
	ga.txt_Paused_texture = LoadTextureFromImage(ga.txt_Paused);

	// Win Scene
	ga.ptime = "";
	ga.pmove = "";
	ga.ph1 = "";
	ga.ph2 = "";

	// ================================================================================

	// Audio
	ga.menuMusic = LoadMusicStream("Resources/Audio/music1.mp3");
	ga.playMusic = LoadMusicStream("Resources/Audio/music2.mp3");
	ga.solvedSound = LoadSound("Resources/Audio/sound1.mp3");
	ga.slideSound = LoadSound("Resources/Audio/sound2.wav");
	ga.selectSound = LoadSound("Resources/Audio/sound3.wav");
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
	hint1.load(LoadImage("Resources/Images/tog_h1_up.png"), LoadImage("Resources/Images/tog_h1_down.png"), LoadImage("Resources/Images/tog_h1_disabled.png"), MEDIUM, true, 120.0f);
	hint2.load(LoadImage("Resources/Images/tog_h2_up.png"), LoadImage("Resources/Images/tog_h2_down.png"), LoadImage("Resources/Images/tog_h2_disabled.png"), MEDIUM, true, 30.0f);

	// Pause Scene
	resumeButton.load(LoadImage("Resources/Images/res_button_up.png"), LoadImage("Resources/Images/res_button_down.png"), MEDIUM);
	menuButton.load(LoadImage("Resources/Images/menu_button_up.png"), LoadImage("Resources/Images/menu_button_down.png"), MEDIUM);

	// Win Scene
	retryButton.load(LoadImage("Resources/Images/retry_button_up.png"), LoadImage("Resources/Images/retry_button_down.png"), MEDIUM);
}

void UnloadAssets()
{
	// Temp
	//if (ga.tempImage.data != nullptr)
	//	ga.tempImage = {};
	
	// Background contents
	UnloadImage(ga.myBgImage);
	UnloadTexture(ga.myBgTexture);
	UnloadImage(ga.myBgBlankImage);
	UnloadTexture(ga.myBgBlankTexture);

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
	// Stars
	UnloadImage(ga.starImage[STAR_0]);
	UnloadImage(ga.starImage[STAR_3]);
	UnloadImage(ga.starImage[STAR_4]);
	UnloadImage(ga.starImage[STAR_5]);
	UnloadImage(ga.starImage[STAR_6]);
	UnloadImage(ga.starImage[STAR_7]);
	UnloadImage(ga.starImage[STAR_8]);
	UnloadImage(ga.starImage[STAR_9]);
	UnloadImage(ga.starImage[STAR_10]);
	UnloadTexture(ga.starTexture[STAR_0]);
	UnloadTexture(ga.starTexture[STAR_3]);
	UnloadTexture(ga.starTexture[STAR_4]);
	UnloadTexture(ga.starTexture[STAR_5]);
	UnloadTexture(ga.starTexture[STAR_6]);
	UnloadTexture(ga.starTexture[STAR_7]);
	UnloadTexture(ga.starTexture[STAR_8]);
	UnloadTexture(ga.starTexture[STAR_9]);
	UnloadTexture(ga.starTexture[STAR_10]);

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
	UnloadSound(ga.selectSound);


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
	gA::hint2.unloadImage();
	gA::hint2.unloadTexture();

	// Pause Scene
	gA::resumeButton.unloadImage();
	gA::resumeButton.unloadTexture();
	gA::menuButton.unloadImage();
	gA::menuButton.unloadTexture();

	// Win Scene
	gA::retryButton.unloadImage();
	gA::retryButton.unloadTexture();
}