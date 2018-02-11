#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "RectTexture.h"
#include "TextTexture.h"
enum class QuadDesc { TLEFT,TRIGHT,BLEFT,BRIGHT,BUTTON ,EMPTY};
//QuadDesc - Describes Quadrant Descrption
//Can be either top/bottom left/right
class Quadrant : public RectTexture
{
public:
	//Default Constructor
	Quadrant();

	//Overload Constuctor
	Quadrant(int x, int y, int width, int height, SDL_Color color, QuadDesc quadDesc);
	Quadrant(int x, int y);

	//Default Destructor
	~Quadrant();

	// Render
	void render(SDL_Renderer* renderer);

	//Accessor function
	void addTexture(Texture* texture);
	void updatePosition(int,int);
	Texture* getTexture(int);
	void popLast();

private:
	std::vector<Texture*> _textures;
	QuadDesc _quadDesc;
};

