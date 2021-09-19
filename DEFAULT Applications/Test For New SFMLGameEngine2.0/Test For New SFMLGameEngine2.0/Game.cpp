#include "Game.h"
#include <iostream>
#include <string>

Game::Game()
{
}


Game::~Game()
{
}

void Game::run()
{
	init(1280, 720);
	gameloop();
}

void Game::init(int width, int height)
{
	_window.create(sf::VideoMode(width, height), "test", true, 60);
	//_window.setViewCenter(sf::Vector2f(width / 4, height / 4));
	//_window.setViewSize(sf::Vector2f(width/2, height /2));
}

void Game::gameloop()
{
	_spriteBatch.initWorld(b2Vec2(0, 9.8f), 50, 60, true);

	blank = _helperFunc.createBlankTexture(256, 256 ,sf::Color(255, 255, 255, 255));
	Circle.loadFromFile("Resources/circle.png");

	font.loadFromFile("Resources/arial.ttf");
	/*
	int x = 0;
	int y = 0;
	int id = 1;

	for (int i=0; i < 512; i+=32)
	{
		for (int k=140; k < 1024+150; k+=32)
		{
			_spriteBatch.createPhysicSpriteBox(id, k, i, 32,32,true,1,1,0, fuck, sf::Color(i, k, 0, 255));
			_spriteBatch.createPhysicSpriteShadow(id, 7, 7, 75);
			id++;
		}
	}
	*/
	
	_spriteBatch.createPhysicSpriteBox(4, 700, 500, 128, 128, false, 1, 1, 0.2f, blank, sf::Color(255, 255, 0, 255));
	_spriteBatch.createPhysicSpriteShadow(4, -7, 7, 75);
	_spriteBatch.createPhysicSpriteBox(5, 400, 500, 128, 128, true, 1, 1, 0.2f, blank, sf::Color(255, 0, 0, 255));
	_spriteBatch.createPhysicSpriteShadow(5, -7, 7, 75);
	_spriteBatch.createPhysicSpriteBox(8, 400, 200, 20, 20, true, 1, 1, 0.2f, blank, sf::Color(255, 0, 0, 255));
	_spriteBatch.createPhysicSpriteShadow(8, -7, 7, 75);
	_spriteBatch.createPhysicSpriteBox(9, 400, 200, 20, 20, true, 1, 1, 0.2f, blank, sf::Color(255, 0, 0, 255));
	_spriteBatch.createPhysicSpriteShadow(8, -7, 7, 75);
	_spriteBatch.createPhysicSpriteCircle(6, 550, 500, 128, true, 1, 1, 0.2f, Circle, sf::Color(0, 255, 0, 255));
	_spriteBatch.createPhysicSpriteShadow(6, -7, 7, 75);
	_spriteBatch.createPhysicSpriteCircle(7, 550, 350, 128, true, 1, 1, 0.6f, Circle, sf::Color(255, 128, 0, 255));
	_spriteBatch.createPhysicSpriteShadow(7, -7, 7, 75);

	_spriteBatch.createPhysicSpriteBox(0, 640, 720, 1280, 20,false,1,1,0, blank, sf::Color(0, 0, 255, 255));
	_spriteBatch.createPhysicSpriteShadow(0, -7, 7, 75);
	_spriteBatch.createPhysicSpriteBox(1, 0, 500, 1280, 20, false, 1, 1, 0, blank, sf::Color(0, 0, 255, 255),90);
	_spriteBatch.createPhysicSpriteShadow(1, -7, 7, 75);
	_spriteBatch.createPhysicSpriteBox(2, 1280, 500, 1280, 20, false, 1, 1, 0, blank, sf::Color(0, 0, 255, 255),90);
	_spriteBatch.createPhysicSpriteShadow(2, -7, 7, 75);
	_spriteBatch.createPhysicSpriteBox(3, 640, 0, 1280, 20, false, 1, 1, 0, blank, sf::Color(0, 0, 255, 255));
	_spriteBatch.createPhysicSpriteShadow(3, -7, 7, 75);

	_spriteBatch.setPhysicSpriteUserDataStr(0, "Wall");
	_spriteBatch.setPhysicSpriteUserDataStr(1, "Wall");
	_spriteBatch.setPhysicSpriteUserDataStr(2, "Wall");
	_spriteBatch.setPhysicSpriteUserDataStr(3, "Wall");

	_spriteBatch.createRevoluteJointAngLimit(4, 8, b2Vec2(-64, 0), b2Vec2(0, 0), false, 45,0,0);
	_spriteBatch.createRevoluteJointAngLimit(4, 9, b2Vec2(64, 0), b2Vec2(0, 0), false,90,0,0);

	_spriteBatch.addPhysicSpritePosition(4, sf::Vector2f(5, -500));
	_spriteBatch.addPhysicSpriteRotation(4, 15);

	_spriteBatch.createText(0, 50, 50, 1, 1, 80, font, "hello Text", sf::Color(0, 0, 0, 255),45);
	_spriteBatch.setTextDrawOrder(0, 2);
	_spriteBatch.addTextPosition(0, sf::Vector2f(50, 50));
	_spriteBatch.setTextStyle(0, sf::Text::Style::Underlined | sf::Text::Style::StrikeThrough);

	_spriteBatch.createSprite(0, 256, 256, 64, 64, blank, sf::Color(255, 0, 0, 255));
	_spriteBatch.createSpriteShadow(0, -7, 7,75);
	_spriteBatch.createSprite(1, 266, 256, 64, 64, blank, sf::Color(255, 255, 0, 255));
	_spriteBatch.createSpriteShadow(1, -7, 7, 75);
	_spriteBatch.setSpriteDrawOrder(1, 1);
	_spriteBatch.createSprite(2, 276, 256, 64, 64, blank, sf::Color(255, 0, 255, 255));
	_spriteBatch.createSpriteShadow(2, -7, 7, 75);
	_spriteBatch.setSpriteDrawOrder(2, 2);
	_spriteBatch.createSprite(3, 296, 256, 64, 64, blank, sf::Color(0, 255, 0, 255));
	_spriteBatch.createSpriteShadow(3, -7, 7, 75);
	_spriteBatch.setSpriteDrawOrder(3, 3);
	_spriteBatch.createSprite(4, 316, 256, 64, 64, blank, sf::Color(0, 0, 255, 255));
	_spriteBatch.createSpriteShadow(4, -7, 7, 75);
	_spriteBatch.setSpriteDrawOrder(4, 3);

	std::cout << _spriteBatch.getPhysicSpriteCountUserDataStr("Wall");
	
	MouseJointDef.bodyA = _spriteBatch.getPhysicSpriteBody(0);
	MouseJointDef.collideConnected = true;
	MouseJointDef.maxForce = 4000;

	_spriteBatch.setSensorPhysicSprite(4, true);



	while (_window.isOpen())
	{
		_window.updateFps();

		input();
		std::cout << _window.getFps() << "\n";

		if (_spriteBatch.isCollidingPhysicSprite(4))
		{
			_spriteBatch.setPhysicSpriteColor(4, sf::Color(0, 255, 0, 255));
		}
		else
		{
			_spriteBatch.setPhysicSpriteColor(4, sf::Color(255, 0, 0, 255));
		}


		_spriteBatch.updateAllPhysicSprites();
		_spriteBatch.worldStep();

		_window.clear(sf::Color(129,191,248,255));
			
		_spriteBatch.drawAll(_window);
		//_spriteBatch.drawShadowSprites(_window);
		_window.display();
	}

}

