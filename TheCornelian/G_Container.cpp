#include "G_Container.h"



G_Container::G_Container() :G_Renderable()
{
}


G_Container::~G_Container()
{
}
void G_Container::pushT(G_Renderable* texture) {
	t.push_back(texture);
	t.back()->updatePos(dst.x, dst.y);
}
void G_Container::render(SDL_Renderer* renderer) {
	for (unsigned int i = 0; i < t.size(); i++) {
		t[i]->render(renderer);
	}
}
void G_Container::updatePos(int nx, int ny) {

	G_Renderable::updatePos(nx, ny);
	for (unsigned int i = 0; i < t.size(); i++) {
		t[i]->updatePos(nx, ny);
	}
}
