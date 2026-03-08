#include "image_slice.h"

Slice sl{};

// Generate a grid of rectangles
std::vector<Rectangle> GenerateGrid(int cols, int rows, float startX, float startY, float tileWidth, float tileHeight) {
    std::vector<Rectangle> grid;
    grid.reserve(cols * rows);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            grid.push_back({
                startX + col * tileWidth,
                startY + row * tileHeight,
                tileWidth,
                tileHeight
            });
        }
    }
    return grid;
}

void Slice::applySlice()
{
    if (sl.slice < 3) {
        sl.slice = 3;
        return;
    }
    if (sl.slice > 10) {
        sl.slice = 10;
        return;
    }

    // 3 = 0.33333f
    if (sl.slice == 3) {
        sl.prec_slice = 0.33333f;
        sl.rec = GenerateGrid(3, 3, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
        sl.puz = GenerateGrid(3, 3, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 4 = 0.25f
	if (sl.slice == 4) {
		sl.prec_slice = 0.25f;
		sl.rec = GenerateGrid(4, 4, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(4, 4, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 5 = 0.20f
	if (sl.slice == 5) {
		sl.prec_slice = 0.20f;
		sl.rec = GenerateGrid(5, 5, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(5, 5, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 6 = 0.16666f
	if (sl.slice == 6) {
		sl.prec_slice = 0.16666f;
		sl.rec = GenerateGrid(6, 6, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(6, 6, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 7 = 0.1428571f
	if (sl.slice == 7) {
		sl.prec_slice = 0.1428571f;
		sl.rec = GenerateGrid(7, 7, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(7, 7, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 8 = 0.125f
	if (sl.slice == 8) {
		sl.prec_slice = 0.125f;
		sl.rec = GenerateGrid(8, 8, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(8, 8, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 9 = 0.11111f
	if (sl.slice == 9) {
		sl.prec_slice = 0.11111f;
		sl.rec = GenerateGrid(9, 9, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(9, 9, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 10 = 0.10f
	if (sl.slice == 10) {
        sl.prec_slice = 0.10f;
		sl.rec = GenerateGrid(10, 10, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(10, 10, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
}

void updateSlice()
{
    // 3 = 0.33333f
    if (sl.slice == 3) {
        sl.prec_slice = 0.33333f;
        sl.rec = GenerateGrid(3, 3, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
        sl.puz = GenerateGrid(3, 3, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 4 = 0.25f
	if (sl.slice == 4) {
		sl.prec_slice = 0.25f;
		sl.rec = GenerateGrid(4, 4, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(4, 4, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 5 = 0.20f
	if (sl.slice == 5) {
		sl.prec_slice = 0.20f;
		sl.rec = GenerateGrid(5, 5, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(5, 5, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 6 = 0.16666f
	if (sl.slice == 6) {
		sl.prec_slice = 0.16666f;
		sl.rec = GenerateGrid(6, 6, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(6, 6, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 7 = 0.1428571f
	if (sl.slice == 7) {
		sl.prec_slice = 0.1428571f;
		sl.rec = GenerateGrid(7, 7, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(7, 7, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 8 = 0.125f
	if (sl.slice == 8) {
		sl.prec_slice = 0.125f;
		sl.rec = GenerateGrid(8, 8, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(8, 8, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 9 = 0.11111f
	if (sl.slice == 9) {
		sl.prec_slice = 0.11111f;
		sl.rec = GenerateGrid(9, 9, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(9, 9, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
    // 10 = 0.10f
	if (sl.slice == 10) {
        sl.prec_slice = 0.10f;
		sl.rec = GenerateGrid(10, 10, tl.p_image.x, tl.p_image.y, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
		sl.puz = GenerateGrid(10, 10, 0.0f, 0.0f, (ga.myPuzzleTexture.width * sl.prec_slice), (ga.myPuzzleTexture.height * sl.prec_slice));
    }
}
