#include "G_Text.h"



G_Text::G_Text():G_Renderable(){
	font = NULL;
	text = "";
}
G_Text::G_Text(std::string str, G_BitmapFont* bMap) {
	font = bMap;
	text = str;
	dst.x = 0;
	dst.y = 0;
	scale = 1;
}
G_Text::G_Text(std::string str, int nx, int ny, G_BitmapFont* bMap) {
	font = bMap;
	text = str;
	dst.x = nx;
	dst.y = ny;
	scale = 1;

}
G_Text::G_Text(std::string str, int nx, int ny, float nscale, G_BitmapFont* bMap) {
	font = bMap;
	text = str;
	dst.x = nx;
	dst.y = ny;
	scale = nscale;

}


G_Text::~G_Text(){
}
void G_Text::render(SDL_Renderer* renderer) {
	
	//If the font has been built
	if (font->mBitmap != NULL)
	{
		//Temp offsets
		int curX = dst.x, curY = dst.y;

		//Go through the text
		for (unsigned int i = 0; i < text.length(); ++i)
		{

			//If the current character is a space
			if (text[i] == ' ')
			{
				//Move over
				curX += font->mSpace;
			}
			//If the current character is a newline
			else if (text[i] == '\n')
			{
				//Move down
				curY += (int) scale*(font->mNewLine);

				//Move back
				curX = dst.x;
			}
			else
			{
				//Get the ASCII value of the character
				int ascii = (unsigned char)text[i];
				//Show the character
				//Set rendering space and render to screen
				SDL_Rect renderQuad = { curX, curY,(int)scale*(font->mChars[ascii].w), (int)scale*(font->mChars[ascii].h) };

				//Render to screen
				SDL_RenderCopyEx(renderer, font->mBitmap, &(font->mChars[ascii]), &renderQuad, NULL, NULL, SDL_FLIP_NONE);

				//Move over the width of the character with one pixel of padding
				curX += (int)scale*(font->mChars[ascii].w + 1);
			}
		}
	}
}