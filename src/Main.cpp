#include "animation.h"
#include "assets.h"
#include "image_puzzle.h"
#include "scene_management.h"
#include "texture_location.h"
#include "transform.h"
#include "user_controls.h"

#include <cmath>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <raylib.h>

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
	
	SetWindowMinSize(screenWidth, screenHeight);
	//MaximizeWindow();
	SetTargetFPS(60);

	// Init Audio device
	InitAudioDevice();
	SetMasterVolume(1.0f);
	
	// Initialize all assets
	LoadAssets();
	gA::LoadClassedAssets();
	gc.fontScaled = getScaledFont(GetScreenWidth(), GetScreenHeight());


	// Check if puzzle has records
	if (!Puzzle::isSolved() /* Or if the puzzle has no records at all in user.dat file */)
	{
		gA::puz[PUZ_1].setStar((int)StarRate::STAR_0);
		gA::puz[PUZ_2].setStar((int)StarRate::STAR_0);
		gA::puz[PUZ_3].setStar((int)StarRate::STAR_0);
	}
	else
	{
		// gA::puz[PUZ_1].setStar( /* scan the obscured user.dat file for record that has the highest rating (3-10) */); not yet implemented
		// same to gA::puz[PUZ_2], 3, 4, 5, etc.
	}

	// BEGIN
	PlayMusicStream(ga.menuMusic);

	// FOR STAR 10 testing
	int rot = 0;
	int txtrWidth = 0;
	int txtrHeight = 0;
	Rectangle src = {};
	Rectangle dest1 = {};
	Rectangle dest2 = {};
	Rectangle dest3 = {};
	Vector2 org = {};

	while (!WindowShouldClose() && !Game::isExited())
	{
		// UPDATES
		// Frames
		Game::updateFrame();

		// MouseClickLocation
		gc.clickLocation = GetMousePosition();
		Vector2 livemouse = GetMouseDelta();
		std::string mouseX = std::to_string(gc.clickLocation.x);
		std::string mouseY = std::to_string(gc.clickLocation.y);
		const char* mX = mouseX.c_str();
		const char* mY = mouseY.c_str();


		// FOR STAR 10 ONLY
		txtrWidth = ga.starTexture[sl.slice].width;
		txtrHeight = ga.starTexture[sl.slice].height;
		src = { 0.0f, 0.0f, (float)txtrWidth, (float)txtrHeight };
		org = { (float)txtrWidth / 2.0f, (float)txtrHeight / 2.0f };
		if (gc.currentScene == Scene::WIN_SCENE) {
			float newTxtrWidth = txtrWidth;
			float newTxtrHeight = txtrHeight;
			dest1 = { (GetScreenWidth() / 2.0f) + (tl.bg_o.width * 0.20f) + (txtrWidth / 2.0f), (GetScreenHeight() / 2.0f) - (txtrHeight / 2.0f), (float)txtrWidth, (float)txtrHeight};
		}
		if (gc.currentScene == Scene::CHOOSE_IMAGE_SCENE) 
		{
			if (gA::puz[PUZ_1].getStar() == 10)
				dest1 = { (float)(tl.bg_o.x + (tl.bg_o.width * 0.75f)) + tl.icon1.width / 2.0f, (float)tl.icon1.y + (tl.icon1.height / 2.0f), (float)txtrWidth, (float)txtrHeight};
			if (gA::puz[PUZ_2].getStar() == 10)
				dest2 = { (float)(tl.bg_o.x + (tl.bg_o.width * 0.75f)) + tl.icon2.width / 2.0f, (float)tl.icon2.y + (tl.icon2.height / 2.0f), (float)txtrWidth, (float)txtrHeight };
			if (gA::puz[PUZ_3].getStar() == 10)
				dest3 = { (float)(tl.bg_o.x + (tl.bg_o.width * 0.75f)) + tl.icon3.width / 2.0f, (float)tl.icon3.y + (tl.icon3.height / 2.0f), (float)txtrWidth, (float)txtrHeight };
		}

		// Resize the texture and maintain quality if the screen dimension is updated
		transformTextures();

		// Get the texture shapes and location
		getShapes();

		// Functions and behaviors inside scenes
		sceneFunctions();
		if (Puzzle::isSolved() && gc.currentScene == Scene::BEGIN_PLAY_SCENE) 
		{
			// Text results
			textureTransform(ga.myBgBlankImage, ga.myBgBlankTexture, IMAGE_AS_BG);
			textureTransform(ga.starImage[sl.slice], ga.starTexture[sl.slice], IMAGE_AS_ICON);

			// STAR TESTING
			if (gc.puz1selected) {
				gA::puz[PUZ_1].setStar(sl.slice);
				gc.puz1selected = false;
			}
			if (gc.puz2selected) {
				gA::puz[PUZ_2].setStar(sl.slice);
				gc.puz2selected = false;
			}
			if (gc.puz3selected){
				gA::puz[PUZ_3].setStar(sl.slice);
				gc.puz3selected = false;
			}
		}

		// Keyboard controls for the system
		UserControls::systemControls();

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

		DrawText(mX, 0, 0, fontSizeSmall, BLACK);
		DrawText(mY, 0, 30, fontSizeSmall, BLACK);

		switch (gc.currentScene)
		{
			case Scene::MENU_SCENE: 
			{
				// Title 
				DrawTexture(ga.myTitleTexture, tl.title.x, tl.title.y, WHITE);

				// Temporary
				DrawTextEx(ga.myFontSmall, "Game by:", { tl.bg.x + tl.bg.width - myString("Game by:").x, tl.bg.y + tl.bg.height - (fontSizeSmall * 2) }, gc.fontScaled, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, "Frankrev", { tl.bg.x + tl.bg.width - myString("Frankrev").x, tl.bg.y + tl.bg.height - fontSizeSmall }, gc.fontScaled, fontSpacing, BLACK);

				// Buttons
				gA::playButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::playButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) }, gc.clickLocation);
				gA::exitButton.draw({ (gc.currentWindowWidth / 2.0f) - (gA::exitButton.getButtonWidth() / 2.0f), 
									(gc.currentWindowHeight / 1.9f) + (gA::playButton.getButtonHeight() * 1.1f) }, gc.clickLocation);
				gA::musicButton.draw({ tl.bg.x, ((tl.bg.y + tl.bg.height) - gA::musicButton.getButtonHeight())}, gc.clickLocation);
				gA::soundButton.draw({ tl.bg.x + (gA::soundButton.getButtonWidth() * 1.1f), ((tl.bg.y + tl.bg.height) - gA::soundButton.getButtonHeight())}, gc.clickLocation);
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

				// Stars
				if (gA::puz[PUZ_1].getStar() == 10) {
					DrawTexturePro(ga.starTexture[gA::puz[PUZ_1].getStar()], src, dest1, org, rot, Fade(WHITE, gA::puz[PUZ_1].getOpacity()));
				}
				else {
					DrawTexture(ga.starTexture[gA::puz[PUZ_1].getStar()],
						(int)(tl.bg_o.x + (tl.bg_o.width * 0.75f)),
						(int)tl.icon1.y,
						Fade(WHITE, gA::puz[PUZ_1].getOpacity()));
				}
				if (gA::puz[PUZ_2].getStar() == 10) {
					DrawTexturePro(ga.starTexture[gA::puz[PUZ_2].getStar()], src, dest2, org, rot, Fade(WHITE, gA::puz[PUZ_2].getOpacity()));
				}
				else {
					DrawTexture(ga.starTexture[gA::puz[PUZ_2].getStar()],
						(int)(tl.bg_o.x + (tl.bg_o.width * 0.75f)),
						(int)tl.icon2.y,
						Fade(WHITE, gA::puz[PUZ_2].getOpacity()));
				}
				if (gA::puz[PUZ_3].getStar() == 10) {
					DrawTexturePro(ga.starTexture[gA::puz[PUZ_3].getStar()], src, dest3, org, rot, Fade(WHITE, gA::puz[PUZ_3].getOpacity()));
				}
				else {
					DrawTexture(ga.starTexture[gA::puz[PUZ_3].getStar()],
						(int)(tl.bg_o.x + (tl.bg_o.width * 0.75f)),
						(int)tl.icon3.y,
						Fade(WHITE, gA::puz[PUZ_3].getOpacity()));
				}
				rot++;		// rotation
				
				// Icons
				DrawTexture(ga.puzzleImage1Texture, (int)tl.icon1.x, (int)tl.icon1.y, WHITE);
				DrawTexture(ga.puzzleImage2Texture, (int)tl.icon2.x, (int)tl.icon2.y, WHITE);
				DrawTexture(ga.puzzleImage3Texture, (int)tl.icon3.x, (int)tl.icon3.y, WHITE);
				
				// Texts
				DrawTexture(ga.txt_ChooseImage_texture, 
							tl.bg_o.x + (tl.bg_o.width / 2) - (ga.txt_ChooseImage_texture.width / 2.0f), 
							tl.bg_o.y - (ga.txt_ChooseImage_texture.height / 2.0f), 
							BLACK);
				DrawTexture(ga.puzImg1Txt_texture, 
							(tl.bg_o.x + (tl.bg_o.width / 2.0f)) - (ga.puzImg1Txt_texture.width / 2.0f),
							(tl.icon1.y + (tl.icon1.height / 2.0f)) - (ga.puzImg1Txt_texture.height / 2.0f), 
							BLACK);
				DrawTexture(ga.puzImg2Txt_texture, 
							(tl.bg_o.x + (tl.bg_o.width / 2.0f)) - (ga.puzImg2Txt_texture.width / 2.0f),
							(tl.icon2.y + (tl.icon2.height / 2.0f)) - (ga.puzImg2Txt_texture.height / 2.0f), 
							BLACK);
				DrawTexture(ga.puzImg3Txt_texture, 
							(tl.bg_o.x + (tl.bg_o.width / 2.0f)) - (ga.puzImg3Txt_texture.width / 2.0f),
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
				DrawRectangle((int)tl.p_image.x, (int)tl.p_image.y, (int)ga.myPuzzleTexture.width, (int)ga.myPuzzleTexture.height, BLACK);

				// The puzzle image
				for (int i = 0; i < (int)Puzzle::puzzleTexture.size(); ++i) 
				{
				    if (i == Puzzle::blankIndex) continue; // **important**

					// Draw the tiles
				    DrawTexture(Puzzle::puzzleTexture[i], (int)sl.rec[i].x, (int)sl.rec[i].y, WHITE);

					// if Hint 1 used (puzzle guide numbers appear so only in puzzle grid loop will draw)
					if (gA::hint1.isToggled()) {
						Vector2 textSize = MeasureTextEx(ga.myFontSmall, toText(Puzzle::puz_guide[i]), fontSizeSmall - 5, fontSpacing);
						float rawX = sl.rec[i].x + sl.rec[i].width * 0.5f - textSize.x * 0.5f;
						float rawY = sl.rec[i].y + sl.rec[i].height * 0.5f - textSize.y * 0.5f;
						auto snappedX = static_cast<int>(rawX);
						auto snappedY = static_cast<int>(rawY);
						// Text guide shadow
						DrawTextEx(ga.myFontSmall, toText(Puzzle::puz_guide[i]), { (float)snappedX, (float)snappedY }, fontSizeSmall + 3, fontSpacing, FadeState::tintOut(BLACK, TEXT));
						// Text guide
						DrawTextEx(ga.myFontSmall, toText(Puzzle::puz_guide[i]), { (float)snappedX, (float)snappedY }, fontSizeSmall, fontSpacing, FadeState::tintOut(WHITE, TEXT));
					}
				}

				// if Hint 1 used
				if (gA::hint1.isToggled()) {
					DrawTextEx(ga.myFontSmall, toText(gA::hint1.getDuration() + 1), { tl.bg_o.x + (tl.bg_o.width / 2.0f) - (gA::hint1.getButtonWidth() + 10.0f), (tl.bg_o.y + tl.bg_o.height) }, fontSizeSmall, fontSpacing, WHITE);
				}
				// if Hint 2 used
				if (gA::hint2.isToggled()) {
					DrawTexture(ga.myPuzzleTexture, (int)((gc.currentWindowWidth / 2.0f) - (ga.myPuzzleTexture.width / 2.0f)),
						(int)((gc.currentWindowHeight / 2.0f) - (ga.myPuzzleTexture.height / 2.0f)),
						FadeState::tintOut(WHITE, TEXTURE));
					DrawTextEx(ga.myFontSmall, toText(gA::hint2.getDuration() + 1), { tl.bg_o.x + (tl.bg_o.width / 2.0f) + 10.0f, (tl.bg_o.y + tl.bg_o.height) }, fontSizeSmall, fontSpacing, WHITE);
				}

				// Tile outline (outside the puzzle so that it can include the solved texture hint 2 and its tile position visualization)
				for (int i{ 0 }; i < (int)Puzzle::puzzleTexture.size(); ++i) 
				{
					DrawRectangleLines((int)sl.rec[i].x, (int)sl.rec[i].y, (int)sl.rec[i].width, (int)sl.rec[i].height, BLACK);
				}

				// The timer and counter 
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::timerLabel, { tl.bg.x, tl.bg.y }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::moveLabel, { tl.bg.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::h1Label, { tl.bg.x, (tl.bg.y + tl.bg.height) - fontSizeSmall * 2 }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::h2Label, { tl.bg.x, (tl.bg.y + tl.bg.height) - fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::get(), { tl.bg.x + Puzzle::Timer::timerLabelSize.x, tl.bg.y }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::move), { tl.bg.x + Puzzle::Counter::moveLabelSize.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::h1), { tl.bg.x + Puzzle::Counter::h1LabelSize.x, (tl.bg.y + tl.bg.height) - fontSizeSmall * 2}, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::h2), { tl.bg.x + Puzzle::Counter::h2LabelSize.x, (tl.bg.y + tl.bg.height) - fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);

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
				// Timer and counter paused
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::timerLabel, { tl.bg.x, tl.bg.y }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Timer::get(), {tl.bg.x + Puzzle::Timer::timerLabelSize.x, tl.bg.y}, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::moveLabel, { tl.bg.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::move), { tl.bg.x + Puzzle::Counter::moveLabelSize.x, tl.bg.y + fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::h1Label, { tl.bg.x, (tl.bg.y + tl.bg.height) - fontSizeSmall * 2}, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, Puzzle::Counter::h2Label, { tl.bg.x, (tl.bg.y + tl.bg.height) - fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::h1), { tl.bg.x + Puzzle::Counter::h1LabelSize.x, (tl.bg.y + tl.bg.height) - fontSizeSmall * 2 }, fontSizeSmall, fontSpacing, BLACK);
				DrawTextEx(ga.myFontSmall, toText(Puzzle::Counter::h2), { tl.bg.x + Puzzle::Counter::h2LabelSize.x, (tl.bg.y + tl.bg.height) - fontSizeSmall }, fontSizeSmall, fontSpacing, BLACK);

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
				DrawTexture(ga.myBgBlankTexture, tl.bg.x, tl.bg.y, WHITE);			// Puzzle results are drawn here

				if (sl.slice == 10) {
					DrawTexturePro(ga.starTexture[sl.slice], src, dest1, org, rot, Fade(WHITE, Puzzle::getPercent(Puzzle::Counter::totalHint)));
					rot++;
				}
				else {
					DrawTexturePro(ga.starTexture[sl.slice], src, dest1, org, 0.0f, Fade(WHITE, Puzzle::getPercent(Puzzle::Counter::totalHint)));
				}

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