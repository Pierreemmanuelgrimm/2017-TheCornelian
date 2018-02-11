#include "Quadrant.h"
#include <iostream>

Quadrant::Quadrant():RectTexture(){
}
Quadrant::Quadrant(int x, int y,  int width, int height, SDL_Color color, QuadDesc quadDesc):RectTexture(x, y, width, height, color)  {
	_quadDesc = quadDesc;
}
Quadrant::Quadrant(int x, int y) : RectTexture(x, y, 0, 0, SDL_Color{ 0x00,0x00,0x00,0x00 }) {
	_quadDesc = QuadDesc::EMPTY;
}


Quadrant::~Quadrant(){
}
void Quadrant::render(SDL_Renderer* renderer) {
	if (!getVisible()) return; 
	RectTexture::render(renderer);
	for (unsigned int j = 0; j < (_textures).size(); j++) {
		//if (_quadDesc == QuadDesc::BUTTON) {
		//	std::cout << static_cast<TextTexture*>(_textures[j])->getString() << std::endl;
		//}
		_textures[j]->render(renderer);
	}
	
}

Texture* Quadrant::getTexture(int i) {
	return _textures[i];
}
void Quadrant::addTexture(Texture* texture) {
	//std::cout << "Texture added" << std::endl;
	//texture->updatePosition(getX(), getY());
	_textures.push_back(texture);
	_textures.back()->updatePosition(getX(), getY());
}
void Quadrant::updatePosition(int x,int y) {
	//std::cout << x << " Button Updated " << y << std::endl;
	Texture::updatePosition(x, y);
	for (unsigned int i = 0; i < _textures.size(); i++) {
		(*_textures[i]).updatePosition(x, y);
	}
}
void Quadrant::popLast() {
	return _textures.pop_back();
}