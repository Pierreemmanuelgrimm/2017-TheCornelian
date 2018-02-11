#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
enum class TextType { RECT, TEXT };
//TextType - Describes the type of texture
//Texture is either rectangle or text.
class Texture{
public:
	//Constructor
	Texture();

	//Overloaded Constructor
	Texture(int, int, int, int, SDL_Color);

	//Descructor
	~Texture();

	// Virtual functions
	virtual void render(SDL_Renderer* renderer);
	virtual void setString(int);
	virtual void updatePosition(int, int);

	//virtual std::string getString();
	//Accesor Functions
		//Get
	int getX(), getY();
	virtual int getWidth();
	int getHeight();
	virtual SDL_Color getColor();
	int getR(), getG(), getB(), getA();
	bool getVisible();

		//Set
	void setX(int), setY(int);
	void setWidth(int), setHeight(int);
	void setColor(SDL_Color);
	void setR(int), setG(int), setB(int), setA(int);
	void setVisible(bool);
	
	

private:
	int x, y;
	int width, height;
	bool isVisible;
	SDL_Color color;
};

