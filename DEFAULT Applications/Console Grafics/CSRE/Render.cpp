
#include "Render.h"
#include <iostream>

namespace CSRE {

	Render::Render() {


	}

	Render::~Render() {


	}


	BOOL Render::SetConsoleFontSize(COORD dwFontSize) {
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
		if (!GetCurrentConsoleFontEx(output, false, &info))
			return false;
		info.dwFontSize = dwFontSize;
		return SetCurrentConsoleFontEx(output, false, &info);
	}


	void Render::drawPixel(int x, int y, int color) {

		SetPixel(_hdcConsole, x, y, color);

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


	void Render::init(HWND hwndConsole, HANDLE console, HDC hdcConsole, int WIDTH, int HEIGHT) {

		_console = console;
		_hdcConsole = hdcConsole;
		_hwndConsole = hwndConsole;

		_width = WIDTH;
		_height = HEIGHT;

		GetWindowRect(hwndConsole, &_r); //stores the console's current dimensions
									//Get a console handle

		//SetConsoleMode(console,0);

		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(hwndConsole, _r.left, _r.top, WIDTH, HEIGHT, TRUE);

	}
	//not working
	void Render::removeScrollbar() {
		CONSOLE_SCREEN_BUFFER_INFO SBInfo;
		COORD NewSBSize;
		int Status;

		GetConsoleScreenBufferInfo(_console, &SBInfo);
		NewSBSize.X = SBInfo.dwSize.X - 2;
		NewSBSize.Y = SBInfo.dwSize.Y;

		Status = SetConsoleScreenBufferSize(_console, NewSBSize);
		if (Status == 0)
		{
			Status = GetLastError();
			std::cout << "SetConsoleScreenBufferSize() failed! Reason : " << Status << std::endl;
			exit(Status);
		}

		GetConsoleScreenBufferInfo(_console, &SBInfo);

	}

	void Render::changeTextColor(int color) {
		SetConsoleTextAttribute(_console,color);
	}

	COLORREF Render::getPixel(int x, int y) {
			return GetPixel(_hdcConsole, x, y);
		
	}

	/*
	void Render::HDCStart() {
		 _hBitmap = CreateCompatibleBitmap(_hdcConsole, _width, _height);
		 _hMemDC = CreateCompatibleDC(_hdcConsole);
		 _hOld = SelectObject(_hMemDC, _hBitmap);

		BitBlt(_hMemDC, 0, 0, _width, _height, _hdcConsole, 0, 0, SRCCOPY);




	}


	void Render::HDCEnd() {


		// Clean up
		DeleteDC(_hMemDC);
		ReleaseDC(_hwndConsole, _hdcConsole);
	}
	*/
}

