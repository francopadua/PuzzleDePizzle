#include "user_controls.h"

void UserControls::systemControls()
{
	// LOCKING/UNLOCKING RESIZE WINDOW
	if (IsKeyPressed(KEY_R))
	{
		if (IsWindowState(FLAG_WINDOW_RESIZABLE)) {
			ClearWindowState(FLAG_WINDOW_RESIZABLE);
		}
		else SetWindowState(FLAG_WINDOW_RESIZABLE);
	}
	if (IsKeyPressed(KEY_G))
	{
		if (gc.draw_guide)		gc.draw_guide = false;
		else					gc.draw_guide = true;
	}
}

void UserControls::userControls()
{
	// MOVEMENT
	if (gc.currentScene == Scene::BEGIN_PLAY_SCENE)
	{
		// Reverse input
		// Keyboard
		// W = down, S = up, A = right, D = left
		if (IsKeyPressed(KEY_S)) { Puzzle::tryMove(-1, 0); } // move blank up
		if (IsKeyPressed(KEY_W)) { Puzzle::tryMove( 1, 0); } // move blank down
		if (IsKeyPressed(KEY_D)) { Puzzle::tryMove( 0,-1); } // move blank left
		if (IsKeyPressed(KEY_A)) { Puzzle::tryMove( 0, 1); } // move blank right
		// Mouse/Touch
		Vector2 mousePos = GetMousePosition();
		Rectangle topTileRect = {
			sl.rec[Puzzle::blankIndex].x,
			sl.rec[Puzzle::blankIndex].y - sl.rec[Puzzle::blankIndex].height,
			sl.rec[Puzzle::blankIndex].width,
			sl.rec[Puzzle::blankIndex].height
		};
		Rectangle bottomTileRect = {
			sl.rec[Puzzle::blankIndex].x,
			sl.rec[Puzzle::blankIndex].y + sl.rec[Puzzle::blankIndex].height,
			sl.rec[Puzzle::blankIndex].width,
			sl.rec[Puzzle::blankIndex].height
		};
		Rectangle leftTileRect = {
			sl.rec[Puzzle::blankIndex].x - sl.rec[Puzzle::blankIndex].width,
			sl.rec[Puzzle::blankIndex].y,
			sl.rec[Puzzle::blankIndex].width,
			sl.rec[Puzzle::blankIndex].height
		};
		Rectangle rightTileRect = {
			sl.rec[Puzzle::blankIndex].x + sl.rec[Puzzle::blankIndex].width,
			sl.rec[Puzzle::blankIndex].y,
			sl.rec[Puzzle::blankIndex].width,
			sl.rec[Puzzle::blankIndex].height
		};
		bool isTopTileClicked = CheckCollisionPointRec(mousePos, topTileRect);
		bool isBottomTileClicked = CheckCollisionPointRec(mousePos, bottomTileRect);
		bool isLeftTileClicked = CheckCollisionPointRec(mousePos, leftTileRect);
		bool isRightTileClicked = CheckCollisionPointRec(mousePos, rightTileRect);
		bool isMouseClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsGestureDetected(GESTURE_TAP);
		if (isMouseClicked && isTopTileClicked) { Puzzle::tryMove(-1, 0); } // move blank up
		if (isMouseClicked && isBottomTileClicked) { Puzzle::tryMove(1, 0); } // move blank down
		if (isMouseClicked && isLeftTileClicked) { Puzzle::tryMove(0, -1); } // move blank left
		if (isMouseClicked && isRightTileClicked) { Puzzle::tryMove(0, 1); } // move blank right
	}

	// GOD MODE
	//if (gc.currentScene == Scene::BEGIN_PLAY_SCENE)
	//{
	//	if (IsKeyDown(KEY_SPACE)) {
	//		for (int i{ 0 }; i < Puzzle::puz_guide.size(); ++i) {
	//			Puzzle::puz_guide[i] = Puzzle::_solved[i];
	//		}
	//	}
	//}
}