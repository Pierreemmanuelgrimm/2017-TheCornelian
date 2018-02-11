#include "Button.h"

Button::Button() {
}
Button::Button(int x, int y, int width, int height, int nhandle, int nid , SDL_Color colorBox, TextTexture* textTexture) : Quadrant(x, y, width, height, colorBox, QuadDesc::BUTTON){
	addTexture(textTexture);
	handle = nhandle;
	id = nid;
	isClickable = 1;
}
Button::Button(int x, int y, int width, int height, int nhandle, int nid, std::string text, SDL_Color colortext, SDL_Color colorBox, TTF_Font* font) : Quadrant(x, y, width, height, colorBox, QuadDesc::BUTTON) {
	TextTexture* textText = new TextTexture(width/3,height/3, width ,height ,text, colortext, font);
	addTexture(textText);
	handle = nhandle;
	id = nid;
	isClickable = 1;
}
Button::~Button(){
}
bool Button::isClicked(int x, int y) {
	if (!getIsClickable()) return false;
	if ((x > getX()) && (x < getX() + getWidth()) && (y > getY()) && (y < getY() + getHeight())) {
		return true;
	}
	return false;
}
bool Button::getIsClickable() {
	return isClickable;
}
void Button :: setIsClickable(bool i) {
	isClickable = i;
}
int Button::getHandle() {
	return handle;
}
int Button::getID() {
	return id;
}
void Button::setID(int a) {
	id = a;
}