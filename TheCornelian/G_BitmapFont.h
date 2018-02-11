#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include "logSDLError.h"
#include <string>
class G_BitmapFont
{
public:
	G_BitmapFont();
	G_BitmapFont(std::string &path,SDL_Renderer*,SDL_Color col);
	~G_BitmapFont();
	void loadFont(std::string& path, SDL_Renderer* renderer);
	bool buildFont();
	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);
	SDL_Color mColor;

	//The font texture
	SDL_Texture* mBitmap;

	void* mPixels;
	int mPitch;

	//Image dimensions
	int mWidth;
	int mHeight;

	//The individual characters in the surface
	SDL_Rect mChars[256];
	

	//Spacing Variables
	int mNewLine, mSpace;
};

