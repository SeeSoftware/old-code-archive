#include "Game.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <algorithm>


Game::Game()
{
}


Game::~Game()
{
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::run()
{
	init(1280, 720);
	gameLoop();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
long long findNextFreeIdThreadFunc(GESFML::SpriteBatch *_spriteBatch)
{
	for (long long i = 0;i < _spriteBatch->getPhysicSpriteBatch().size() + 1;i++)
	{
		if (!_spriteBatch->isExistingPhysicSprite(i))
		{
			return i;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
void updateSpritebatch(GESFML::Window *_window, GESFML::SpriteBatch *_spriteBatch,bool *canUpdate,bool *canSpawn)
{
	while (_window->isOpen())
	{

		while (!*canUpdate)
		{
			std::this_thread::yield();
		}
		*canSpawn = false;
		if (*canUpdate)
		{
			_spriteBatch->updateAllPhysicSprites();
			_spriteBatch->worldStep();
		}
		*canSpawn = true;
	}
}*/


/*
void occlusionThread(GESFML::SpriteBatch *_spriteBatch, GESFML::Window *_window, int scrWidth, int scrHeight, bool *canUpdate, bool *canDraw, bool *isDrawing)
{
	while (_window->isOpen())
	{

		while (*isDrawing)
		{
			std::this_thread::yield();
		}

			*canDraw = false;

			for (long long i = 0;i < _spriteBatch->getPhysicSpriteBatch().size() + 1;i++)
			{
				if (_spriteBatch->isExistingPhysicSprite(i))
				{

					float x = _spriteBatch->getPhysicSpritePosition(i).x;
					float y = _spriteBatch->getPhysicSpritePosition(i).y;
					float w = _spriteBatch->getPhysicSpriteSize(i).x;
					float h = _spriteBatch->getPhysicSpriteSize(i).y;

					


					if (_window->getWindow().mapCoordsToPixel(sf::Vector2f(x, y)).x < 0)
					{
						_spriteBatch->setPhysicSpriteDraw(i, false);
					}
					else
					{
						_spriteBatch->setPhysicSpriteDraw(i, true);
					}

					if (_window->getWindow().mapCoordsToPixel(sf::Vector2f(x, y)).x > scrWidth)
					{
						_spriteBatch->setPhysicSpriteDraw(i, false);
					}
					else
					{
						_spriteBatch->setPhysicSpriteDraw(i, true);
					}

				
			}
		}

			*canDraw = true;
	}
}*/
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
void drawThread(GESFML::SpriteBatch *_spriteBatch, GESFML::Window *_window, bool *canDraw, bool *isDrawing, sf::Time *frametime)
{
	while (_window->isOpen())
	{


	}
}
/*
void generateWorldThread(void *(Game::*function)())
{
	function();
}*/

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void generateWorldThreadFunc(GESFML::SpriteBatch *_spriteBatch, bool *_canSpawn, bool *_canUpdate, bool *_canDraw, bool *_isDrawing, int *_ammountOfChunksGenerated,long long *_ammountOfBlocksPlaced, bool *_runGenerateFunction, std::unordered_map<std::string, sf::Texture> *_textureBatch, std::unordered_map<long long, std::unordered_map<long long, long long> > *_worldBlocks)
{
	while (!*_runGenerateFunction)
	{
		std::this_thread::yield();
	}
	while (*_isDrawing)
	{
		std::this_thread::yield();
	}
	*_canDraw = false;
	while (!*_canSpawn)
	{
		std::this_thread::yield();
	}
	*_canUpdate = false;
		while (*_ammountOfChunksGenerated <= AMMOUNT_OF_CHUNKS_TO_GENERATE-1)
		{
			
			for (int k = 0; k < 32; k++)
			{
				for (int j = 0; j < 16;j++)
				{
					
					long long id = findNextFreeIdThreadFunc(_spriteBatch);

					if (*_canSpawn)
					{
						//_spriteBatch->getIdsToIgnoreWhileDrawingPhysicSpritesArray().push_back(id);
						_spriteBatch->createPhysicSpriteBox(id, j * BLOCK_PIXELSIZE + (*_ammountOfChunksGenerated * BLOCK_PIXELSIZE * 16) + BLOCK_PIXELSIZE / 2 - (AMMOUNT_OF_CHUNKS_TO_GENERATE / 2 * BLOCK_PIXELSIZE * 16), (BLOCK_PIXELSIZE / 2) + k * BLOCK_PIXELSIZE , BLOCK_PIXELSIZE, BLOCK_PIXELSIZE, false, 1, 0, 0.2f, (*_textureBatch)["Texture_Test"], sf::Color(255, 255, 255, 255));
						//_spriteBatch->createPhysicSpriteShadow(id, -7, -7, 75);
						(*_worldBlocks)[j + ((*_ammountOfChunksGenerated) * 16)][k] = id;
						*_ammountOfBlocksPlaced += 1;
						
					}
					
				}
			}
			//std::cout << *generation;
			*_ammountOfChunksGenerated += 1;
			_spriteBatch->setIdsToIgnoreWhileDrawingPhysicSprites({});
		}
		*_canDraw = true;
		*_canUpdate = true;
}





//EXISTING GUI ELEMENTS
//Menu_Background  = The very background of everything

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::init(int w, int h)
{
	//create The window and world
	_width = w;
	_height = h;
	_window.create(sf::VideoMode(w, h), "Some War Game", true, 60);
	_spriteBatch.initWorld(b2Vec2(0, 9.8f), 10, 60, true);
	//load Textures
	_textureBatch["Blank"] = GESFML::HelperFunctions::createBlankTexture(256, 256, GESFML::Color(255, 255, 255).getSfColor());
	_textureBatch["Texture_Test"].loadFromFile("Resources/Textures/Dev.png");
	_textureBatch["Title_Screen"].loadFromFile("Resources/Textures/TitleScreen.png");
	_textureBatch["Player_Animation"].loadFromFile("Resources/Textures/PlayerAnimation.png");

	//load Default Font
	_DefaultFont.loadFromFile("Resources/Fonts/DefaultFont.ttf");
	

	//creating the menu background
	long long tmpid;
	tmpid = findNextFreeIdSprite();
	_spriteBatch.createSprite(tmpid, 0, 0, _width, _height, _textureBatch["Title_Screen"], GESFML::Color(255, 255, 255).getSfColor());
	_spriteBatch.setSpriteDrawOrder(tmpid, 0);
	//assining a identifier to the background
	_guiElements["Menu_Background"] = tmpid;

	//create a sprite that will be the start button
	tmpid = findNextFreeIdSprite();
	_spriteBatch.createSprite(tmpid, 500, 250, 250, 75, _textureBatch["Blank"], GESFML::Color(255, 0, 0).getSfColor());
	_spriteBatch.setSpriteUserDataStr(tmpid, "Menu_Button_Start");
	_spriteBatch.createSpriteShadow(tmpid, -7, -7,75);
	//assinging identifier to start button
	_guiElements["Menu_Button_Start"] = tmpid;

	//creating a lable for the start button
	_spriteBatch.createText(500, 570, 265, 1, 1, 35, _DefaultFont, "Start Game", GESFML::Color(255, 255, 255, 255).getSfColor());
	_guiElements["Menu_Button_Start_Label"] = 500;
	
	_window.setViewSize(sf::Vector2f(_width, _height));
	_window.setViewCenter(sf::Vector2f(_width / 2, _height / 2));
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Game::gameLoop()
{
	
	//create Threads
	//std::thread drawThreadT(drawThread, &_spriteBatch, &_window, &_canDraw, &_isDrawing, &_frametime);
	std::thread generateWorldT(generateWorldThreadFunc, &_spriteBatch, &_canSpawn, &_canUpdate, &_canDraw, &_isDrawing, &_ammountOfChunksGenerated,&_ammountOfBlocksPlaced,&_runGenerateFunction, &_textureBatch, &_worldBlocks);


	while (_window.isOpen())
	{
		//while we cant update
		_window.updateFps();
		if (_canUpdate)
		{
			_canSpawn = false;
			if (_canUpdate)
			{
				//update world
				_spriteBatch.worldStep();
				_spriteBatch.updateAllPhysicSprites();
			}
			_canSpawn = true;
		}

		//Input processing and Entity Processing
		input();
		processEntities();


		if (!_canDraw)
		{
			_window.updateFps();
			_window.clear(GESFML::Color(0, 128, 255).getSfColor());
			_spriteBatch.drawSprites(_window);
			_spriteBatch.drawAllText(_window);
			_window.display();
			_frametime = sf::seconds(_window.getFrameTime().asSeconds() / _window.getFps());
		}
		std::this_thread::yield();
		_isDrawing = true;
		if (_canDraw)
		{

			_window.clear(GESFML::Color(0, 128, 255).getSfColor());
			_spriteBatch.drawAllOcclusion(_window, sf::IntRect(_window.getWindow().mapPixelToCoords(sf::Vector2i(0, 0)).x, _window.getWindow().mapPixelToCoords(sf::Vector2i(0, 0)).y, _width+ _window.getWindow().mapPixelToCoords(sf::Vector2i(0, 0)).x, _height+_window.getWindow().mapPixelToCoords(sf::Vector2i(0, 0)).y));
			//_spriteBatch.drawAllOcclusion(_window, sf::IntRect(0,0,_width,_height));
			//_spriteBatch.drawAllFast(_window);
			_window.display();

			std::cout << _window.getFps() << "\n";
		}
		_isDrawing = false;

		_frametime = sf::seconds(_window.getFrameTime().asSeconds());

	}

	
	//exit programm
	//drawThreadT.join();
	generateWorldT.join();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::input()
{
	_mousePressed = -1;
	_mouseReleased = -1;
	_keyPressed = -1;
	_keyReleased = -1;
	//int mousePressed = -1;
	//int mouseReleased = -1;

	sf::Event event;
	if (_window.pollEvent(event))
	{

		_mousePos = GESFML::Vector2D(event.mouseMove.x, event.mouseMove.y);

		switch (event.type)
		{
			//if we press the close button
		case sf::Event::Closed:
			_window.close();		//close window
			break;

		case sf::Event::KeyPressed:
			_keyboardInput.pressKey(event.key.code);
			_keyPressed = _keyboardInput.getKeyPressed();
			break;
		case sf::Event::KeyReleased:
			_keyboardInput.releaseKey(event.key.code);
			_keyReleased = _keyboardInput.getKeyReleased();
			break;
		case sf::Event::MouseButtonPressed:
			_mouseInput.pressKey(event.mouseButton.button);
			_mousePressed = _mouseInput.getKeyPressed();
			_mousePos = GESFML::Vector2D(event.mouseButton.x, event.mouseButton.y);

			break;
		case sf::Event::MouseButtonReleased:
			_mouseInput.releaseKey(event.mouseButton.button);
			_mouseReleased = _mouseInput.getKeyReleased();
			break;
		default:
			break;
		}

		

	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game::processEntities()
{

	for (auto x : _spriteBatch.getPhysicSpriteBatch())
	{
		//---------------------------------------------------------------------------------------------------
		if (_spriteBatch.getPhysicSpriteUserDataStr(x.first) == "Game_Player")
		{
			_entityDataNum[x.first]["Time"] += _frametime.asSeconds()*4;

			if (!_keyboardInput.getKey(sf::Keyboard::A) && !_keyboardInput.getKey(sf::Keyboard::D))
			{


				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 0)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 1)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(30, 0), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 2)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(60, 0), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 3)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(90, 0), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
			}
			//-----------
			if (_keyPressed == sf::Keyboard::A)
			{
				_entityDataNum[x.first]["Time"] == 0;
			}

			if (_keyboardInput.getKey(sf::Keyboard::A))
			{
				_spriteBatch.setPhysicSpriteVelocity(x.first, GESFML::Vector2D(-150, _spriteBatch.getPhysicSpriteVelocity(x.first).y).getB2Vec());
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 0)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(0, 62), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 1)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(30, 62), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 2)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(60, 62), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 3)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(90, 62), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
			}
			if (_keyReleased == sf::Keyboard::A)
			{
				_entityDataNum[x.first]["Time"] == 0;
				_spriteBatch.setPhysicSpriteVelocity(x.first, GESFML::Vector2D(0, _spriteBatch.getPhysicSpriteVelocity(x.first).y).getB2Vec());
			}
			//--------
			if (_keyPressed == sf::Keyboard::D)
			{
				_entityDataNum[x.first]["Time"] == 0;
			}

			if (_keyboardInput.getKey(sf::Keyboard::D))
			{
				_spriteBatch.setPhysicSpriteVelocity(x.first, GESFML::Vector2D(150, _spriteBatch.getPhysicSpriteVelocity(x.first).y).getB2Vec());
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 0)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(0, 124), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 1)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(30, 124), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 2)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(60, 124), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 3)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(90, 124), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
			}
			if (_keyReleased == sf::Keyboard::D)
			{
				_entityDataNum[x.first]["Time"] == 0;
				_spriteBatch.setPhysicSpriteVelocity(x.first, GESFML::Vector2D(0, _spriteBatch.getPhysicSpriteVelocity(x.first).y).getB2Vec());
			}

			if (_spriteBatch.testPointPhysicSprite(_spriteBatch.getPhysicSpritePosition(x.first).x-14, _spriteBatch.getPhysicSpritePosition(x.first).y + 33) || _spriteBatch.testPointPhysicSprite(_spriteBatch.getPhysicSpritePosition(x.first).x + 14, _spriteBatch.getPhysicSpritePosition(x.first).y + 33))
			{
				_entityDataNum[x.first]["CanJump"] = 1;
			}
			else
			{
				_entityDataNum[x.first]["CanJump"] = 0;
			}

			if (_entityDataNum[x.first]["CanJump"] == 1)
			{
				_spriteBatch.setPhysicSpriteVelocity(x.first, GESFML::Vector2D(_spriteBatch.getPhysicSpriteVelocity(x.first).x, 0).getB2Vec());
			}

			if (_keyPressed == sf::Keyboard::Space)
			{
				if (_entityDataNum[x.first]["CanJump"] == 1)
				{
					_spriteBatch.setPhysicSpriteVelocity(x.first, GESFML::Vector2D(_spriteBatch.getPhysicSpriteVelocity(x.first).x,-200).getB2Vec() );
				}
			}



			if (_spriteBatch.getPhysicSpriteVelocity(x.first).y < -30)
			{
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 0)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(0, 186), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 1)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(30, 186), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 2)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(60, 186), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 3)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(90, 186), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
			}
			if (_spriteBatch.getPhysicSpriteVelocity(x.first).y > 30)
			{
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 0)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(0, 248), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 1)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(30, 248), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 2)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(60, 248), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
				if (static_cast<int>(floor(_entityDataNum[x.first]["Time"])) % 4 == 3)
				{
					_spriteBatch.getPhysicSprite(x.first).setTextureRect(sf::IntRect(sf::Vector2i(90, 248), sf::Vector2i(30, 62)));
					_spriteBatch.getPhysicSprite(x.first).setScale(sf::Vector2f(1, 1));
					_spriteBatch.getPhysicSprite(x.first).setOrigin(sf::Vector2f(15, 31));
				}
			}

			
			_window.setViewCenter(_spriteBatch.getPhysicSpritePosition(x.first));

		}
		//---------------------------------------------------------------------------------------------------
	}
	
	for (auto x : _spriteBatch.getSpriteBatch())
	{
		//------------------------------------------------------------------------------------------------------------
		if (_spriteBatch.getSpriteUserDataStr(x.first) == "Menu_Button_Start")
		{

			long double state = _spriteBatch.getSpriteUserDataNum(_guiElements["Menu_Button_Start"]);

			if (state == 4)
			{
				continue;
			}
			

			std::vector<long long> _ids;
			//convert mouse pos to world coords
			sf::Vector2f mapCoords = _window.getWindow().mapPixelToCoords(sf::Vector2i(_mousePos.x, _mousePos.y));
			//get all ids im hovering over
			_ids = _spriteBatch.testPointSpriteIdAll(mapCoords.x, mapCoords.y);

			//if we press on the button
			if (std::find(_ids.begin(), _ids.end(), _guiElements["Menu_Button_Start"]) != _ids.end())
			{

				sf::Color tmp = _spriteBatch.getSpriteColor(_guiElements["Menu_Button_Start"]);
				tmp.g = 100;
				tmp.b = 100;
				_spriteBatch.setSpriteColor(_guiElements["Menu_Button_Start"], tmp);
				

				//if we press leftklick
				if (_mousePressed == sf::Mouse::Button::Left)
				{
					//unpause the generate world thread
					_runGenerateFunction = true;
					//change state
					_spriteBatch.setSpriteUserDataNum(_guiElements["Menu_Button_Start"], 1);
				}


			}
			else
			{
				sf::Color tmp = _spriteBatch.getSpriteColor(_guiElements["Menu_Button_Start"]);
				tmp.g = 0;
				tmp.b = 0;
				_spriteBatch.setSpriteColor(_guiElements["Menu_Button_Start"], tmp);
			}
			
			//_spriteBatch.setSpritePosition(_guiElements["Menu_Button_Start"], (_spriteBatch.getSpritePosition(_guiElements["Menu_Button_Start"]) - sf::Vector2f((1.0/60.0)*_frametime.asSeconds(),(1.0/60.0)*_frametime.asSeconds())));
			if (state == 1)
			{
				/////////////////////-----------CREATING THE GUI------------------///////////////////////
				//hide button
				sf::Color tmp = _spriteBatch.getSpriteColor(_guiElements["Menu_Button_Start"]);
				tmp.a = 0;
				_spriteBatch.setSpriteColor(_guiElements["Menu_Button_Start"],tmp);
				//hide button Shadow
				tmp = _spriteBatch.getSpriteShadowColor(_guiElements["Menu_Button_Start"]);
				tmp.a = 0;
				_spriteBatch.setSpriteShadowColor(_guiElements["Menu_Button_Start"], tmp);
				//hide button label
				tmp = _spriteBatch.getTextColor(_guiElements["Menu_Button_Start_Label"]);
				tmp.a = 0;
				_spriteBatch.setTextColor(_guiElements["Menu_Button_Start_Label"], tmp);

				//create The Text for displaying the progress of the world Generation
				_spriteBatch.createText(1000, 505, 50, 1, 1, 35, _DefaultFont, "Generating World: 0%", GESFML::Color(0, 0, 0, 255).getSfColor());
				_guiElements["Menu_GenerateWorld_Text_Progress"] = 1000;
				_spriteBatch.createText(1001, 504, 49, 1, 1, 35, _DefaultFont, "Generating World: 0%", GESFML::Color(255, 255, 255, 255).getSfColor());
				_guiElements["Menu_GenerateWorld_Text_Progress_Shadow"] = 1001;

				//set the text to be Bold
				_spriteBatch.setTextStyle(_guiElements["Menu_GenerateWorld_Text_Progress"], sf::Text::Style::Bold);
				_spriteBatch.setTextStyle(_guiElements["Menu_GenerateWorld_Text_Progress_Shadow"], sf::Text::Style::Bold);

				long long id = findNextFreeIdSprite();
				//progress bar border
				_spriteBatch.createSprite(id, 500, 100, 245, 45, _textureBatch["Blank"], GESFML::Color(0, 0, 0, 255).getSfColor());
				_guiElements["Menu_GenerateWorld_ProgressBar_Border"] = id;
				id = findNextFreeIdSprite();
				//progress bar background
				_spriteBatch.createSprite(id, 510, 110, 225, 25, _textureBatch["Blank"], GESFML::Color(128, 128, 128, 255).getSfColor());
				_guiElements["Menu_GenerateWorld_ProgressBar_Background"] = id;
				id = findNextFreeIdSprite();
				//progress bar 
				_spriteBatch.createSprite(id, 510, 110, 0, 25, _textureBatch["Blank"], GESFML::Color(0, 255, 0, 255).getSfColor());
				_guiElements["Menu_GenerateWorld_ProgressBar"] = id;

				//changeing state
				_spriteBatch.setSpriteUserDataNum(_guiElements["Menu_Button_Start"], 2);
			}
			if (state == 2)
			{
				//format the string
				std::ostringstream stringStream;
				stringStream << "Generating World: " << floor(((_ammountOfBlocksPlaced / ((16.0f*32.0f)*AMMOUNT_OF_CHUNKS_TO_GENERATE))*100.0f)) << "%";

				//display the string
				_spriteBatch.setText(_guiElements["Menu_GenerateWorld_Text_Progress"], stringStream.str());
				_spriteBatch.setText(_guiElements["Menu_GenerateWorld_Text_Progress_Shadow"], stringStream.str());
				//change the progress bar size to fit the progress of the world
				_spriteBatch.setSpriteSize(_guiElements["Menu_GenerateWorld_ProgressBar"], GESFML::Vector2D(floor(((_ammountOfBlocksPlaced / ((16.0f*32.0f)*AMMOUNT_OF_CHUNKS_TO_GENERATE))*225.0f)), 25).getSfVec());
				//change the background color to fit the progress of the world
				_spriteBatch.setSpriteColor(_guiElements["Menu_Background"], GESFML::Color(floor(((_ammountOfBlocksPlaced / ((16.0f*32.0f)*AMMOUNT_OF_CHUNKS_TO_GENERATE))*255.0f)), floor(((_ammountOfBlocksPlaced / ((16.0f*32.0f)*AMMOUNT_OF_CHUNKS_TO_GENERATE))*255.0f)), floor(((_ammountOfBlocksPlaced / ((16.0f*32.0f)*AMMOUNT_OF_CHUNKS_TO_GENERATE))*255.0f))).getSfColor());

				//if the world generation is done (99% or 100%)
				if (_ammountOfBlocksPlaced == ((16.0f*32.0f)*AMMOUNT_OF_CHUNKS_TO_GENERATE))
				{
					//hide progressbar
					sf::Color tmp = _spriteBatch.getSpriteColor(_guiElements["Menu_GenerateWorld_ProgressBar"]);
					tmp.a = 0;
					_spriteBatch.setSpriteColor(_guiElements["Menu_GenerateWorld_ProgressBar"], tmp);
					//hide progressbar background
					tmp = _spriteBatch.getSpriteColor(_guiElements["Menu_GenerateWorld_ProgressBar_Background"]);
					tmp.a = 0;
					_spriteBatch.setSpriteColor(_guiElements["Menu_GenerateWorld_ProgressBar_Background"], tmp);
					//hide progressbar border
					tmp = _spriteBatch.getSpriteColor(_guiElements["Menu_GenerateWorld_ProgressBar_Border"]);
					tmp.a = 0;
					_spriteBatch.setSpriteColor(_guiElements["Menu_GenerateWorld_ProgressBar_Border"], tmp);
					//Hide Menu Background
					tmp = _spriteBatch.getSpriteColor(_guiElements["Menu_Background"]);
					tmp.a = 0;
					_spriteBatch.setSpriteColor(_guiElements["Menu_Background"], tmp);
					//Hide Progress text
					tmp = _spriteBatch.getTextColor(_guiElements["Menu_GenerateWorld_Text_Progress"]);
					tmp.a = 0;
					_spriteBatch.setTextColor(_guiElements["Menu_GenerateWorld_Text_Progress"], tmp);
					//Hide Progress text shadow
					tmp = _spriteBatch.getTextColor(_guiElements["Menu_GenerateWorld_Text_Progress_Shadow"]);
					tmp.a = 0;
					_spriteBatch.setTextColor(_guiElements["Menu_GenerateWorld_Text_Progress_Shadow"], tmp);
					//changeing state to spawn entities and players
					_spriteBatch.setSpriteUserDataNum(_guiElements["Menu_Button_Start"], 3);
				}

			}

			if (state == 3)
			{

				long long id = findNextFreeId();
				//player
				_spriteBatch.createPhysicSpriteBox(id, 500, -100, BLOCK_PIXELSIZE-3, BLOCK_PIXELSIZE*2 - 2, true, 1, 0, 0, _textureBatch["Player_Animation"], GESFML::Color(255, 255, 255, 255).getSfColor());
				_spriteBatch.setPhysicSpriteUserDataStr(id, "Game_Player");
				_spriteBatch.getPhysicSpriteBody(id)->SetFixedRotation(true);
				_worldEntities["Player1"] = id;
	

				createBlock(1, -1, 1);
				createBlock(25, -1, 1);
				//changeing state to idle
				_spriteBatch.setSpriteUserDataNum(_guiElements["Menu_Button_Start"], 4);
			}

		}
		//----------------------------------------------------------------------------------------------------------------
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
long long Game::findNextFreeId()
{
	for (long long i = 0;i < _spriteBatch.getPhysicSpriteBatch().size() + 1;i++)
	{
		if (!_spriteBatch.isExistingPhysicSprite(i))
		{
			return i;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
long long Game::findNextFreeIdSprite()
{
	for (long long i = 0;i < _spriteBatch.getSpriteBatch().size() + 1;i++)
	{
		if (!_spriteBatch.isExistingSprite(i))
		{
			return i;
		}
	}
}

void Game::createBlock(int x, int y, int blockId)
{
	long long id = findNextFreeId();
	_worldBlocks[x][y] = id;
	_entityDataNum[id]["BlockID"] = blockId;
	_spriteBatch.createPhysicSpriteBox(id, x * BLOCK_PIXELSIZE + BLOCK_PIXELSIZE / 2 , (BLOCK_PIXELSIZE / 2) + y * BLOCK_PIXELSIZE , BLOCK_PIXELSIZE, BLOCK_PIXELSIZE, false, 1, 1, 0.2f, _textureBatch["Texture_Test"], sf::Color(255, 255, 255, 255));
	//_spriteBatch.createPhysicSpriteShadow(id, -7, -7, 50);
}

void Game::deleteBlock(int x, int y)
{
	long long id = findNextFreeId();
	_spriteBatch.deletePhysicSprite(_worldBlocks[x][y]);
	_worldBlocks[x].erase(y);
	_entityDataNum[id].clear();
	
}

