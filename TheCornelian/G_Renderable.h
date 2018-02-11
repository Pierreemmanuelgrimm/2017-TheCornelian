#pragma once
#include <SDL.h>
class G_Renderable
{
public:
	//Default Constructor
	G_Renderable();

	//Default Deconstructot
	~G_Renderable();


	virtual void render(SDL_Renderer*) = 0;
		//Render
	virtual void updatePos(int x, int y);
		//Allows to shift a texture by (x,y);
	
	SDL_Rect dst; // Destination rectangle to render the texture
	
};

