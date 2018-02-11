#pragma once 
#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <GL\glew.h>


#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

#include "CornEngine.h"

#include "Texture.h"
#include "TextTexture.h"
#include "RectTexture.h"
#include "Quadrant.h"
#include "ImageTexture.h"
#include "Button.h"
#include "PlayerNameTexture.h"
#include "PlayerHealthText.h"
#include "PlayerHealthBox.h"

#include "Map.h"
#include "Mob.h"
#include "Pirate.h"
#include "Cannibal.h"
#include "Animal.h"
#include "Combat.h"

void fatalError(std::string);
//void close();

enum class GameState {PLAY, EXIT};
	//GameState - Describes State of Game
	//Game is either PLAY (ie running) or EXIT
enum textureID {
};
class MainGame {
public:
	//Default Constructor
	MainGame();

	//Destructor
	~MainGame();

	// -- RUN -----
	void run();
	//run() - Run game
	void o(std::string);
	
private:
	//******************************
	//Member functions
	
	void initSystems();
		//Initializes Game
	void initTextures();
		//Loads all textures and initializes textures
	SDL_Texture* loadTexture(std::string file, SDL_Renderer *ren);
		//Loads individual texture;
	void gameLoop();
		//Main game loop
	void processInput();
		//Input Processing
	void drawGame();
		//Render update

	SDL_Window* _window;
		//Window to which all will be rendered
	SDL_Renderer* _renderer;
		//Renderer used to render textures

	vector<G_BitmapFont*> gFonts;
		//Game fonts, holds font data
	enum gFontID {
		DEFAULT_BLACK,
		DEFAULT_RED
	};//Enum holding all predefined values of Fonts (fonts are preloaded, no dynamic loading), this list keeps track of loaded fonts

	vector<SDL_Texture*> gTextures;
		//Game textures, holds actual texture
	enum gTextureID {
		RED_BLOCK,
		GREEN_BLOCK
	};//Enum holding all predefined textures that will be loaded

	vector<SDL_Color> gColors;
		//Holds all colors to use in the game
	enum gColorID {
		RED,
		GREEN,
		BLUE,
		WHITE,
		BLACK
	};//Enum holding all predefined colors

	vector<G_Renderable*> gRenders;
		//Instance of all objects that will be rendered, contains pointer to actual texture
	

	//***************************************
	vector<SDL_Texture*> _textures;
	vector<SDL_Texture*> _fonts;
	void addPlayer(Mob*);
	void updatePlayer();
	void handleEvent();
		// Handle Event
		//0x0 represents all main game accesses 
		//0x1 represents all exploration events
	int mapX, mapY;
	int _handle;
	int _id;
	
	TTF_Font* _font;
	vector<Quadrant*> _quadrants;
	vector<Mob*> _players;
	vector<Mob*> _opponents;
	Map map;
	vector<bool> _inputStates;
	int _screenWidth;
	int _screenHeight;
	vector<Button*> _buttons;
	vector<TextTexture*> _textText;
	GameState _gameState;
	int _scrap;
	int _objective;
	Combat* _combat;
	clock_t gameTime;
};

#endif
