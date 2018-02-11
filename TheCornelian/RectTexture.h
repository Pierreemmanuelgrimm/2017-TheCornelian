#pragma once
#include "Texture.h"
class RectTexture : public Texture
{
public:
	//Default Constructor
	RectTexture();

	// Overload Constructor
	RectTexture(int x, int y, int width, int height, SDL_Color color);

	//Default Destructor
	~RectTexture();

	//Render
	void render(SDL_Renderer* renderer);

	//Accessor functions
		//Get

		//Set


private:
};