void Game::input()
{
	int mousePressed = -1;
	int mouseReleased = -1;
	sf::Event event;
	if (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window.close();

		case sf::Event::KeyPressed:
			_input.pressKey(event.key.code);
			break;
		case sf::Event::KeyReleased:
			_input.releaseKey(event.key.code);
			break;
		case sf::Event::MouseButtonPressed:
			_mouseinput.pressKey(event.mouseButton.button);
			mousePressed = _mouseinput.getKeyPressed();

			break;
		case sf::Event::MouseButtonReleased:
			_mouseinput.releaseKey(event.mouseButton.button);
			mouseReleased = _mouseinput.getKeyReleased();
			break;
		default:
			break;
		}
	}

	sf::Vector2f cursorPos;
	cursorPos = _window.getWindow().mapPixelToCoords(sf::Mouse::getPosition(_window.getWindow()));

	if (mousePressed == sf::Mouse::Button::Left || mousePressed == sf::Mouse::Button::Right)
	{
		if (grabbedbody == -9999999999998)
		{
			sf::Vector2f cursorPos;
			cursorPos = _window.getWindow().mapPixelToCoords(sf::Mouse::getPosition(_window.getWindow()));

			if (_spriteBatch.testPointPhysicSprite(cursorPos.x, cursorPos.y))
			{

				grabbedbody = _spriteBatch.testPointIdPhyiscSprite(cursorPos.x, cursorPos.y);

				if (_spriteBatch.isExistingPhysicSprite(grabbedbody))
				{
					if (_spriteBatch.getPhysicSpriteUserDataStr(grabbedbody) != "Wall")
					{
						MouseJointDef.bodyB = _spriteBatch.getPhysicSpriteBody(grabbedbody);
						MouseJointDef.target.Set(cursorPos.x / 30.0f, cursorPos.y / 30.0f);
						MouseJoint = (b2MouseJoint*)_spriteBatch.getWorld()->CreateJoint(&MouseJointDef);

					}
				}
			}
		}
		
	}
	if (mouseReleased == sf::Mouse::Button::Left || mouseReleased == sf::Mouse::Button::Right)
	{
		
		if(_spriteBatch.isExistingPhysicSprite(grabbedbody)){
			if(_spriteBatch.getPhysicSpriteUserDataStr(grabbedbody) != "Wall")
			_spriteBatch.getWorld()->DestroyJoint(MouseJoint);
		}
		grabbedbody = -9999999999998;
	}

	if (((grabbedbody != -9999999999998))&&_mouseinput.getKey(sf::Mouse::Button::Left))
	{
		sf::Vector2f cursorPos;
		cursorPos = _window.getWindow().mapPixelToCoords(sf::Mouse::getPosition(_window.getWindow()));

		if (_spriteBatch.isExistingPhysicSprite(grabbedbody))
		{
			if (_spriteBatch.getPhysicSpriteUserDataStr(grabbedbody) != "Wall")
			{
				_spriteBatch.freezePhysicSprite(grabbedbody, false);
				MouseJoint->SetTarget(b2Vec2(cursorPos.x / 30, cursorPos.y / 30));
			}
		}
		
	}

	//if (mousePressed == sf::Mouse::Button::Right)
	if(_mouseinput.getKey(sf::Mouse::Button::Right))
	{
		//if (_spriteBatch.isExistingPhysicSprite(grabbedbody))
		//{
			//if (_spriteBatch.isPhysicSpriteDynamic(grabbedbody))
			//{
				//_spriteBatch.setPhysicSpriteSizeCircle(grabbedbody, _spriteBatch.getPhysicSpriteSize(grabbedbody).x*1.1f);
				//_spriteBatch.setPhysicSpriteSizeBox(grabbedbody, _spriteBatch.getPhysicSpriteSize(grabbedbody).x*1.1f, _spriteBatch.getPhysicSpriteSize(grabbedbody).y*1.1f);
				id++;
				_spriteBatch.createPhysicSpriteCircle(id, cursorPos.x, cursorPos.y, 25, true, 1, 0, 0.5f, Circle, sf::Color(0, 128, 255));

				//_spriteBatch.freezePhysicSprite(grabbedbody, true);

			//}
		//}
		
		
	}


	
	

}


