#include "scene_management.h"

void sceneFunctions()
{
	// SCENE 1
	if (gc.currentScene == Scene::MENU_SCENE) {
		// Scene 1-2 switch
		if (gA::playButton.isPressed()) {
			gc.currentScene = Scene::CHOOSE_IMAGE_SCENE;
		}
		// Exit
		if (gA::exitButton.isPressed()) {
			Game::exited = true;
		}

		// Scene 1 actions
		if (!gA::musicButton.isToggled()) {
			UpdateMusicStream(ga.menuMusic);
			ResumeMusicStream(ga.menuMusic);
		}
		else {
			PauseMusicStream(ga.menuMusic);
		}
	}

	// SCENE 2
	if (gc.currentScene == Scene::CHOOSE_IMAGE_SCENE) {
		// Scene 2-1 switch
		if (gA::backButton.isPressed()) {
			if (ga.myPuzzleTexture.id != 0)
				UnloadTexture(ga.myPuzzleTexture);
			gc.currentScene = Scene::MENU_SCENE;
		}
		// Scene 2-3 switch
		// Icon 1
		if (gc.puz1hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			theImagePuzzle(ga.myPuzzleImage, ga.puzzleImage1, ga.myPuzzleTexture);
			gc.currentScene = Scene::CROP_SLICE_IMAGE_SCENE;
			}
		// Icon 2
		if (gc.puz2hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			theImagePuzzle(ga.myPuzzleImage, ga.puzzleImage2, ga.myPuzzleTexture);
			gc.currentScene = Scene::CROP_SLICE_IMAGE_SCENE;
		}
		// Icon 3
		if (gc.puz3hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			theImagePuzzle(ga.myPuzzleImage, ga.puzzleImage3, ga.myPuzzleTexture);
			gc.currentScene = Scene::CROP_SLICE_IMAGE_SCENE;
		}
		// Folder button open
		if (gA::folderButton.isPressed()) {
			const char* filepath = tinyfd_openFileDialog("Select an Image",	"",	3, FILTER, "Image files", 0);

			if (filepath) {
				if (ga.myPuzzleTexture.id != 0) {
					UnloadTexture(ga.myPuzzleTexture);
				}

				ga.myPuzzleImage = LoadImage(filepath);
				ga.myPuzzleTexture = LoadTextureFromImage(imageManipulate(&ga.myPuzzleImage, IMAGE_AS_PUZZLE));
				gc.currentScene = Scene::CROP_SLICE_IMAGE_SCENE;
			}
		}

		// Actions from other previous scenes
		if (!gA::musicButton.isToggled()) {
			UpdateMusicStream(ga.menuMusic);
			ResumeMusicStream(ga.menuMusic);
		}
		else {
			PauseMusicStream(ga.menuMusic);
		}
	}

	// SCENE 3
	if (gc.currentScene == Scene::CROP_SLICE_IMAGE_SCENE) {
		// Scene 3-2 switch
		if (gA::backButton.isPressed()) {
			if (ga.myPuzzleTexture.id != 0) {
				UnloadTexture(ga.myPuzzleTexture);
			}
			gc.currentScene = Scene::CHOOSE_IMAGE_SCENE;
		}

		// Scene 3-4 switch
		if (gA::startButton.isPressed()) {
			Puzzle::loadPuzzle(ga.myPuzzleImage, sl.puz);
			Puzzle::finalizeLoad();
			StopMusicStream(ga.menuMusic);
			gc.currentScene = Scene::BEGIN_PLAY_SCENE;
			PlayMusicStream(ga.playMusic);
		}
		// Scene 3 actions
		if (gA::plusButton.isPressed()) {
			sl.slice++;
		}
		if (gA::subButton.isPressed()) {
			sl.slice--;
		}
		// Slice the image
		sl.applySlice();

		// Actions from previous scenes
		if (!gA::musicButton.isToggled()) {
			UpdateMusicStream(ga.menuMusic);
			ResumeMusicStream(ga.menuMusic);
		}
	}

	//SCENE 4
	if (gc.currentScene == Scene::BEGIN_PLAY_SCENE) {
		// update the grid everytime when window is resized
		updateSlice();
		// Scene 4-5 switch
		if (gA::pauseButton.isPressed()) {
			gc.currentScene = Scene::PAUSE_SCENE;
		}
		// Scene 4-6 switch (delayed)
		if (Delay::timeTarget == 3.0f) {
			gc.currentScene = Scene::WIN_SCENE;
		}

		gA::hint1.handleInput();

		// Scene 4 actions
		if (gA::hint1.isToggled()) {
			// 14 seconds before the guide hint disappears
			FadeState::Out();
			// 60 seconds before the hint guide enables again
			gA::hint1.update();
		}

		// Actions from previous scenes
		if (!gA::musicButton.isToggled()) {
			UpdateMusicStream(ga.playMusic);
			ResumeMusicStream(ga.playMusic);
		}
		else {
			PauseMusicStream(ga.playMusic);
		}
	}

	//SCENE 5
	if (gc.currentScene == Scene::PAUSE_SCENE) {
		// Scene 5-4 switch
		if (gA::resumeButton.isPressed()) {
			gc.currentScene = Scene::BEGIN_PLAY_SCENE;
		}
		// Scene 5-1 switch
		if (gA::menuButton.isPressed()) {
			StopMusicStream(ga.playMusic);
			// Destroy the puzzle
			Puzzle::destroy();
			UnloadTexture(ga.myPuzzleTexture);

			// Reset everything
			Delay::Reset();					// reset delay
			FadeState::Reset();				// reset fade animation
			Audio::winSound = true;			// reset win sound

			// Then go to Scene 1
			gc.currentScene = Scene::MENU_SCENE;
			if (gA::musicButton.isToggled()) {
				PauseMusicStream(ga.menuMusic);
			}
			else {
				PlayMusicStream(ga.menuMusic);
			}
		}

		// Actions from previous scenes
		if (!gA::musicButton.isToggled()) {
			UpdateMusicStream(ga.playMusic);
			ResumeMusicStream(ga.playMusic);
		}
		else {
			PauseMusicStream(ga.playMusic);
		}
	}

	//SCENE 6
	if (gc.currentScene == Scene::WIN_SCENE) {
		// Scene 6-4
		if (gA::retryButton.isPressed()) {
			// Rebuild and Re-shuffle the puzzle
			Puzzle::destroy();
			Puzzle::loadPuzzle(ga.myPuzzleImage, sl.puz);
			Puzzle::finalizeLoad();

			// Reset everything
			Delay::Reset();					// reset delay
			FadeState::Reset();				// reset fade animation

			// Then back to the Play Scene
			gc.currentScene = Scene::BEGIN_PLAY_SCENE;
		}
		// Scene 6-1 switch
		if (gA::menuButton.isPressed()) {
			StopMusicStream(ga.playMusic);
			// Destroy the puzzle
			Puzzle::destroy();
			UnloadTexture(ga.myPuzzleTexture);

			// Then go to Scene 1
			gc.currentScene = Scene::MENU_SCENE;
			if (gA::musicButton.isToggled()) {
				PauseMusicStream(ga.menuMusic);
			}
			else {
				PlayMusicStream(ga.menuMusic);
			}
		}

		// Actions from previous scenes
		if (!gA::musicButton.isToggled()) {
			UpdateMusicStream(ga.playMusic);
			ResumeMusicStream(ga.playMusic);
		}
		else {
			PauseMusicStream(ga.playMusic);
		}
	}
}