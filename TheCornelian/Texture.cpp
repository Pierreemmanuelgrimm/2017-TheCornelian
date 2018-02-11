#include "Texture.h"

//Default Constructor
Texture::Texture(){
	x = 0;
	y = 0;
	isVisible = 1;
	color = { 0x00, 0x00, 0x00, 0x00 };
}
Texture::Texture(int nx, int ny, int nwidth, int nheight, SDL_Color ncolor) {
	x = nx;
	y = ny;
	width = nwidth;
	height = nheight;
	isVisible = 1;
	color = ncolor;
}

//Destructor
Texture::~Texture(){
}

// Virtual
void Texture::render(SDL_Renderer* renderer) {
	return;
}
void Texture::setString(int x) {
	return;
}

int Texture::getX() {
	return x;
}
int Texture::getY() {
	return y;
}
int Texture::getR() {
	return getColor().r;
}
int Texture::getG() {
	return getColor().g;
}
int Texture::getB() {
	return getColor().b;
}
int Texture::getA() {
	return getColor().a;
}
SDL_Color Texture::getColor() {
	return color;
}

bool Texture::getVisible() {
	return isVisible;
}

void Texture::setX(int nx) {
	x = nx;
}
void Texture::setY(int ny) {
	y = ny;
}
void Texture::setColor(SDL_Color c) {
	setR(c.r);
	setG(c.g);
	setB(c.b);
	setA(c.a);
}
void Texture::setR(int na) {
	color.a = na;
}
void Texture::setG(int ng) {
	color.g = ng;
}
void Texture::setB(int nb) {
	color.b = nb;
}
void Texture::setA(int na) {
	color.a = na;
}
void Texture::setVisible(bool b) {
	isVisible = b;
}
void Texture::updatePosition(int x, int y) {
	setX(getX() + x);
	setY(getY() + y);
}

int Texture::getWidth() {
	return width;
}
int Texture::getHeight() {
	return height;
}

void Texture::setWidth(int nwidth) {
	width = nwidth;
}
void Texture::setHeight(int nheight) {
	height = nheight;
}


