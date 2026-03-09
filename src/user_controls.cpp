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
		// W = down, S = up, A = right, D = left
		if (IsKeyPressed(KEY_S)) { Puzzle::tryMove(-1, 0); } // move blank up
		if (IsKeyPressed(KEY_W)) { Puzzle::tryMove( 1, 0); } // move blank down
		if (IsKeyPressed(KEY_D)) { Puzzle::tryMove( 0,-1); } // move blank left
		if (IsKeyPressed(KEY_A)) { Puzzle::tryMove( 0, 1); } // move blank right
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