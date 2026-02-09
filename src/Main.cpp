#include "animation.h"
#include "assets.h"
#include "image_puzzle.h"
#include "scene_management.h"
#include "texture_location.h"
#include "transform.h"
#include "user_controls.h"

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <raylib.h>

const char* toText(int num)
{
	static std::string buf;
	buf = std::to_string(num);
	return buf.c_str();
}

// Temporary
Vector2 myString(const std::string& str)
{
	Vector2 strSize = MeasureTextEx(ga.myFontSmall, str.c_str(), fontSizeSmall, fontSpacing);
	return strSize;
}

int main()
{
	// Initialize window
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "PuzzleDePizzle");
	
	//SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowMinSize(screenWidth, screenHeight);
	MaximizeWindow();
	SetTargetFPS(60);

	// Init Audio device
	InitAudioDevice();
	SetMasterVolume(1.0f);
	
	// Initialize all assets
	LoadAssets();
	gA::LoadClassedAssets();

	PlayMusicStream(ga.menuMusic);
	while (!WindowShouldClose() && !Game::isExited())
	{
		// THE FRAMES
		Game::updateFrame();

		// MouseClickLocation
		gc.clickLocation = GetMousePosition();
		Vector2 livemouse = GetMouseDelta();
		std::string mouseX = std::to_string(gc.clickLocation.x);
		std::string mouseY = std::to_string(gc.clickLocation.y);
		const char* mX = mouseX.c_str();
		const char* mY = mouseY.c_str();

		// Resize the texture and maintain quality if the screen dimension is updated
		transformTextures();

		// Get the texture shapes and location
		getShapes();

		// Keyboard controls for the system
		UserControls::systemControls();

		// Functions and behaviors inside scenes
		sceneFunctions();

		// DISPLAY EVERYTHING HERE NOW
		BeginDrawing();
		ClearBackground(BLACK);

		// The background image
		DrawTexture(ga.myBgTexture, tl.bg.x, tl.bg.y, RAYWHITE);
		// The background border
		DrawTexture(ga.myBgBorderTexture[0], tl.bg.x, tl.bg.y - ga.myBgBorderTexture[0].height, WHITE);
		DrawTexture(ga.myBgBorderTexture[0], tl.bg.x, (tl.bg.y + tl.bg.height), WHITE);
		DrawTexture(ga.myBgBorderTexture[1], tl.bg.x - ga.myBgBorderTexture[1].width, tl.bg.y, WHITE);
		DrawTexture(ga.myBgBorderTexture[1], (tl.bg.x + tl.bg.width), tl.bg.y, WHITE);

		//DrawText(mX, 0, 0, fontSizeSmall, GRAY);
		//DrawText(mY, 0, 30, fontSizeSmall, GRAY);

		switch (gc.currentScene)
		{
			case Scene::MENU_SCENE: 
			{
				// Title 
				DrawTexture(ga.myTitleTexture, tl.title.x, tl.title.y, WHITE);

				// Temporary
				DrawTextEx(ga.myFontSmall, "Game by:", { tl.bg.x + tl.bg.width - myString("Game by:").x, tl.bg.y + tl.bg.height - (fontSizeSmall * 2) }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, "Frankrev", { tl.bg.x + tl.bg.width - myString("Frankrev").x, tl.bg.y + tl.bg.height - fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);

				// Buttons
				gA::playButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::playButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) }, gc.clickLocation);
				gA::exitButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::exitButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) + (gA::playButton.getButtonHeight() * 1.1f) }, gc.clickLocation);
				gA::musicButton.draw({ tl.bg.x, (tl.bg.height - (gA::musicButton.getButtonHeight()))}, gc.clickLocation);
				gA::soundButton.draw({ tl.bg.x + (gA::soundButton.getButtonWidth() * 1.1f), (tl.bg.height - (gA::soundButton.getButtonHeight()))}, gc.clickLocation);
			} break;

			case Scene::CHOOSE_IMAGE_SCENE: 
			{
				//DrawTexture(ga.myBgTextureOverlay, tl.bg_o.x, tl.bg_o.y, WHITE);
				DrawRectangleRounded({ tl.bg_o.x, tl.bg_o.y, tl.bg_o.width, tl.bg_o.height }, 0.1f, 1, Fade(BLACK, 0.5f));

				gA::backButton.draw({ (tl.bg.x) * 1.04f, tl.bg.y + 10.0f }, gc.clickLocation);
				gA::folderButton.draw({ (tl.bg.x + tl.bg.width) * 0.9f, tl.bg.y + 10.0f }, gc.clickLocation);

				// Rectangle selection
				if (CheckCollisionPointRec(gc.clickLocation, tl.icon1sel)) {
					DrawRectangleRec(tl.icon1sel, SKYBLUE);
					gc.puz1hover = true;
				}
				else if (CheckCollisionPointRec(gc.clickLocation, tl.icon2sel)) 
				{
					DrawRectangleRec(tl.icon2sel, YELLOW);
					gc.puz2hover = true;
				}
				else if (CheckCollisionPointRec(gc.clickLocation, tl.icon3sel)) 
				{
					DrawRectangleRec(tl.icon3sel, GREEN);
					gc.puz3hover = true;
				}
				else {
					gc.puz1hover = false;
					gc.puz2hover = false;
					gc.puz3hover = false;
				}
				
				// Icons
				DrawTexture(ga.puzzleImage1Texture, tl.icon1.x, tl.icon1.y, WHITE);
				DrawTexture(ga.puzzleImage2Texture, tl.icon3.x, tl.icon2.y, WHITE);
				DrawTexture(ga.puzzleImage3Texture, tl.icon3.x, tl.icon3.y, WHITE);
				
				// Texts
				DrawTexture(ga.txt_ChooseImage_texture, 
							tl.bg_o.x + (tl.bg_o.width / 2) - (ga.txt_ChooseImage_texture.width / 2.0f), 
							tl.bg_o.y - (ga.txt_ChooseImage_texture.height / 2.0f), 
							BLACK);
				DrawTexture(ga.puzImg1Txt_texture, 
							(tl.bg_o.x + (tl.bg_o.width / 2.0f)), 
							(tl.icon1.y + (tl.icon1.height / 2.0f)) - (ga.puzImg1Txt_texture.height / 2.0f), 
							BLACK);
				DrawTexture(ga.puzImg2Txt_texture, 
							(tl.bg_o.x + (tl.bg_o.width / 2.0f)), 
							(tl.icon2.y + (tl.icon2.height / 2.0f)) - (ga.puzImg2Txt_texture.height / 2.0f), 
							BLACK);
				DrawTexture(ga.puzImg3Txt_texture, 
							(tl.bg_o.x + (tl.bg_o.width / 2.0f)), 
							(tl.icon3.y + (tl.icon3.height / 2.0f)) - (ga.puzImg3Txt_texture.height / 2.0f), 
							BLACK);
			} break;

			case Scene::CROP_SLICE_IMAGE_SCENE: 
			{
				//DrawTexture(ga.myBgTextureOverlay, tl.bg_o.x, tl.bg_o.y, WHITE);
				DrawRectangleRounded({ tl.bg_o.x, tl.bg_o.y, tl.bg_o.width, tl.bg_o.height }, 0.1f, 1, Fade(BLACK, 0.5f));
				DrawTexture(ga.txt_SliceImage_texture, 
							tl.bg_o.x + (tl.bg_o.width / 2) - (ga.txt_SliceImage_texture.width / 2.0f), 
							tl.bg_o.y - (ga.txt_SliceImage_texture.height / 2.0f), 
							BLACK);

				gA::backButton.draw({ (tl.bg.x) * 1.04f, tl.bg.y + 10.0f }, gc.clickLocation);
				gA::startButton.draw({ (tl.bg.x + tl.bg.width) * 1.0f - (gA::startButton.getButtonWidth() * 1.04f), tl.bg.y + 10.0f }, gc.clickLocation);

				gA::subButton.draw({ tl.bg_o.x + (tl.bg_o.width / 2.0f) - (gA::subButton.getButtonWidth() + 10.0f), (tl.bg_o.y + tl.bg_o.height)}, gc.clickLocation);
				gA::plusButton.draw({ tl.bg_o.x + (tl.bg_o.width / 2.0f) + 10.0f, (tl.bg_o.y + tl.bg_o.height) }, gc.clickLocation);

				if (ga.myPuzzleTexture.id != 0) {
					// Draw texture in the middle of the screen
					DrawTexture(ga.myPuzzleTexture, tl.p_image.x, tl.p_image.y, WHITE);
				}
				gc.puz1hover = false;
				gc.puz2hover = false;
				gc.puz3hover = false;

				for (const auto& r : sl.rec) {
					DrawRectangleLinesEx(r, 1.0f, GRAY);
				}

			} break;

			case Scene::BEGIN_PLAY_SCENE:
			{
				// Initialize keyboard game controls
				if (!Puzzle::isSolved())
					UserControls::userControls();

				// BG Overlay
				DrawRectangleRounded({ tl.bg_o.x, tl.bg_o.y, tl.bg_o.width, tl.bg_o.height }, 0.1f, 1, Fade(BLACK, 0.5f));
				// Buttons
				gA::pauseButton.draw({ (tl.bg.x + tl.bg.width) * 0.9f, tl.bg.y + 10.0f }, gc.clickLocation);
				gA::hint1.draw({ tl.bg_o.x + (tl.bg_o.width / 2.0f) - (gA::hint1.getButtonWidth() + 10.0f), (tl.bg_o.y + tl.bg_o.height) }, gc.clickLocation);
				gA::hint2.draw({ tl.bg_o.x + (tl.bg_o.width / 2.0f) + 10.0f, (tl.bg_o.y + tl.bg_o.height) }, gc.clickLocation);

				// Puzzle blank space
				DrawRectangle(tl.p_image.x, tl.p_image.y, tl.p_image.width, tl.p_image.height, BLACK);
				// The puzzle image
				for (int i = 0; i < (int)Puzzle::puzzleTexture.size(); ++i) {
				    if (i == Puzzle::blankIndex) continue; // **important**
					// Draw the tiles
				    DrawTexture(Puzzle::puzzleTexture[i], sl.rec[i].x, sl.rec[i].y, WHITE);
					// if Hint 1 used (puzzle guide numbers appear so only in puzzle grid loop will draw)
					if (gA::hint1.isToggled()) {
						Vector2 textSize = MeasureTextEx(ga.myFontSmall, toText(Puzzle::puz_guide[i]), fontSizeSmall - 5, fontSpacing);
						DrawRectangle(sl.rec[i].x, sl.rec[i].y, textSize.x + 5, textSize.y, FadeState::tintOut(BLACK, RECTANGLE));
						DrawTextEx(ga.myFontSmall, toText(Puzzle::puz_guide[i]), {sl.rec[i].x, sl.rec[i].y}, fontSizeSmall, fontSpacing, FadeState::tintOut(WHITE, TEXT));
					}
				}

				// if Hint 1 used
				if (gA::hint1.isToggled()) {
					DrawTextEx(ga.myFontSmall, toText(gA::hint1.getDuration() + 1), { tl.bg_o.x + (tl.bg_o.width / 2.0f) - (gA::hint1.getButtonWidth() + 10.0f), (tl.bg_o.y + tl.bg_o.height) }, fontSizeSmall, fontSpacing, WHITE);
				}
				// if Hint 2 used
				if (gA::hint2.isToggled()) {
					DrawTexture(ga.myPuzzleTexture, tl.p_image.x, tl.p_image.y, FadeState::tintOut(WHITE, TEXTURE));
					DrawTextEx(ga.myFontSmall, toText(gA::hint2.getDuration() + 1), { tl.bg_o.x + (tl.bg_o.width / 2.0f) + 10.0f, (tl.bg_o.y + tl.bg_o.height) }, fontSizeSmall, fontSpacing, WHITE);
				}

				// Tile outline
				for (const auto& r : sl.rec)
					DrawRectangleLinesEx(r, 1.0f, BLACK);

				// The timer and counter label
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::timerLabel, { tl.bg.x, tl.bg.y }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::moveLabel, { tl.bg.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::h1Label, { tl.bg.x, tl.bg.height - fontSizeSmall * 2 }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::h2Label, { tl.bg.x, tl.bg.height - fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);

				// Get Frame Time (Timer)
				Puzzle::Timer::elapsedTime += Game::getFrame();
				if (Puzzle::Timer::elapsedTime >= 1.0f && !Puzzle::isSolved()) {
					++Puzzle::Timer::totalSeconds;
					Puzzle::Timer::elapsedTime -= 1.0f;
				}

				// The timer and counter itself
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::get(), { tl.bg.x + Puzzle::Timer::timerLabelSize.x, tl.bg.y }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::move), { tl.bg.x + Puzzle::Counter::moveLabelSize.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::h1), { tl.bg.x + Puzzle::Counter::h1LabelSize.x, tl.bg.height - fontSizeSmall * 2 }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::h2), { tl.bg.x + Puzzle::Counter::h2LabelSize.x, tl.bg.height - fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);

				// Check puzzle state
				Puzzle::check();
				if (Puzzle::isSolved()) {
					// Clear the frame time
					Puzzle::Timer::elapsedTime = 0.0f;
					FadeState::Update();
					DrawRectangle(tl.p_image.x, tl.p_image.y, tl.p_image.width, tl.p_image.height, FadeState::getTint(WHITE));
					DrawTexture(ga.myPuzzleTexture, tl.p_image.x, tl.p_image.y, FadeState::getTint(WHITE));
					// Wait to win scene
					Delay::Update();
				}

			} break;

			case Scene::PAUSE_SCENE:
			{
				// Time count and move paused
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::timerLabel, { tl.bg.x, tl.bg.y }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::moveLabel, { tl.bg.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::get(), {tl.bg.x + Puzzle::Timer::timerLabelSize.x, tl.bg.y}, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::move), { tl.bg.x + Puzzle::Counter::moveLabelSize.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);

				DrawTexture(ga.txt_Paused_texture, 
							tl.bg_o.x + (tl.bg_o.width / 2) - (ga.txt_Paused_texture.width / 2.0f), 
							tl.bg_o.y + (ga.txt_Paused_texture.height * 2.0f), 
							BLACK);

				gA::resumeButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::resumeButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) }, gc.clickLocation);
				gA::menuButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::menuButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) + (gA::resumeButton.getButtonHeight() * 1.1f) }, gc.clickLocation);
			} break;

			case Scene::WIN_SCENE:
			{
				DrawRectangle(tl.bg.x, tl.bg.y, tl.bg.width, tl.bg.height, Fade(BLACK, 0.7f));
				gA::retryButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::retryButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) }, gc.clickLocation);
				gA::menuButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::menuButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) + (gA::resumeButton.getButtonHeight() * 1.1f) }, gc.clickLocation);

			} break;
		}

		EndDrawing();
	}

	UnloadAssets();

	CloseAudioDevice();

	CloseWindow();

	return 0;
}