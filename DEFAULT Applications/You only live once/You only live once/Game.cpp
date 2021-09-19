#include "Game.h"



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
	_width = width;
	_height = height;
	_window.create(sf::VideoMode(width, height), "You only live once", true, 60);
	_window.setViewCenter(sf::Vector2f(_width / 2, _height / 2));
	_window.setViewSize(sf::Vector2f(_width, _height));
	_spriteBatch.initWorld(b2Vec2(0, 9.8f), 15, 60, true);

	_textureBatch["white_box"] = _helperFunc.createBlankTexture(512, 512, sf::Color(255, 255, 255, 255));
	_textureBatch["white_circle"].loadFromFile("Resources/Textures/Circle.png");
	_textureBatch["gui_vignette"].loadFromFile("Resources/Textures/Vignette.png");
	_textureBatch["white_box_border"].loadFromFile("Resources/Textures/boxBorder.png");
	_textureBatch["white_circle_border"].loadFromFile("Resources/Textures/circleBorder.png");
	_textureBatch["ground_tile"].loadFromFile("Resources/Textures/groundTile2.jpg");
	_textureBatch["ground_tile"].setSmooth(true);

	_spriteBatch.createSprite(999999999, 0, 0, _width, _height, _textureBatch["gui_vignette"], sf::Color(255, 255, 255, 100));
	_spriteBatch.setSpriteDrawOrder(999999999, 3);
	for (int i = 0; i < 10;i++)
	{
		_spriteBatch.createPhysicSpriteBox(i, i*128+64, _height - 25 / 2, 128, 128, false, 1, 1, 0.2f, _textureBatch["ground_tile"], sf::Color(255, 255, 255, 255));
		_spriteBatch.createPhysicSpriteShadow(i, -7, 7, 75);
	}

	_spriteBatch.createPhysicSpriteBox(14, _width / 2, 600, 50, 50, true, 1, 1, 0, _textureBatch["white_box_border"], sf::Color(255, 255, 255, 255));
	_spriteBatch.createPhysicSpriteCircle(11, _width / 2, 512+25, 50, true, 1, 1, 0, _textureBatch["white_circle_border"], sf::Color(255, 128, 0, 255));
	_spriteBatch.createPhysicSpriteCircle(12, _width / 2, 512-25, 50, true, 1, 1, 0, _textureBatch["white_circle_border"], sf::Color(255, 128, 0, 255));
	_spriteBatch.createPhysicSpriteBox(13, _width / 2, 512+25, 45, 51 , true, 1, 1, 0, _textureBatch["white_box_border"], sf::Color(255, 0, 255, 255));

	_spriteBatch.createPhysicSpriteShadow(14, -7, 7, 15);

	_spriteBatch.setSensorPhysicSprite(13, true);
	//_spriteBatch.getPhysicSpriteBody(13)->GetFixtureList()->SetSensor(true);

	_spriteBatch.createRevoluteJointAngLimit(14, 11, b2Vec2(0, 25), b2Vec2(0, 0), false, 0, 0, 0);
	_spriteBatch.createRevoluteJointAngLimit(14, 12, b2Vec2(0, -25), b2Vec2(0, 0), false, 0, 0, 0);
	_spriteBatch.createRevoluteJointAngLimit(14, 13, b2Vec2(0, 25), b2Vec2(0, 0), false, 0, 0, 0);

	_spriteBatch.setPhysicSpriteColor(11, sf::Color(0, 0, 0, 0));
	_spriteBatch.setPhysicSpriteColor(12, sf::Color(0, 0, 0, 0));
	//_spriteBatch.setPhysicSpriteColor(13, sf::Color(0, 0, 0, 0));

	_spriteBatch.getPhysicSpriteBody(14)->SetFixedRotation(true);

	_helperFunc.setSizeInPixel(_spriteBatch.getPhysicSpriteBatch()[14], 50, 100);

	_spriteBatch.setPhysicSpriteUserDataStr(14, "player_mainBody");
	_spriteBatch.setPhysicSpriteUserDataStr(13, "player_body");
	_spriteBatch.setPhysicSpriteUserDataStr(12, "player_body");
	_spriteBatch.setPhysicSpriteUserDataStr(11, "player_body");

	_spriteBatch.createPhysicSpriteBox(50, _width / 2 + 10, 50, 70, 70, true, 1, 1, 0.2f, _textureBatch["white_box_border"], sf::Color(255, 255, 0, 255));
	_spriteBatch.createPhysicSpriteBox(51, 750, _height - 70, 250, 70, false, 1, 1, 0.2f, _textureBatch["white_box_border"], sf::Color(0, 255, 0, 255),-45);
}

