#include "stdafx.h"
#include "Render.h"
#include "colormod.h"
#include <iostream>



BOOL Render::SetConsoleFontSize(COORD dwFontSize) {
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return false;
	info.dwFontSize = dwFontSize;
	return SetCurrentConsoleFontEx(output, false, &info);
}


void Render::updatescreen(bool drawData[256][256], HDC console_HANDLE, int WIDTH,int HEIGHT) {

	
	for (int y=0;y < HEIGHT;y++) {

		for (int x=0;x < WIDTH;x++) {
			bool data = drawData[x][y];
			switch (data) {
			case true:
				SetPixel(console_HANDLE, x,y, RGB(255, 255, 0));
				break;
			case false:
				SetPixel(console_HANDLE, x, y, RGB(0, 0, 0));
				break;
			}
			//SetConsoleTextAttribute(console, (15));
			//std::cout << x << " " << y;
		}
		std::cout << "\n";
	}


}

void Render::ClearScreen() {

		HANDLE                     hStdOut;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD                      count;
		DWORD                      cellCount;
		COORD                      homeCoords = { 0, 0 };

		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;

		/* Get the number of cells in the current buffer */
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
		cellCount = csbi.dwSize.X *csbi.dwSize.Y;

		/* Fill the entire buffer with spaces */
		if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Fill the entire buffer with the current colors and attributes */
		if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Move the cursor home */
		SetConsoleCursorPosition(hStdOut, homeCoords);
	
}