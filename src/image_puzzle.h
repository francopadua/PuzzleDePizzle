#pragma once

#include "assets.h"
#include "image_slice.h"
#include "scene_management.h"
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

    extern std::vector<int> _solved;

    namespace Counter
    {
        // Label
	    extern const char* moveLabel;
	    extern Vector2 moveLabelSize;
        extern const char* h1Label;
        extern Vector2 h1LabelSize;
        extern const char* h2Label;
        extern Vector2 h2LabelSize;

        // Counter
	    extern int move;        // number of moves taken
        extern int h1;          // number of hint 1 used
        extern int h2;          // number of hint 2 used
        extern int totalHint;
    }

    namespace Timer
    {
        // Label
	    extern const char* timerLabel;
	    extern Vector2 timerLabelSize;

        // Timer
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

    // update puzzle state
    void update();

    // movement
    bool tryMove(int dr, int dc); // dr = -1..1, dc = -1..1

    // puzzle result opacity
    float getPercent(int totalHints);
}

void theImagePuzzle(Image& myPuzzleImage, const Image& myImageChoosen, Texture& myPuzzleTexture);

void saveScore();