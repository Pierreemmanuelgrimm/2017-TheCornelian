#pragma once
#include "G_Renderable.h"
#include <vector>
class G_Container : public G_Renderable
{
public:
	G_Container();
	~G_Container();
	void pushT(G_Renderable*);
		// Push new G_Texture into vector
	void render(SDL_Renderer*);
		// Render all elements in vector
	void updatePos(int x, int y);
		//shift position of all objects inside container (including container) by (x,y)

	std::vector<G_Renderable*> t;
		//Vector of G_Texture inside thecontainer
	

};

