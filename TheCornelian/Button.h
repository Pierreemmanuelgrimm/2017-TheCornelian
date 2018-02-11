#pragma once
#include "Quadrant.h"
#include "TextTexture.h"
class Button : public Quadrant
{
public:
	// Default Constructor
	Button();

	// Overload Constructor
	Button(int x, int y, int width, int height, int handle, int nid, std::string text, SDL_Color colortext, SDL_Color colorBox, TTF_Font* nfont);
	Button(int x, int y, int width, int height, int handle, int nid, SDL_Color colorBox, TextTexture* textTexure);

	//Destructor
	~Button();

	//Accessor
	bool isClicked(int x, int y);
	bool getIsClickable();

	//Methods
	void setIsClickable(bool);
	int getHandle();
	int getID();
	void setID(int);
private:
	std::vector<Texture*> _textures;
	bool isClickable;
	int handle;
	int id;
};

