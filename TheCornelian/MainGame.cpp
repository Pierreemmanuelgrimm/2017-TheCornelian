#include "MainGame.h"

#include "res_path.h"
#include "cleanup.h"
#include "logSDLError.h"
using namespace std;
// Define Constants, Globals & Statics
// --> Here
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit..." << std::endl;
	SDL_Quit();
	int tmp;
	std::cin >> tmp;
	//close();
}
//void close() {
//	SDL_Quit();
//	exit(EXIT_FAILURE);
//}
MainGame::MainGame() {
	_window = NULL;
	_renderer = NULL;
	_font = NULL;
	_screenWidth = 1920;
	_screenHeight = 1080;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame() {
}

void MainGame::run() {
	initSystems();
	initTextures();
	gameLoop();
	//close();
}

void MainGame::initSystems() {
	// Initialize TTF	
	if (TTF_Init() < 0) {
		fatalError("TTF failed to intialize!");
	}
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fatalError("SDL failed to initialize");
	}

	// Initialize Window
	_window = SDL_CreateWindow("Island Escape", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
	}

	SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
	//SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	// Initialize renderer
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr) {
		fatalError("Renderer failed to create");
	}
	// Create OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		fatalError("SDL_GL context could not be created!");
	}

	// Initialize Glew
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}
	// Load images
	std::string path = getResourcePath("images") + "textUI.png";
	SDL_Surface* UITextBoxes = IMG_Load(path.c_str());
	if (!UITextBoxes) {
		fatalError("Couldnt load image!");
	}
	ImageTexture* UITextBox = new ImageTexture(0,0,1280,360,UITextBoxes);


	// Load Font
	path = getResourcePath("fonts") + "font2.ttf";
	int font_size = 35;
	_font = TTF_OpenFont(path.c_str(), font_size);
	if (!_font) {
		fatalError("Could not load font!");
	}

	// Create Button List
	_handle = 0x00000000;
	_inputStates.push_back(0);
	_inputStates[0] = 0;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Colors
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Color black = { 0x00, 0x00, 0x00, 0x00 };
	SDL_Color red = { 0xFF, 0x00, 0x00, 0x00 };
	SDL_Color beige = { 240,240, 170 };
	SDL_Color green = { 0,170,0 };
	//Quadrants
	//Top Left
	_quadrants.push_back(new Quadrant(0, 0, _screenWidth * 2 / 3, _screenHeight * 2 / 3, { 0x99 , 0xFF , 0xFF , 0xFF }, QuadDesc::TLEFT));
	//Top Right
	_quadrants.push_back(new Quadrant(_screenWidth * 2 / 3, 0, _screenWidth * 1 / 3, _screenHeight * 2 / 3, green, QuadDesc::TRIGHT));
	//Bot Left
	_quadrants.push_back(new Quadrant(0, _screenHeight * 2 / 3, _screenWidth * 2 / 3, _screenHeight * 1 / 3, { 0xFF , 0xFF , 0xFF , 0xFF }, QuadDesc::BLEFT));
	//Bot Right
	_quadrants.push_back(new Quadrant(_screenWidth * 2 / 3, _screenHeight * 2 / 3, _screenWidth * 1 / 3, _screenHeight * 1 / 3, { 0x00 , 0xFF , 0x00 , 0xFF }, QuadDesc::BLEFT));

	
	// Create Text input / Output

	RectTexture *inputTextBox = new RectTexture((*_quadrants[2]).getWidth() / 30, (*_quadrants[2]).getHeight() / 10, (28 * (*_quadrants[2]).getWidth()) / 30, 1 * (((*_quadrants[2]).getHeight()) / 8), beige);
	TextTexture *inputText = new TextTexture((*inputTextBox).getX(), (*inputTextBox).getY() + (3* font_size/8), (*inputTextBox).getWidth(), (*inputTextBox).getHeight(), "" ,black, _font);	
	RectTexture *outputTextBox = new RectTexture((*_quadrants[2]).getWidth() / 30, 3 * (*_quadrants[2]).getHeight() / 10, 29 * ((*_quadrants[2]).getWidth() / 30), 6 * (((*_quadrants[2]).getHeight()) / 10), beige);
	TextTexture *outputText = new TextTexture((*outputTextBox).getX(), (*outputTextBox).getY() + (3 * font_size / 8), (*outputTextBox).getWidth(), (*outputTextBox).getHeight() - font_size, "", black, _font);
	(*_quadrants[2]).addTexture(inputTextBox);
	(*_quadrants[2]).addTexture(inputText); // Index 1 = Text input
	_textText.push_back(inputText); // Index 0
	(*_quadrants[2]).addTexture(outputTextBox);
	(*_quadrants[2]).addTexture(outputText); // Index = 3 = Text output
	_textText.push_back(outputText); // Index 1
	(*_quadrants[2]).addTexture(UITextBox);

	//Create exit button
	Button *exitButton = new Button(540, 300, 40, 40, 0x00000001,0, "X", white, red, _font);
	_buttons.push_back(exitButton);
	(*_quadrants[3]).addTexture(exitButton);
	
	// Create Movement boxes
	int xx[4] = { 490, 880 , 490 , 100 };
	int yy[4] = { 520, 310 , 100 , 310 };
	Texture * a;
	for (int i = 0; i < 4; i++) {
		a = new Button(xx[i], yy[i], 300, 100, 0x10000002, 0, "", black, white, _font);
		_buttons.push_back(static_cast<Button*>(a)); // Index 2 - 5
		(*_quadrants[0]).addTexture(a); // Occupy [0 - 3]
		static_cast<Button*>((*_quadrants[0]).getTexture(i))->setVisible(0);
	}
	// Initialize random
	srand(time(NULL));
	// Initialize opponents
	
	Quadrant* opponentBox = new  Quadrant(0,0,(*_quadrants[0]).getWidth(), (*_quadrants[0]).getHeight(),beige, QuadDesc::EMPTY);

	for (unsigned int i = 0; i < 5; i++) {
		Mob* noMob = new Mob();
		_opponents.push_back(noMob);
		Quadrant* q = new Quadrant(10 ,  10 + 110*i , 400, 100, white, QuadDesc::EMPTY);
		PlayerNameTexture* p1 = new PlayerNameTexture(10, 10, 0, 0, _opponents[i], black, _font);
		PlayerHealthText* p2 = new PlayerHealthText(10, 30, 0, 0, _opponents[i], black, _font, "health");
		RectTexture* p3 = new RectTexture(180, 50, 200, 30, black);
		PlayerHealthBox* p4 = new PlayerHealthBox(180, 50, 200, 30, _opponents[i], green, "health");
		PlayerHealthText* p5 = new PlayerHealthText(10, 50, 0, 0, _opponents[i], black, _font, "level");

		(*q).addTexture(p1);
		(*q).addTexture(p2);
		(*q).addTexture(p3);
		(*q).addTexture(p4);
		(*q).addTexture(p5);
		(*_quadrants[0]).addTexture(q);
		static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(0); //Indices 4 -> 8
	}
	Mob* noMob = new Mob();
	_opponents.push_back(noMob); // Index 5 will become blank copy

	// Create map
	map.init();
	map.setStartingLocation(mapX, mapY);

	// Initialise scrap to finish game to zero
	_scrap = 0;
	_objective = 25;

}
void MainGame::initTextures() {
	std::string path;

	// **** INITIALIZE COLORS *********************
	gColors.push_back({ 0xFF,0x00,0x00,0x00 }); // RED
	gColors.push_back({ 0x00,0xFF,0x00,0x00 }); // BLUE
	gColors.push_back({ 0x00,0x00,0xFF,0x00 }); // GREEN
	gColors.push_back({ 0xFF,0xFF,0xFF,0x00 }); // WHITE
	gColors.push_back({ 0x00,0x00,0x00,0x00 }); // BLACK

	// **** INITIALIZE FONTS ***********************
	path = getResourcePath("fonts");
	gFonts.push_back(new G_BitmapFont(path + "default.gif", _renderer, gColors[BLACK])); // DEFAULT_BLACK
	gFonts.push_back(new G_BitmapFont(path + "default.gif", _renderer, gColors[RED])); // DEFAULT_RED
	
	// **** INITIALIZE TEXTURES *********************
	path = getResourcePath("images");
	gTextures.push_back(loadTexture(path + "red.png", _renderer)); //RED_BLOCK
	gTextures.push_back(loadTexture(path + "green.bmp", _renderer)); //GREEN_BLOCK
	
	//**************** TEST ***********************
	G_Container* Gg = new  G_Container();
	Gg->updatePos(500, 500);
	Gg->pushT(new G_Image(gTextures[RED_BLOCK]));
	Gg->pushT(new G_Image(gTextures[GREEN_BLOCK]));
	Gg->pushT(new G_Text("ABCDE HI hi",0,0,4, gFonts[DEFAULT_BLACK]));
	//gRenders.push_back(Gg);

}
SDL_Texture* MainGame::loadTexture(std::string file, SDL_Renderer *ren) {
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture* texture = nullptr;
	//Load the image
	SDL_Surface* loadedImage = IMG_Load(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr) {
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadPNG");
	}
	return texture;
}
void MainGame::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		handleEvent();
		drawGame();
	}
}
void MainGame::processInput() {
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		TextTexture *t = _textText[0];
		std::string  str = t->getString();
		switch (evnt.type) {
		case SDL_QUIT:
			_handle = 0x00000001;
			break;
		case SDL_KEYUP:
			_inputStates[0] = (_inputStates[0] && (evnt.key.keysym.sym != 13));
				break;
		case SDL_KEYDOWN:
			// Set input states
				_inputStates[0] = (evnt.key.keysym.sym == 13);

			if (evnt.key.keysym.sym == SDLK_BACKSPACE && str.length() > 0) {
				str.pop_back();
				(*t).setString(str);
			}
			else if (evnt.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
				SDL_SetClipboardText(str.c_str());
			}
			else if (evnt.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
				str = SDL_GetClipboardText();
				(*t).setString(str);
			}
			break;

		case SDL_TEXTINPUT:
				//Not Copy & Pasting
				if (!((evnt.text.text[0] == 'c' || evnt.text.text[0] == 'C') && (evnt.text.text[0] == 'v' || evnt.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
					str += evnt.text.text;		
					(*t).setString(str);
				}
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
			for (unsigned int i = 0; i < _buttons.size(); i++) {
				if ((*_buttons[i]).isClicked(evnt.motion.x, evnt.motion.y)) {
					_handle = ((*_buttons[i]).getHandle());
					_id = ((*_buttons[i]).getID());
					return;
				}
			}
			break;
		}
	}
}
void MainGame::drawGame() {
	//Clear
	SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(_renderer);
	//Render all 4 Quadrants
	for (unsigned int i = 0; i < _quadrants.size(); i++) {
		(*_quadrants[i]).render(_renderer);
	}
	//SDL_Rect renderQuad;
	//renderQuad.x = 0;
	//renderQuad.y = 0;
	//SDL_QueryTexture(sFonts[0]->mBitmap, NULL, NULL, &renderQuad.w, &renderQuad.h);
	//renderQuad.w /= 2;
	//renderQuad.h /= 2;
	//SDL_RenderCopyEx(_renderer, sFonts[0]->mBitmap, NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);

	for (unsigned int i = 0; i < gRenders.size(); i++) {
		gRenders[i]->render(_renderer);
	}
	SDL_RenderPresent(_renderer);
}
void MainGame::handleEvent() {
	switch (_handle) {
		//set game to exit
	case 0x00000001:
		_gameState = GameState::EXIT;
		break;

		//Start Game
	case 0x00000000:
		_textText[1]->addStringEnd("Welcome to my Game!");
		_textText[1]->addStringEnd("Please enter your name:");
		_handle = 0x00000002;
		break;

		// Require name input & create character
	case 0x00000002:
		if (_inputStates[0]) {
			_textText[1]->addStringEnd(_textText[0]->getString());
			//Mob*  player = new Mob((_textText[0]->getString()), 1000, 1000, 1000, false, false, 0);
			Mob* player = new Mob(0);
			//Mob* player2 = new Mob(0);
			//Mob* player3 = new Mob(0);
			//Mob* player4 = new Mob(0);
			//Mob* player5 = new Mob(0);
			player->setName((_textText[0]->getString()));
			player->setStrength(50);
			player->setDexterity(50);
			player->setArmor(50);
			player->setPerception(50);
			//Mob*  player2 = new Mob((_textText[0]->getString()), 1000, 1000, 1000, false, false, 0);
			//Mob*  player3 = new Mob((_textText[0]->getString()), 1000, 1000, 1000, false, false, 0);
			_textText[0]->clear();
			addPlayer(player);
			//addPlayer(player2);
			//addPlayer(player3);
			//addPlayer(player4);
			//addPlayer(player5);
			_handle = 0x10000000;
		}
		break;

		//DEBUG
	case 0x00000003: {
		std::string a;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				a = a + " " + std::to_string((*map.getLocation(i, j)).getID());
			}
			_textText[1]->addStringEnd(a);
			a = "";
		}
	}
					 _handle = 0x00000004;
					 break;

					 // DEBUG
	case 0x00000004:
		_textText[1]->addStringEnd(std::to_string(mapX));
		_textText[1]->addStringEnd(std::to_string(mapY));
		_handle = 0x10000000;
		break;

		// SHOW MOVEMENT BUTTONS
	case 0x10000000: {
		vector<Location*> tmap;
		tmap.push_back(map.getLocation(mapX, mapY + 1));
		tmap.push_back(map.getLocation(mapX + 1, mapY));
		tmap.push_back(map.getLocation(mapX, mapY - 1));
		tmap.push_back(map.getLocation(mapX - 1, mapY));
		std::vector<int> ind;
		ind.push_back(0);
		ind.push_back(1);
		ind.push_back(2);
		ind.push_back(3);
		if (map.getLocation(mapX, mapY)->getID() == 6) std::random_shuffle(ind.begin(), ind.end());
		for (int i = 0; i < 4; i++) {
			int id = tmap[ind[i]]->getID();
			(static_cast<TextTexture*>(static_cast<Button*>((*_quadrants[0]).getTexture(i))->getTexture(0)))->setString(tmap[ind[i]]->getString());
			static_cast<Button*>((*_quadrants[0]).getTexture(i))->setID(ind[i]);
			static_cast<Button*>((*_quadrants[0]).getTexture(i))->setVisible(1);
			bool clickable = 1;
			SDL_Color col = { 0xFF, 0xFF, 0xFF, 0xFF };
			if (id == 0 || id == 1) {
				clickable = 0;
				col = { 0xFF, 0x20, 0x20, 0xFF };
			}

			static_cast<Button*>((*_quadrants[0]).getTexture(i))->setIsClickable(clickable);
			static_cast<Button*>((*_quadrants[0]).getTexture(i))->setColor(col);
		}

		_handle = 0x10000001;
	}
	 break;

	 // EMPTY DO NOTHING
	case 0x10000001:

		break;

		// MOVING BUTTON HAS BEEN CLICKED
	case 0x10000002:
		switch (_id) {
		case 0:
			mapY++;
			break;
		case 1:
			mapX++;
			break;
		case 2:
			mapY--;
			break;
		case 3:
			mapX--;
			break;
		}
		//Make buttons invisible
		for (unsigned int i = 0; i < _buttons.size(); i++) {
			if (_buttons[i]->getHandle() == 0x10000002) {
				_buttons[i]->setVisible(0);
				_buttons[i]->setIsClickable(0);
			}
		}
		
		if (map.getLocation(mapX, mapY)->getID() == 9) {
			// CHECK VICTORY CONDITION
			if(_scrap == _objective){
				_handle = 0xF0000000;
				return;
			}
			// REFRESH ENERGY
			for (unsigned int i = 0; i < _players.size(); i++) {
				_textText[1]->addStringEnd("Your energy is replenished as you visit the base.");
				_players[i]->setEnergy(_players[i]->getMaxEnergy());
			}
		}
		_handle = 0x10000003;
		break;

		// TRIGGER EVENT ON MOVEMENT
	case 0x10000003:
		_handle = map.getLocationHandle(mapX, mapY, _id);
		std::cout << _handle << std::endl;
		break;
		// ADD OPPONENTS
	case 0x10000004:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Mob(1);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// YOU ARRIVE ON PIRATE BASE
	case 0x10000005:
		for (int i = 0; i < 5; i++) {
			*_opponents[i] = Pirate(5);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT RANDOM PIRATES
	case 0x10000006:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Pirate(0);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT WEAK PIRATES
	case 0x10000007:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Pirate(1);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT YOUR LEVEL PIRATES
	case 0x10000008:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Pirate(_players[0]->getLevel());
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// YOU ARRIVE ON CANNIBAL BASE
	case 0x10000009:
		for (int i = 0; i < 5; i++) {
			*_opponents[i] = Cannibal(i, 5);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// YOU MOVE AND THERE IS NOTHING
	case 0x10000010:
		_textText[1]->addStringEnd("You encounter nothing while traveling.");
		_handle = 0x10000000;
		break;
		// COMBAT RANDOM CANNIBAL
	case 0x10000011:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Cannibal(i, 0);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT WEAK CANNIBALS
	case 0x10000012:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Cannibal(i, 1);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT YOUR LEVEL CANNIBALS
	case 0x10000013:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Cannibal(i, _players[0]->getLevel());
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT RANDOM ANIMALS
	case 0x10000014:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Animal(i, 0);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT WEAK ANIMALS
	case 0x10000015:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Animal(i, 1);
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
		// COMBAT YOUR LEVEL ANIMALS
	case 0x10000016:
		for (int i = 0; i < ((rand() % 4) + 1); i++) {
			*_opponents[i] = Animal(i, _players[0]->getLevel());
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(1);
		}
		_handle = 0x11000000;
		break;
	// INITIALIZE COMBAT
	case 0x11000000:
	{
		_combat = new Combat();
		*_combat = Combat("visible", _players, _opponents, _textText[1]);
		_textText[1]->addStringEnd("The fight starts...");
		_handle = 0x11000001;
	}
	gameTime = clock();
	break;
	// CONTINUE COMBAT
	case 0x11000001:
		if (!(_combat->getTeamStatus(_players))) {
			_handle = 0x11000003; // Lose
			return;
		}
		if (!(_combat->getTeamStatus(_opponents))) {
			_handle = 0x11000002; // Win
			return;
		}
		//if (((float)(clock() - gameTime) / CLOCKS_PER_SEC) > 0.1) {
			_combat->fight();
			gameTime = clock();
		//}
		break;
		// END COMBAT WITH WIN
	case 0x11000002:
		_combat->~Combat();
		updatePlayer();
		for (unsigned int i = 0; i < 5; i++) {
			*_opponents[i] = *_opponents[5];
			static_cast<Quadrant*>((*_quadrants[0]).getTexture(i + 4))->setVisible(0);
		}
		_handle = 0x10000000;
		break;

		// END COMBAT WITH LOSS
	case 0x11000003:
		_handle = 0x00000001;
		break;
	// TRIP
	case 0x11010001:
		{
			std::string str;
			int a = rand() % _players.size();
			std::cout << a << std::endl;
			str += _players[a]->getName() + " tripped,";
			if (_players[a]->getDexterity() < (10 + (rand() % 10))) {
				int damage = 40 + rand() % 20 - _players[a]->getArmor();
				if (damage <= 0) {
					str += " but takes no damage";
				}
				else {
					_players[a]->addHealth(-1*damage);
					str += " taking " + to_string(damage) + " damage";
				}

			}
			else {
				str += " but did not fall over";
			}
			_textText[1]->addStringEnd(str);
			updatePlayer();
			_handle = 0x10000000;
		}
		break;
	// FALLING ROCKS
	case 0x11010002:
		{
			_textText[1]->addStringEnd("The mountain shakes and rocks start falling on you");
			std::string str;
			for (unsigned int i = 0; i < _players.size(); i++) {
				if (!(_players[i]->getIsDead())) {
					str = _players[i]->getName();
					if (_players[i]->getDexterity() < (10 + (rand() % 10))) {
						int damage = 80 + rand() % 40 - 2 * _players[i]->getArmor();
						if (damage <= 0) {
							str += " takes no damage";
						}
						else {
							_players[i]->addHealth(-1 * damage);
							str += " takes " + to_string(damage) + " damage";
						}
					}
					else {
						str += " dodges the rocks";
					}
					_textText[1]->addStringEnd(str);				
				}
			}
			updatePlayer();
			_handle = 0x10000000;
		}
		break;
	// SMALL CANNIBAL TRAP
	case 0x11010003:
		{
			std::string str;
			int a = rand() % _players.size();
			std::cout << a << std::endl;
			str += _players[a]->getName() + " activates a trap,";
			if (_players[a]->getDexterity() < (15 + (rand() % 10))) {
				int damage = 40 + rand() % 20 - _players[a]->getArmor();
				if (damage <= 0) {
					str += " but takes no damage";
				}
				else {
					_players[a]->addHealth(-1 * damage);
					str += " taking " + to_string(damage) + " damage";
				}

			}
			else {
				str += " but mangages to avoid getting hurt";
			}
			_textText[1]->addStringEnd(str);
			updatePlayer();
			_handle = 0x10000000;
		}
		break;

	// LARGE CANNIBAL TRAP
	case 0x11010004:
		{
			_textText[1]->addStringEnd("You stumble upon a large trap");
			std::string str;
			for (unsigned int i = 0; i < _players.size(); i++) {
				if (!(_players[i]->getIsDead())) {
					str = _players[i]->getName();
					if (_players[i]->getDexterity() < (15 + (rand() % 10))) {
						int damage = 80 + rand() % 40 - 2 * _players[i]->getArmor();
						if (damage <= 0) {
							str += " takes no damage";
						}
						else {
							_players[i]->addHealth(-1 * damage);
							str += " takes " + to_string(damage) + " damage";
						}
					}
					else {
						str += " manages to avoid getting hurt";
					}
					_textText[1]->addStringEnd(str);
				}
			}
			updatePlayer();
			_handle = 0x10000000;
		}
		break;
	// FIND ANIMAL
	case 0x11020001:
		{
			std::string str;
			int rnd = rand() % _players.size();
			str = _players[rnd]->getName() + " seems a wild animal and attemps to tame it, ";
			
			if (_players[rnd]->getDexterity() + _players[rnd]->getStrength() < 30 + rand() % 20) {
				str += "but fails to capture it";
			}
			else {
				Animal* animal = new Animal(-1, (rand() % _players[rnd]->getLevel()) + 1);
				animal->setTeam(0);
				addPlayer(animal);
				str += "and succeeded";
			}
			_textText[1]->addStringEnd(str);
		}
		_handle = 0x10000000;
		break;
	// FIND A PERSON
	case 0x11020002:
		{
		int s = rand() % 100;
		std::string str;
		int level = (rand() % _players[0]->getLevel()) - 2;
		Mob* wanderer = new Mob(1);
		wanderer->setName("Nameless Wanderer");

		str = "You meet a wanderer, and attempt to talk to him, ";
			if (s > 95) {
				str += " he is friendly and decides to join you";
				if (level < 1) level = 1;
				wanderer->setTeam(0);
				addPlayer(wanderer);
				_handle = 0x10000000;
			}
			else {
				str += " he feels threatened and attacks";
				*_opponents[0] = *wanderer;
				_opponents[0]->setName("Nameless Wanderer");
				static_cast<Quadrant*>((*_quadrants[0]).getTexture(4))->setVisible(1);
				_handle = 0x11000000;
			}
		
		_textText[1]->addStringEnd(str);
		}
		break;
	case 0xF0000000:
	// end of the game;
	break;
	}
}
void MainGame::addPlayer(Mob* player) {
	if (_players.size() == 5) return;
	_players.push_back(player);
	int l = _players.size() - 1;
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Color black = { 0x00, 0x00, 0x00, 0x00 };
	SDL_Color red = { 0xFF, 0x00, 0x00, 0x00 };
	SDL_Color green = { 0x00, 0xFF, 0x00, 0x00 };
	Quadrant* q = new Quadrant(_screenWidth / 30, 10 + l * 2 * _screenHeight / 15, 8 * _screenWidth / 30, 2 * _screenHeight / 16, white, QuadDesc::EMPTY);
	PlayerNameTexture* p1 = new PlayerNameTexture(10, 10, 0, 0, player, black, _font);

	
	RectTexture* p2 = new RectTexture(10, 60, 200, 30, black);
	PlayerHealthBox* p3 = new PlayerHealthBox(10,60,200,30,player, green, "health");
	PlayerHealthText* p4 = new PlayerHealthText(20, 70, 0, 0, player, white, _font, "health");
	
	RectTexture* p5 = new RectTexture(10, 100, 200, 30, black);
	PlayerHealthBox* p6 = new PlayerHealthBox(10, 100, 200, 30, player, green, "energy");
	PlayerHealthText* p7 = new PlayerHealthText(20, 110, 0, 0, player, white, _font, "energy");

	PlayerHealthText* p8 = new PlayerHealthText(10, 40, 0, 0, player, black, _font, "level");
	PlayerHealthText* p9 = new PlayerHealthText(110, 40, 0, 0, player, black, _font, "experience");

	PlayerHealthText* p10 = new PlayerHealthText(240, 42, 0, 0, player, black, _font, "strength");
	PlayerHealthText* p11 = new PlayerHealthText(240, 67, 0, 0, player, black, _font, "perception");
	PlayerHealthText* p12 = new PlayerHealthText(240, 92, 0, 0, player, black, _font, "dexterity");
	PlayerHealthText* p13 = new PlayerHealthText(240, 117, 0, 0, player, black, _font, "armor");

	(*q).addTexture(p1);
	(*q).addTexture(p2);
	(*q).addTexture(p3);
	(*q).addTexture(p4);
	(*q).addTexture(p5);
	(*q).addTexture(p6);
	(*q).addTexture(p7);
	(*q).addTexture(p8);
	(*q).addTexture(p9);
	(*q).addTexture(p10);
	(*q).addTexture(p11);
	(*q).addTexture(p12);
	(*q).addTexture(p13);
	(*_quadrants[1]).addTexture(q);
}
void MainGame::updatePlayer() {
	vector<Mob*> a;
	for (unsigned int i = 0; i < _players.size(); i++) {
		if (!(_players[i]->getIsDead())) a.push_back(_players[i]);
	}
	for (unsigned int i = 0; i < a.size(); i++) {
		*(_players[i]) = *a[i];
	}
	for (unsigned int j = a.size(); j < _players.size(); j++) {
		_players[j]->~Mob();
		_players.pop_back();
		_quadrants[1]->popLast();
	}
}
void MainGame::o(std::string str) {
	_textText[1]->addStringEnd(str);
}