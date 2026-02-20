#pragma once

#include "assets.h"
#include "config.h"
#include "image_puzzle.h"
#include "image_slice.h"
#include "PuzzleResult.h"

#include <raylib.h>

Image imageManipulate(Image* myImage, ImageType imageType);
void textureTransform(const Image& image, Texture2D& texture, ImageType imageType);
void transformTextures();
void arrayTransform();
