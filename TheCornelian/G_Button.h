#pragma once
#include "G_Renderable.h"
class G_Button : public G_Renderable
{
public:
	G_Button();
	~G_Button();

	void* onClick;
};

