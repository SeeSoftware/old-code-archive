#include "stdafx.h"
#include "MainGame.h"
#include <new>
#include <thread>

#define _WIN32_WINNT 0x0500
using namespace std;

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	
}

void MainGame::run() {
	
	SetConsoleTextAttribute(hConsole, (15));

	cout << "WELCOME TO THIS GAME !" << "\n\n";
	cout << "WIDTH : ";
	cin >> WIDTH;
	cout << "\n";
	cout << "HEIGHT:";
	cin >> HEIGHT;
	cout << "\n";

	if (WIDTH > 256) {
		WIDTH = 256;
	}
	if (HEIGHT > 256) {
		HEIGHT = 256;
	}

	init();
	
	//drawData = new bool [WIDTH][HEIGHT];

	for (int y = 0;y < HEIGHT;y++) {
		for (int x = 0; x < WIDTH;x++) {
			drawData[0][0] = true;
		}
	}
	renderer.ClearScreen();
	renderer.updatescreen(drawData, consoleHDC, 1, 100);
	renderer.updatescreen(drawData, consoleHDC, 1, 100);
	renderer.updatescreen(drawData, consoleHDC, 1, 100);
	renderer.updatescreen(drawData, consoleHDC, 1, 100);
	while (!GetAsyncKeyState(VK_ESCAPE)) {
		renderer.updatescreen(drawData, consoleHDC, WIDTH, HEIGHT);

		std::this_thread::sleep_for(500ms);

		input();
		for (int y = 0;y < HEIGHT;y++) {
			for (int x = 0; x < WIDTH;x++) {
				if (drawData[x][y] == true) {
					logicData[x][y] == true;


				}
				if (logicData[x][y] == true) {
					if (x < 256 && y < 256) {
						drawData[x + 1][y] = true;
						drawData[x][y + 1] = true;
						drawData[x + 1][y + 1] = true;
						if (x > 0 && y>0) {
							drawData[x - 1][y] = true;
							drawData[x][y - 1] = true;
							drawData[x - 1][y - 1] = true;
							drawData[x + 1][y - 1] = true;
							drawData[x - 1][y + 1] = true;
						}
					}
				}
			}
		}


		
		

		//std::thread t1(input);
		//t1.join();
	}

	cout << "\nEnd of Game.";
	cin >> tmp;

}

void MainGame::init() {
	console = GetConsoleWindow();
	GetWindowRect(console, &r); //stores the console's current dimensions
								//Get a console handle
	consoleHWND = GetConsoleWindow();
	//Get a handle to device context
	consoleHDC = GetDC(console);

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (15));

	Font.X = 8;
	Font.Y = 8;

	//renderer.SetConsoleFontSize(Font);

	ABS_WIDTH = WIDTH;
	ABS_HEIGHT = HEIGHT;




	//SetConsoleMode(console,0);

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, ABS_WIDTH, ABS_HEIGHT, TRUE);
}

void MainGame::input() {



}
