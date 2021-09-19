#pragma once
#include <vector>
#include <Windows.h>

namespace CSRE{

class Render
{


public:

	Render();
	~Render();

	BOOL SetConsoleFontSize(COORD dwFontSize);

	void drawPixel(int x, int y, int color);
	COLORREF getPixel(int x, int y);

	void ClearScreen();

	void init(HWND hconsole, HANDLE console, HDC hdcConsole, int WIDTH, int HEIGHT);
	/*
	void HDCStart();
	void HDCEnd();
	*/

	void removeScrollbar();
	void changeTextColor(int color);

private:
	RECT _r;
	HWND _hwndConsole;
	HANDLE _console;
	HDC _hdcConsole;
	int _width, _height;

	/*
	HBITMAP _hBitmap;
	HDC _hMemDC;
	HGDIOBJ _hOld;
	*/
	};

}
