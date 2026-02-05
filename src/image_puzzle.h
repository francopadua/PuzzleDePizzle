#pragma once

#include "assets.h"
#include "image_slice.h"
#include "transform.h"
#include <numeric>
#include <random>
#include <raylib.h>
#include <vector>

namespace Puzzle 
{
    extern std::vector<Rectangle> arrGrid;
    extern std::vector<Texture2D> txtTemp;

	extern std::vector<Texture2D> puzzleTexture;
	extern std::vector<int> puz_guide;

    extern int gridSize;     // number of columns/rows
    extern int blankIndex; // current blank position (signed int!)

	extern int move;        // number of moves taken

    namespace Timer
    {
        // The labels
	    extern const char* timerLabel;
	    extern Vector2 timerLabelSize;
	    extern const char* moveLabel;
	    extern Vector2 moveLabelSize;

        // The timer
	    extern float elapsedTime;
	    extern int totalSeconds;
	    extern int seconds;
	    extern int minutes;
	    extern int hours;

        const char* get();
    }

    // Completed puzzle
    inline bool solved;

    // Load initial puzzle
	void loadPuzzle(const Image& puzImage, const std::vector<Rectangle>& rec);

    // helpers
    inline int toIndex(int r, int c) { return r * gridSize + c; }
    inline std::pair<int,int> toRowCol(int idx) { return { idx / gridSize, idx % gridSize }; }

    // call after loading & randomizing textures
    void finalizeLoad(); 

    // Check the puzzle
    void check();
    inline bool isSolved() { return solved; }

    // destroy the puzzle
    void destroy();

    // movement
    bool tryMove(int dr, int dc); // dr = -1..1, dc = -1..1
}

void theImagePuzzle(Image& myPuzzleImage, const Image& myImageChoosen, Texture& myPuzzleTexture);