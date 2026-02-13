#include "texture_location.h"
#include "transform.h"

Image imageManipulate(Image* myImage, ImageType imageType)
{
	// Screen Width/Height
	int gsw = GetScreenWidth();
	int gsh = GetScreenHeight();

	// Get image dimensions
	int Width = myImage->width;
	int Height = myImage->height;

	// target size
	float maxWidth{};
	float maxHeight{};
	// Compute scale ratio while preserving aspect ratio
	float scaleX{};
	float scaleY{};
	float scale{};
	// New dimensions
	int newWidth{};
	int newHeight{};

	if (imageType == IMAGE_AS_TITLE) {
		maxWidth = ga.myBgTexture.width / 2.0f;
		maxHeight = ga.myBgTexture.height / 2.0f;
		scaleX = maxWidth / Width;
		scaleY = maxHeight / Height;
		scale = std::min(scaleX, scaleY);

		newWidth = static_cast<int>(Width * scale);
		newHeight = static_cast<int>(Height * scale);
	}
	else if (imageType == IMAGE_AS_ICON) {
		maxWidth = ga.myBgTexture.width / 5.0f;
		maxHeight = ga.myBgTexture.height / 5.0f;
		scaleX = maxWidth / Width;
		scaleY = maxHeight / Height;
		scale = std::min(scaleX, scaleY);

		newWidth = static_cast<int>(Width * scale);
		newHeight = static_cast<int>(Height * scale);
	}
	else if (imageType == IMAGE_AS_BG_OVERLAY) {
		maxWidth = gsw / 1.3f;
		maxHeight = gsh / 1.3f;
		scaleX = maxWidth / Width;
		scaleY = maxHeight / Height;
		scale = std::min(scaleX, scaleY);

		newWidth = static_cast<int>(Width * scale);
		newHeight = static_cast<int>(Height * scale);
	}
	else if (imageType == IMAGE_AS_PUZZLE) {
		maxWidth = gsw / 1.7f;
		maxHeight = gsh / 1.7f;
		scaleX = maxWidth / Width;
		scaleY = maxHeight / Height;
		scale = std::min(scaleX, scaleY);

		newWidth = static_cast<int>(Width * scale);
		newHeight = static_cast<int>(Height * scale);
	}
	else {
		maxWidth = gsw;
		maxHeight = gsh;
		scaleX = maxWidth / Width;
		scaleY = maxHeight / Height;
		scale = std::min(scaleX, scaleY);

		newWidth = static_cast<int>(Width * scale);
		newHeight = static_cast<int>(Height * scale);
	}

	ImageResize(myImage, newWidth, newHeight);

	return *myImage;
}

void textureTransform(const Image& image, Texture2D& texture, ImageType imageType)
{
	if (image.data != nullptr)
	{
		if (texture.id != 0)	UnloadTexture(texture);

		Image temp = ImageCopy(image);
		Image temp2 = imageManipulate(&temp, imageType);

		// For text attach to the 0 opacity blank BG image, so that I don't need to resize every Image text
		if (image.data == ga.myBgBlankImage.data)
		{
			// Will define on a separate function later
			if (Puzzle::isSolved()) {
				// Can be used anywhere but the highest detail is the base font, not the scaledFont
				float scaleX = (float)GetScreenWidth() / screenWidth;
				float scaleY = (float)GetScreenHeight() / screenHeight;
				float scale = std::min(scaleX, scaleY);
				float scaledFont = fontSizeSmall * scale;	// Base font size: 30.0f

				// Format
				/*
						   Time:	{Puzzle::Timer::get()}
						  Moves:	{Puzzle::Counter::move}
					Hint 1 used:	{Puzzle::Counter::hint1}
					Hint 2 used:	{Puzzle::Counter::hint2}
				*/

				Vector2 ptime = MeasureTextEx(ga.myFontSmall, "Time:", scaledFont, fontSpacing);
				Vector2 pmove = MeasureTextEx(ga.myFontSmall, "Moves:", scaledFont, fontSpacing);
				Vector2 ph1 = MeasureTextEx(ga.myFontSmall, "Hint 1 used:", scaledFont, fontSpacing);
				Vector2 ph2 = MeasureTextEx(ga.myFontSmall, "Hint 2 used:", scaledFont, fontSpacing);	// This is the longest text, maybe because 2 has bigger glyphs than 1

				ImageDrawTextEx(&temp2, ga.myFontSmall, "Time: ", { (ph2.x - ptime.x) + (ga.myBgTexture.width / 4.0f), ga.myBgTexture.height * 0.30f}, scaledFont, fontSpacing, WHITE);
				ImageDrawTextEx(&temp2, ga.myFontSmall, "Moves: ", { (ph2.x - pmove.x) + (ga.myBgTexture.width / 4.0f), ga.myBgTexture.height * 0.35f}, scaledFont, fontSpacing, WHITE);
				ImageDrawTextEx(&temp2, ga.myFontSmall, "Hint 1 used: ", { (ph2.x - ph1.x) + (ga.myBgTexture.width / 4.0f), ga.myBgTexture.height * 0.40f }, scaledFont, fontSpacing, WHITE);
				ImageDrawTextEx(&temp2, ga.myFontSmall, "Hint 2 used: ", { (ga.myBgTexture.width / 4.0f), ga.myBgTexture.height * 0.45f }, scaledFont, fontSpacing, WHITE);

				ImageDrawTextEx(&temp2, ga.myFontSmall, ga.ptime.c_str(), { (ga.myBgTexture.width / 2.0f), ga.myBgTexture.height * 0.30f }, scaledFont, fontSpacing, WHITE);
				ImageDrawTextEx(&temp2, ga.myFontSmall, ga.pmove.c_str(), { (ga.myBgTexture.width / 2.0f), ga.myBgTexture.height * 0.35f }, scaledFont, fontSpacing, WHITE);
				ImageDrawTextEx(&temp2, ga.myFontSmall, ga.ph1.c_str(), { (ga.myBgTexture.width / 2.0f), ga.myBgTexture.height * 0.40f }, scaledFont, fontSpacing, WHITE);
				ImageDrawTextEx(&temp2, ga.myFontSmall, ga.ph2.c_str(), { (ga.myBgTexture.width / 2.0f), ga.myBgTexture.height * 0.45f }, scaledFont, fontSpacing, WHITE);
			}
		}

		texture = LoadTextureFromImage(temp2);

		UnloadImage(temp);
		temp2 = {};
		ga.tempImage = {};
	}
}

