#include "TextTexture.h"
//#include <iostream>

TextTexture::TextTexture():Texture(){
	// DO NOT CALL
}

TextTexture::TextTexture(int x, int y, int width, int height, std::string text, SDL_Color color, TTF_Font* nfont) : Texture(x, y, width, height, color) {
	textStr = text;
	font = nfont;
	
}
TextTexture::~TextTexture(){
}
void TextTexture::render(SDL_Renderer* renderer) {
	if (!getVisible()) return;
	//SDL_Surface *textSurf = TTF_RenderText_Solid(font, textStr.c_str(), getColor());
	//std::cout << textStr << std::endl;
	SDL_Surface *textSurf = TTF_RenderText_Blended_Wrapped(font, getString().c_str(), getColor(), getWidth());
	SDL_Texture *textText = SDL_CreateTextureFromSurface(renderer, textSurf);
	SDL_Rect textRect;
	textRect.x = getX();
	textRect.y = getY();
	SDL_QueryTexture(textText, NULL, NULL, &textRect.w, &textRect.h);
	SDL_SetRenderDrawColor(renderer, getR(), getG(), getB(), getA());
	SDL_RenderCopy(renderer, textText, NULL, &textRect);

	SDL_FreeSurface(textSurf);
	textSurf = nullptr;
	SDL_DestroyTexture(textText);
	textText = nullptr;

}
void TextTexture::setString(std::string str) {
	textStr = str;
}
void TextTexture::setString(int n) {
	textStr = std::to_string(n);
}
void TextTexture::addStringEnd(std::string str) {
	if (textStr.length() > 4000) {
		textStr = textStr.substr(0, 4000);
	}
	textStr = str + "\n" + textStr;
}
std::string TextTexture::getString() {
	return textStr;
}
void TextTexture::clear() {
	textStr = "";
}