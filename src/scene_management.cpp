#include "scene_management.h"

void sceneMusic(Music& music)
{
	if (gA::musicButton.isToggled()) {
		PauseMusicStream(music);
	}
	else {
		ResumeMusicStream(music);
		UpdateMusicStream(music);
	}
}

void sceneSound(Sound& sound)
{
	if (gA::soundButton.isToggled()) {
		StopSound(sound);
	}
	else
		PlaySound(sound);
}

void sceneFunctions()
{
	// SCENE 1
	if (gc.currentScene == Scene::MENU_SCENE) {
		// Scene Audio
		sceneMusic(ga.menuMusic);

		// Scene 1-2 switch
		if (gA::playButton.isPressed()) {
			sceneSound(ga.selectSound);
			gc.currentScene = Scene::CHOOSE_IMAGE_SCENE;
		}
		// Exit
		if (gA::exitButton.isPressed()) {
			sceneSound(ga.selectSound);
			Game::exited = true;
		}
	}

	// SCENE 2
	if (gc.currentScene == Scene::CHOOSE_IMAGE_SCENE) {
		// Scene Music
		sceneMusic(ga.menuMusic);
		
		// Scene 2-1 switch
		if (gA::backButton.isPressed()) {
			sceneSound(ga.selectSound);
			if (ga.myPuzzleTexture.id != 0)
				UnloadTexture(ga.myPuzzleTexture);
			gc.currentScene = Scene::MENU_SCENE;
		}
		// Scene 2-3 switch
		// Icon 1
		if (gc.puz1hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			sceneSound(ga.selectSound);
			theImagePuzzle(ga.myPuzzleImage, ga.puzzleImage1, ga.myPuzzleTexture);
			gc.puz1selected = true;
			gc.currentScene = Scene::CROP_SLICE_IMAGE_SCENE;
		}
		// Icon 2
		if (gc.puz2hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			sceneSound(ga.selectSound);
			theImagePuzzle(ga.myPuzzleImage, ga.puzzleImage2, ga.myPuzzleTexture);
			gc.puz2selected = true;
			gc.currentScene = Scene::CROP_SLICE_IMAGE_SCENE;
		}
		// Icon 3
		if (gc.puz3hover && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			sceneSound(ga.selectSound);
			theImagePuzzle(ga.myPuzzleImage, ga.puzzleImage3, ga.myPuzzleTexture);
			gc.puz3selected = true;
			gc.currentScene = Scene::CROP_SLICE_IMAGE_SCENE;
		}

		// Folder button open
		if (gA::folderButton.isPressed()) {
			sceneSound(ga.selectSound);
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
	}

	// SCENE 3
	if (gc.currentScene == Scene::CROP_SLICE_IMAGE_SCENE) {
		// Scene Music
		sceneMusic(ga.menuMusic);

		// Scene 3-2 switch
		if (gA::backButton.isPressed()) {
			sceneSound(ga.selectSound);
			if (ga.myPuzzleTexture.id != 0) {
				UnloadTexture(ga.myPuzzleTexture);
			}
			gc.currentScene = Scene::CHOOSE_IMAGE_SCENE;
		}

		// Scene 3-4 switch
		if (gA::startButton.isPressed()) {
			sceneSound(ga.selectSound);
			Puzzle::loadPuzzle(ga.myPuzzleImage, sl.puz);
			Puzzle::finalizeLoad();
			StopMusicStream(ga.menuMusic);
			gc.currentScene = Scene::BEGIN_PLAY_SCENE;
			PlayMusicStream(ga.playMusic);
		}
		// Scene 3 actions
		if (gA::plusButton.isPressed()) {
			sceneSound(ga.selectSound);
			sl.slice++;
		}
		if (gA::subButton.isPressed()) {
			sceneSound(ga.selectSound);
			sl.slice--;
		}
		// Slice the image
		sl.applySlice();
	}

	//SCENE 4
	if (gc.currentScene == Scene::BEGIN_PLAY_SCENE) {
		// Scene Updates
		sceneMusic(ga.playMusic);
		updateSlice();			// update the grid everytime when window is resized
		Puzzle::update();		// update puzzle state (e.g. timer, hint counter)
		// Scene 4-5 switch
		if (gA::pauseButton.isPressed()) {
			sceneSound(ga.selectSound);
			gc.currentScene = Scene::PAUSE_SCENE;
		}
		// Scene 4-6 switch (delayed)
		if (Delay::timeTarget == 4.0f) {
			gc.currentScene = Scene::WIN_SCENE;
		}

		//gA::hint1.handleInput();
		//gA::hint2.handleInput();
		if (gA::hint1.getDuration() == 0.0f) {
			gA::hint1.resetToggle();
			gA::hint1.resetDisable();
			gA::hint1.resetRemaining();
			FadeState::alphaOutText = 1.0f;
			FadeState::alphaOutRec = 1.0f;
		}
		if (gA::hint2.getDuration() == 0.0f) {
			gA::hint2.resetToggle();
			gA::hint2.resetDisable();
			gA::hint2.resetRemaining();
			FadeState::alphaOutTexture = 0.9f;
		}

		// Scene 4 actions
		if (gA::hint1.isPressed()) {
			++Puzzle::Counter::h1;
			sceneSound(ga.selectSound);
		}
		if (gA::hint2.isPressed()) {
			++Puzzle::Counter::h2;
			sceneSound(ga.selectSound);
		}

		if (gA::hint1.isToggled()) {
			FadeState::Out(14, RECTANGLE);
			FadeState::Out(14, TEXT);	// 14 seconds before the guide hint disappears
			gA::hint1.update();			// 120 seconds before the hint 2 enables again
		}
		if (gA::hint2.isToggled()) {
			FadeState::Out(5, TEXTURE);
			gA::hint2.update();			// 30 seconds before the hint 2 enables again
		}

		// Scene 4 updates
		if (Puzzle::isSolved()) {
			saveScore();
			if (gc.puz1selected)	gA::puz[PUZ_1].setOpacity(Puzzle::getPercent(Puzzle::Counter::totalHint));
			if (gc.puz2selected)	gA::puz[PUZ_2].setOpacity(Puzzle::getPercent(Puzzle::Counter::totalHint));
			if (gc.puz3selected)	gA::puz[PUZ_3].setOpacity(Puzzle::getPercent(Puzzle::Counter::totalHint));

			if (Audio::winSound) {
				Audio::winSound = false;
				sceneSound(ga.solvedSound);
			}
		}
	}

	//SCENE 5
	if (gc.currentScene == Scene::PAUSE_SCENE) {
		// Scene Music
		sceneMusic(ga.playMusic);
		// Scene 5-4 switch
		if (gA::resumeButton.isPressed()) {
			sceneSound(ga.selectSound);
			gc.currentScene = Scene::BEGIN_PLAY_SCENE;
		}
		// Scene 5-1 switch
		if (gA::menuButton.isPressed()) {
			sceneSound(ga.selectSound);
			StopMusicStream(ga.playMusic);
			PlayMusicStream(ga.menuMusic);
			sceneMusic(ga.menuMusic);
			// Destroy the puzzle
			Puzzle::destroy();
			UnloadTexture(ga.myPuzzleTexture);

			// Reset everything
			Delay::Reset();					// reset delay
			FadeState::Reset();				// reset fade animation
			gA::hint1.reset();				// reset hint1 state
			gA::hint2.reset();				// reset hint2 state
			Puzzle::_solved.clear();		// reset puzzle solver

			// Then go to Scene 1
			gc.currentScene = Scene::MENU_SCENE;
		}
	}

	//SCENE 6
	if (gc.currentScene == Scene::WIN_SCENE) {
		// Scene Music
		sceneMusic(ga.playMusic);

		// Reset everything
		Audio::winSound = true;			// reset win sound
		Delay::Reset();					// reset delay
		FadeState::Reset();				// reset fade animation
		gA::hint1.reset();				// reset hint1 state
		gA::hint2.reset();				// reset hint2 state
		Puzzle::_solved.clear();		// reset puzzle solver

		// Scene 6-4
		if (gA::retryButton.isPressed()) {
			sceneSound(ga.selectSound);
			// Rebuild and Re-shuffle the puzzle
			Puzzle::destroy();
			updateSlice();		// Get the updated slice size
			Puzzle::loadPuzzle(ga.myPuzzleImage, sl.puz);
			Puzzle::finalizeLoad();

			// Then back to the Play Scene
			gc.currentScene = Scene::BEGIN_PLAY_SCENE;
		}
		// Scene 6-1 switch
		if (gA::menuButton.isPressed()) {
			sceneSound(ga.selectSound);
			StopMusicStream(ga.playMusic);
			PlayMusicStream(ga.menuMusic);
			sceneMusic(ga.menuMusic);
			// Destroy the puzzle
			Puzzle::destroy();
			UnloadTexture(ga.myPuzzleTexture);

			// Then go to Scene 1
			gc.currentScene = Scene::MENU_SCENE;
		}
	}
}