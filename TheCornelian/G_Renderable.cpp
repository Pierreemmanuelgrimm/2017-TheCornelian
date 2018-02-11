#include "G_Renderable.h"

G_Renderable::G_Renderable(){
	dst = { 0,0,0,0 };

}

G_Renderable::~G_Renderable(){
}
void G_Renderable::updatePos(int nx, int ny) {
	dst.x += nx;
	dst.y += ny;
}