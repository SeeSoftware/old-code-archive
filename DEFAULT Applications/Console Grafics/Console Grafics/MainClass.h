#pragma once

#include <CSRE\Render.h>

#include <cstdlib>
#include <complex>
class MainClass
{
public:
	MainClass();
	~MainClass();

	void run();


private:
	
	void init(int WIDTH, int HEIGHT);
	void GoL_TestforLive(int x, int y);

	std::vector<COLORREF> _screenBuffer;

	CSRE::Render _renderer;
	int _width, _height;
	
};

