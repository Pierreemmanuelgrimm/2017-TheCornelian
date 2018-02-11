#pragma once
#include <string>
#include "Texture.h"
class TextTexture : public Texture
{
public:
	//Default Constructor
	TextTexture();

	//Overload Constructor
	TextTexture(int x , int y , int width, int height, std::string text, SDL_Color color, TTF_Font* nfont);

	//Desctructor
	~TextTexture();

	// Render function
	void render(SDL_Renderer* renderer);

	//Accessor functions
		//Get
	virtual std::string getString();
		//Setc
	void clear();
	void setString(std::string);
	void setString(int);
	void addStringEnd(std::string);

private:
	std::string textStr;
	TTF_Font* font;
};

