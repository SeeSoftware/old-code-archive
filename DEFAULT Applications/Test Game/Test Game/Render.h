#pragma once
#include <vector>
#include <Windows.h>
class Render
{
public:

	
	static BOOL SetConsoleFontSize(COORD dwFontSize);

	static void updatescreen(bool drawDatav[256][256], HDC console,int WIDTH,int HEIGHT);

	static void ClearScreen();

};