// This is called everytime the window is resized
void arrayTransform()
{
	Puzzle::arrGrid.clear();
	Puzzle::txtTemp.clear();
	Puzzle::arrGrid = GenerateGrid(Puzzle::gridSize, Puzzle::gridSize, 0.0f, 0.0f, ga.myPuzzleTexture.width * sl.prec_slice, ga.myPuzzleTexture.height * sl.prec_slice);

	Image tmp = ImageCopy(ga.myPuzzleImage);
	std::vector<Texture2D> testArr;
	testArr.reserve(Puzzle::puzzleTexture.size());

	for (const auto& s : Puzzle::arrGrid)
		testArr.push_back(LoadTextureFromImage(ImageFromImage(imageManipulate(&tmp, IMAGE_AS_PUZZLE), s)));

	Puzzle::txtTemp.resize(Puzzle::puzzleTexture.size());
	for (int i{ 0 }; i < Puzzle::puzzleTexture.size(); ++i) {
		Puzzle::txtTemp[i] = testArr[Puzzle::puz_guide[i] - 1];
	}

	// SWAPP
	Puzzle::puzzleTexture.swap(Puzzle::txtTemp);
}

void transformTextures()
{
		// Resize the texture and maintain quality if the screen dimension is updated
		if (gc.currentWindowWidth != GetScreenWidth() || gc.currentWindowHeight != GetScreenHeight())
		{
			// The choosed image
			textureTransform(ga.myPuzzleImage, ga.myPuzzleTexture, IMAGE_AS_PUZZLE);
			arrayTransform();

			// Background contents
			textureTransform(ga.myBgImage, ga.myBgTexture, IMAGE_AS_BG);
			textureTransform(ga.myBgBlankImage, ga.myBgBlankTexture, IMAGE_AS_BG);
			textureTransform(ga.myBgImageOverlay, ga.myBgTextureOverlay, IMAGE_AS_BG_OVERLAY);
			textureTransform(ga.myBgBorder[0], ga.myBgBorderTexture[0], IMAGE_AS_BG);
			textureTransform(ga.myBgBorder[1], ga.myBgBorderTexture[1], IMAGE_AS_BG);

			// Title
			textureTransform(ga.myTitle, ga.myTitleTexture, IMAGE_AS_TITLE);

			// The built-in puzzle images
			textureTransform(ga.puzzleImage1, ga.puzzleImage1Texture, IMAGE_AS_ICON);
			textureTransform(ga.puzzleImage2, ga.puzzleImage2Texture, IMAGE_AS_ICON);
			textureTransform(ga.puzzleImage3, ga.puzzleImage3Texture, IMAGE_AS_ICON);

			// Text as images
			// Choose Image Scene
			textureTransform(ga.txt_ChooseImage, ga.txt_ChooseImage_texture, IMAGE_AS_ICON);
			textureTransform(ga.puzImg1Txt, ga.puzImg1Txt_texture, IMAGE_AS_ICON);
			textureTransform(ga.puzImg2Txt, ga.puzImg2Txt_texture, IMAGE_AS_ICON);
			textureTransform(ga.puzImg3Txt, ga.puzImg3Txt_texture, IMAGE_AS_ICON);
			// Slice Image Scene
			textureTransform(ga.txt_SliceImage, ga.txt_SliceImage_texture, IMAGE_AS_ICON);
			// Pause Scene
			textureTransform(ga.txt_Paused, ga.txt_Paused_texture, IMAGE_AS_ICON);


			// ==================================================================================


			// Buttons
			// Menu Scene
			gA::playButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, LARGE);
			gA::exitButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, LARGE);
			gA::musicButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, SMALL);
			gA::soundButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, SMALL);

			// Choose Image Scene
			gA::backButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, MEDIUM);
			gA::folderButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, MEDIUM);

			// Slice Image Scene
			gA::plusButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, SMALL);
			gA::subButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, SMALL);
			gA::startButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, MEDIUM);

			// Begin Play Scene
			gA::pauseButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, SMALL);
			gA::hint1.scaled(ga.myBgTexture.width, ga.myBgTexture.height, SMALL);
			gA::hint2.scaled(ga.myBgTexture.width, ga.myBgTexture.height, SMALL);

			// Pause Scene
			gA::resumeButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, LARGE);
			gA::menuButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, LARGE);

			// Win Scene
			gA::retryButton.scaled(ga.myBgTexture.width, ga.myBgTexture.height, LARGE);

			// Then assign to current window resolution
			gc.currentWindowWidth = GetScreenWidth();
			gc.currentWindowHeight = GetScreenHeight();
		}
}