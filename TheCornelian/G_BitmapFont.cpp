#include "G_BitmapFont.h"

G_BitmapFont::G_BitmapFont(){
	//Initialize variables
	mBitmap = NULL;
	mNewLine = 0;
	mSpace = 0;
	mWidth = 0;
	mHeight = 0;
	mPixels = NULL;
	mPitch = 0;
}

G_BitmapFont::G_BitmapFont(std::string& path,SDL_Renderer* renderer,SDL_Color col) {
	mColor = col;
	loadFont(path, renderer);
	buildFont();
}
G_BitmapFont::~G_BitmapFont(){
}
void G_BitmapFont::loadFont(std::string &path, SDL_Renderer* renderer) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		logSDLError(std::cout, "Unable to load image %s! SDL_image in : %s\n" +   path);
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			logSDLError(std::cout, "Unable to convert loaded surface to display format! %s\n" +  path);
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &mPixels, &mPitch);
				
				//Copy loaded/formatted surface pixels
				memcpy(mPixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);


				//Get image dimensions
				mWidth = formattedSurface->w;
				mHeight = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)mPixels;
				int pixelCount = (mPitch / 4) * mHeight;

				//Map colors	
				Uint32 newColor = SDL_MapRGB(formattedSurface->format, mColor.r, mColor.g, mColor.b);
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0x50, 0xFF, 0xFF); // used to be 0x00,0xFF,0xFF
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] < colorKey) // used to be pixels[i] == colorKey
					{
						pixels[i] = transparent;
					}
					else
					{
						pixels[i] = newColor;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				mPixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mBitmap = newTexture;
}
void G_BitmapFont::free()
{
	//Free texture if it exists
	if (mBitmap != NULL)
	{
		SDL_DestroyTexture(mBitmap);
		mBitmap = NULL;
		mWidth = 0;
		mHeight = 0;
		mPixels = NULL;
		mPitch = 0;
	}
}
void G_BitmapFont::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mBitmap, red, green, blue);
}

void G_BitmapFont::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mBitmap, blending);
}

void G_BitmapFont::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mBitmap, alpha);
}
int G_BitmapFont::getWidth()
{
	return mWidth;
}

int G_BitmapFont::getHeight()
{
	return mHeight;
}
//Using SDL, SDL_image, SDL_ttf, standard IO, math, strings, and string streams
bool G_BitmapFont::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if (mPixels != NULL)
	{
		logSDLError(std::cout, "Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(mBitmap, NULL, &mPixels, &mPitch) != 0)
		{
			printf("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}

bool G_BitmapFont::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if (mPixels == NULL)
	{
		logSDLError(std::cout, "Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(mBitmap);
		mPixels = NULL;
		mPitch = 0;
	}

	return success;
}

void* G_BitmapFont::getPixels()
{
	return mPixels;
}

int G_BitmapFont::getPitch()
{
	return mPitch;
}

Uint32 G_BitmapFont::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)mPixels;

	//Get the pixel requested
	return pixels[(y * (mPitch / 4)) + x];
}

bool G_BitmapFont::buildFont()
{
	bool success = true;

	//Lock pixels for access
	if (!lockTexture())
	{
		logSDLError(std::cout, "Unable to lock bitmap font texture!\n");
		
		success = false;
	}
	else
	{
		//Set the background color
		Uint32 bgColor = getPixel32(0, 0);

		//Set the cell dimensions
		int cellW = getWidth() / 16;
		int cellH = getHeight() / 16;

		//New line variables
		int top = cellH;
		int baseA = cellH;

		//The current character we're setting
		int currentChar = 0;

		//Go through the cell rows
		for (int rows = 0; rows < 16; ++rows)
		{
			//Go through the cell columns
			for (int cols = 0; cols < 16; ++cols)
			{
				//Set the character offset
				mChars[currentChar].x = cellW * cols;
				mChars[currentChar].y = cellH * rows;

				//Set the dimensions of the character
				mChars[currentChar].w = cellW;
				mChars[currentChar].h = cellH;

				//Find Left Side
				//Go through pixel columns
				for (int pCol = 0; pCol < cellW; ++pCol)
				{
					//Go through pixel rows
					for (int pRow = 0; pRow < cellH; ++pRow)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (getPixel32(pX, pY) != bgColor)
						{
							//Set the x offset
							mChars[currentChar].x = pX;

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Right Side
				//Go through pixel columns
				for (int pColW = cellW - 1; pColW >= 0; --pColW)
				{
					//Go through pixel rows
					for (int pRowW = 0; pRowW < cellH; ++pRowW)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pColW;
						int pY = (cellH * rows) + pRowW;

						//If a non colorkey pixel is found
						if (getPixel32(pX, pY) != bgColor)
						{
							//Set the width
							mChars[currentChar].w = (pX - mChars[currentChar].x) + 1;

							//Break the loops
							pColW = -1;
							pRowW = cellH;
						}
					}
				}

				//Find Top
				//Go through pixel rows
				for (int pRow = 0; pRow < cellH; ++pRow)
				{
					//Go through pixel columns
					for (int pCol = 0; pCol < cellW; ++pCol)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (getPixel32(pX, pY) != bgColor)
						{
							//If new top is found
							if (pRow < top)
							{
								top = pRow;
							}

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Bottom of A
				if (currentChar == 'A')
				{
					//Go through pixel rows
					for (int pRow = cellH - 1; pRow >= 0; --pRow)
					{
						//Go through pixel columns
						for (int pCol = 0; pCol < cellW; ++pCol)
						{
							//Get the pixel offsets
							int pX = (cellW * cols) + pCol;
							int pY = (cellH * rows) + pRow;

							//If a non colorkey pixel is found
							if (getPixel32(pX, pY) != bgColor)
							{
								//Bottom of a is found
								baseA = pRow;

								//Break the loops
								pCol = cellW;
								pRow = -1;
							}
						}
					}
				}

				//Go to the next character
				++currentChar;
			}
		}

		//Calculate space
		mSpace = cellW / 2;

		//Calculate new line
		mNewLine = baseA - top;

		//Lop off excess top pixels
		for (int i = 0; i < 256; ++i)
		{
			mChars[i].y += top;
			mChars[i].h -= top;
		}

		unlockTexture();
	}

	return success;
}