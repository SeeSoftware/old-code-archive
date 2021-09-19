#pragma once

#include "Render.h"
#include <vector>
#include <Windows.h>
#include <iostream>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void init();
	void input();

	bool logicData[256][256] = { {} };
	bool drawData[256][256] = { {} };
	//bool drawData[1280][720] = { {} };
	int ABS_WIDTH = 10;
	int ABS_HEIGHT = 10;
	int WIDTH = 10;
	int HEIGHT = 10;
	int tmp;
	int k;
	bool runing = true;

	HWND console;
	RECT r;
	Render renderer;
	HANDLE hConsole;
	COORD Font;
	HWND consoleHWND;
	HDC consoleHDC;

};

