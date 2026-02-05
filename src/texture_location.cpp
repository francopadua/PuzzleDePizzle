#include "texture_location.h"

TextureLoc tl{};

void getShapes()
{
	// Background
	tl.bg = {
		(gc.currentWindowWidth - ga.myBgTexture.width) / 2.0f,
		(gc.currentWindowHeight - ga.myBgTexture.height) / 2.0f,
		static_cast<float>(ga.myBgTexture.width),
		static_cast<float>(ga.myBgTexture.height)
	};
	// Background overlay
	tl.bg_o = {
		tl.bg.x + (tl.bg.width / 2) - (ga.myBgTextureOverlay.width / 2),
		tl.bg.y + (tl.bg.height / 2) - (ga.myBgTextureOverlay.height /2),
		static_cast<float>(ga.myBgTextureOverlay.width),
		static_cast<float>(ga.myBgTextureOverlay.height)
	};
	// Title
	tl.title = {
		tl.bg.x + (tl.bg.width / 2.0f) - (ga.myTitleTexture.width / 2.0f),
		tl.bg.y + (tl.bg.height / 2.0f) - ga.myTitleTexture.height,
		static_cast<float>(ga.myTitleTexture.width),
		static_cast<float>(ga.myTitleTexture.height)
	};

	// Icons
	tl.icon1 = {
		(tl.bg_o.width * 0.1f) + tl.bg_o.x,
		((tl.bg_o.height - ga.puzzleImage1Texture.height) / 2.0f) + tl.bg_o.y, 
		static_cast<float>(ga.puzzleImage1Texture.width),
		static_cast<float>(ga.puzzleImage1Texture.height)
	};
	tl.icon2 = {
		(tl.bg_o.width * 0.1f) + tl.bg_o.x,
		((tl.bg_o.height - ga.puzzleImage2Texture.height) / 2.0f) + tl.bg_o.y,
		static_cast<float>(ga.puzzleImage2Texture.width),
		static_cast<float>(ga.puzzleImage2Texture.height)
	};
	tl.icon3 = {
		(tl.bg_o.width * 0.1f) + tl.bg_o.x,
		((tl.bg_o.height - ga.puzzleImage3Texture.height) / 2.0f) + tl.bg_o.y, 
		static_cast<float>(ga.puzzleImage3Texture.width),
		static_cast<float>(ga.puzzleImage3Texture.height)
	};
	// Relocation of icons
	tl.icon1.y = ((tl.bg_o.y + tl.icon2.y) / 2.0f) - (tl.icon1.height / 2.0f);
	tl.icon3.y = ((tl.bg_o.y + tl.bg_o.height + tl.icon2.y + tl.icon2.height) / 2.0f) - (tl.icon1.height / 2.0f);

	// Puzzle image
	tl.p_image = {
		tl.bg.x + (tl.bg.width / 2) - (ga.myPuzzleTexture.width / 2),
		tl.bg.y + (tl.bg.height / 2) - (ga.myPuzzleTexture.height /2),
		static_cast<float>(ga.myPuzzleTexture.width),
		static_cast<float>(ga.myPuzzleTexture.height)
	};
	
	// Other shapes
	tl.icon1sel = {
		tl.bg_o.x,
		tl.icon1.y,
		tl.bg_o.width,
		tl.icon1.height
	};
	tl.icon2sel = {
		tl.bg_o.x,
		tl.icon2.y,
		tl.bg_o.width,
		tl.icon2.height
	};
	tl.icon3sel = {
		tl.bg_o.x,
		tl.icon3.y,
		tl.bg_o.width,
		tl.icon3.height
	};
}
