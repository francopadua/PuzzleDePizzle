#include "image_puzzle.h"

namespace Puzzle
{
    std::vector<Rectangle> arrGrid;
    std::vector<Texture2D> txtTemp;

	std::vector<Texture2D> puzzleTexture;
	std::vector<int> puz_guide;

	int gridSize = 0;
	int blankIndex = -1;

}

namespace Puzzle::Counter
{
    // Label
	const char* moveLabel = "Moves: ";
	Vector2 moveLabelSize{};
    const char* h1Label = "H1 used: ";
    Vector2 h1LabelSize{};
    const char* h2Label = "H2 used: ";
    Vector2 h2LabelSize{};
    
    // Counter
	int move = 0;
    int h1 = 0;
    int h2 = 0;
}

namespace Puzzle::Timer
{
    // Label
	const char* timerLabel = "Timer: ";
    Vector2 timerLabelSize{};

    // Timer
	float elapsedTime = 0.0f;
	int totalSeconds = 0;
    int seconds = 0;
	int minutes = 0;
	int hours = 0;

    const char* get() {
        seconds = totalSeconds % 60;
	    minutes = (totalSeconds % 3600) / 60;
	    hours = totalSeconds / 3600;
        if (hours > 0)
            return TextFormat("%d:%02d:%02d", hours, minutes, seconds);
        if (minutes > 0)
            return TextFormat("%02d:%02d", minutes, seconds);
        return TextFormat("%02d", seconds);
    }
}

void theImagePuzzle(Image& myPuzzleImage, const Image& myImageChoosen, Texture& myPuzzleTexture)
{
	myPuzzleImage = ImageCopy(myImageChoosen);
	myPuzzleTexture = LoadTextureFromImage(imageManipulate(&myPuzzleImage, IMAGE_AS_PUZZLE));
}

bool isSolvable(const std::vector<int>& guide)
{
    int inversions = 0;

    // Count inversions
    for (int i = 0; i < guide.size() - 1; i++) {
        for (int j = i + 1; j < guide.size(); j++) {
            if (guide[i] > guide[j]) inversions++;
        }
    }

    return (inversions % 2 == 0);
}

void randomize(std::vector<Texture2D>& puz, std::vector<int>& guide, int gridSize, int& blankIndex)
{
	std::random_device rd;
	std::mt19937 g(rd());

    while (true) {
        // Shuffle the whole array
	    std::vector<size_t> indices(puz.size() - 1);
	    std::iota(indices.begin(), indices.end(), 0);
	    std::shuffle(indices.begin(), indices.end(), g);

	    std::vector<Texture2D> new_puz;
	    std::vector<int> new_guide;
        new_puz.reserve(indices.size());
        new_guide.reserve(indices.size());

	    for (const auto& e : indices) {
            new_puz.push_back(puz[e]);
            new_guide.push_back(guide[e]);
	    }

        if (isSolvable(new_guide)) {
            // Then place the blankIndex at the very last
            new_puz.push_back(puz.back());
            new_guide.push_back(guide.back());
            // Then replace the original
	        puz.swap(new_puz);
	        guide.swap(new_guide);
            break;
        }
    }
}

// Initial load
void Puzzle::loadPuzzle(const Image& puzImage, const std::vector<Rectangle>& rec)
{
    puzzleTexture.clear();
    puz_guide.clear();

	puzzleTexture.reserve(std::size(rec));
	puz_guide.reserve(std::size(puzzleTexture));
    
    // Refresh image transform
    Image tmp = ImageCopy(puzImage);
    Image tmp2 = imageManipulate(&tmp, IMAGE_AS_PUZZLE);

    int i = 1;
	for (const auto& r : rec) {
		puzzleTexture.push_back(LoadTextureFromImage(ImageFromImage(tmp2, r)));
		puz_guide.push_back(i);
		++i;
        arrGrid.push_back(r);
	}

    gridSize = (int)std::lround(std::sqrt((double)rec.size()));
    blankIndex = (int)puz_guide.size() - 1;

	randomize(puzzleTexture, puz_guide, gridSize, blankIndex);
}

// Final load
void Puzzle::finalizeLoad()
{
    const auto total = (int)puzzleTexture.size();
    auto n = (int)std::lround(std::sqrt((double)total));
    if (n * n != total) {
        // handle error: textures must form a square grid
        TraceLog(LOG_WARNING, "Puzzle::finalizeLoad: not a perfect square: total=%d", total);
    }
    gridSize = n;
    blankIndex = total - 1; // last tile initially blank (matches your randomize)

    // Label
	Timer::timerLabelSize = MeasureTextEx(ga.myFontSmall, Timer::timerLabel, fontSizeSmall, fontSpacing);
    Counter::moveLabelSize = MeasureTextEx(ga.myFontSmall, Counter::moveLabel, fontSizeSmall, fontSpacing);
    Counter::h1LabelSize = MeasureTextEx(ga.myFontSmall, Counter::h1Label, fontSizeSmall, fontSpacing);
    Counter::h2LabelSize = MeasureTextEx(ga.myFontSmall, Counter::h2Label, fontSizeSmall, fontSpacing);
}

// Check puzzle state
void Puzzle::check()
{
    for (int i{ 1 }; i < puz_guide.size(); ++i) {
        if (i != puz_guide[i - 1]) {
            solved = false;
            return;
        }
    }
    solved = true;
}

// Destroy puzzle
void Puzzle::destroy() 
{ 
    for (auto& tex : puzzleTexture)
        UnloadTexture(tex);
    for (auto& tex : txtTemp)
        UnloadTexture(tex);

    puzzleTexture.clear();
    txtTemp.clear();
    arrGrid.clear();
    puz_guide.clear();

    // Reset puzzle state
    solved = false;
    Timer::elapsedTime = 0.0f;
    Timer::totalSeconds = 0;
    Counter::move = 0;
    Counter::h1 = 0;
    Counter::h2 = 0;
}

// Update puzzle state
void Puzzle::update()
{
	// Get Frame Time (Timer)
	Puzzle::Timer::elapsedTime += Game::getFrame();
	if (Puzzle::Timer::elapsedTime >= 1.0f && !Puzzle::isSolved()) {
		++Puzzle::Timer::totalSeconds;
		Puzzle::Timer::elapsedTime -= 1.0f;
	}
}

bool Puzzle::tryMove(int dr, int dc)
{
    if (gridSize <= 0 || blankIndex < 0) return false;

    auto [r, c] = toRowCol(blankIndex);
    int nr = r + dr;
    int nc = c + dc;

    // bounds check (signed ints — avoids underflow)
    if (nr < 0 || nr >= gridSize || nc < 0 || nc >= gridSize) return false;

    int swapIndex = toIndex(nr, nc);

    // swap both texture and guide so they remain in sync
    std::swap(puzzleTexture[blankIndex], puzzleTexture[swapIndex]);
    std::swap(puz_guide[blankIndex], puz_guide[swapIndex]);

    blankIndex = swapIndex;

    // Then make a move count
    Counter::move++;
    // With sound
    sceneSound(ga.slideSound);

    return true;
}

void saveScore()
{
    // Save the score
    ga.ptime = Puzzle::Timer::get();
    ga.pmove = toText(Puzzle::Counter::move);
    ga.ph1 = toText(Puzzle::Counter::h1);
    ga.ph2 = toText(Puzzle::Counter::h2);
}