void Game::gameloop()
{

	while (_window.isOpen())
	{

		input();
		processEntities();

		_spriteBatch.updateAllPhysicSprites();
		_spriteBatch.worldStep();

		_window.clear(sf::Color(255, 255, 255, 255));
		_spriteBatch.drawAll(_window);
		_window.display();


	}
}

void Game::input()
{
	pressedMouseKey = -1;
	pressedKey = -1;


	sf::Event event;
	if (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::MouseButtonPressed:
			_mouseInput.pressKey(event.mouseButton.button);
			if (releasedMouseKey != -1)
			{
				pressedMouseKey = _mouseInput.getKeyPressed();
				releasedMouseKey = -1;
			}
		
			break;
		case sf::Event::MouseButtonReleased:
			_mouseInput.releaseKey(event.mouseButton.button);
			releasedMouseKey = _mouseInput.getKeyReleased();
			break;
		case sf::Event::KeyPressed:
			_keyboardInput.pressKey(event.key.code);
			if (releasedKey != -1)
			{
				pressedKey = _keyboardInput.getKeyPressed();
				releasedKey = -1;
			}
			
			break;
		case sf::Event::KeyReleased:
			_keyboardInput.releaseKey(event.key.code);
			releasedKey = _keyboardInput.getKeyReleased();
			break;

		default:
			break;
		}


		


	}
	
}

void Game::processEntities()
{
	for (auto x : _spriteBatch.getPhysicSpriteBatch())
	{
		if (_spriteBatch.getPhysicSpriteUserDataStr(x.first) == "player_mainBody")
		{
			if (_spriteBatch.isCollidingPhysicSpriteExceptUserDataStr(x.first - 1, { "player_mainBody","player_body" }))
			{
				_spriteBatch.setPhysicSpriteVelocity(x.first, b2Vec2(_spriteBatch.getPhysicSpriteVelocity(x.first).x,  0));

			}
			if (!_spriteBatch.isCollidingPhysicSpriteExceptUserDataStr(x.first - 1, { "player_mainBody","player_body" }))
			{
				_inAir = false;
			}

			if (_keyboardInput.getKey(sf::Keyboard::Space) && !_inAir)
			{
				_inAir = true;
				if (_spriteBatch.isCollidingPhysicSpriteExceptUserDataStr(x.first - 1, { "player_mainBody","player_body" }))
				{
					_spriteBatch.applyImpusePhysicSprite(x.first, b2Vec2(0, -1500), b2Vec2(0, 0));

				}
			}
			if (_keyboardInput.getKey(sf::Keyboard::A))
			{
				_spriteBatch.setPhysicSpriteVelocity(x.first, b2Vec2(-100, _spriteBatch.getPhysicSpriteVelocity(x.first).y));
			}
			if (_keyboardInput.getKey(sf::Keyboard::D))
			{
				_spriteBatch.setPhysicSpriteVelocity(x.first, b2Vec2(100, _spriteBatch.getPhysicSpriteVelocity(x.first).y));
			}

			std::cout  << _spriteBatch.isCollidingPhysicSpriteExceptUserDataStr(x.first - 1, { "player_mainBody","player_body" });
			
		}
	}

}