#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>

#include <GE2D/GLSLProgram.h>
#include <GE2D\GLTexture.h>
#include <GE2D\GE2D.h>
#include <GE2D\InputManager.h>
#include <GE2D\Timing.h>
#include "Bullet.h"

#include <vector>
#include <GE2D/Sprite.h>
#include <GE2D\Errors.h>
#include <GE2D\Window.h>

#include <GE2D/SpriteBatch.h>


#include <GE2D\Camera2D.h>


enum class GameState { PLAY, EXIT };

class MainGame
{
public:
public:
	MainGame();
	~MainGame();

	void run();

private:
	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();

	GE2D::Window _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	std::vector <GE2D::Sprite*> _sprites;

	GE2D::GLSLProgram _colorProgram;
	GE2D::Camera2D _camera;
	
	GE2D::SpriteBatch _spriteBatch;

	GE2D::InputManager _inputManager;

	GE2D::FpsLimiter _fpsLimiter;

	std::vector<Bullet> _bullets;

	float _fps;
	float _time;
};

