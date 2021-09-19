#include "MainClass.h"
#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <thread>
#include <cstdlib>
#include <time.h>

 

using namespace std;

MainClass::MainClass()
{
}


MainClass::~MainClass()
{

}


void MainClass::init(int WIDTH,int HEIGHT) {
	_width = WIDTH;
	_height = HEIGHT;
	_renderer.init(GetConsoleWindow(), GetStdHandle(STD_OUTPUT_HANDLE), GetDC(GetConsoleWindow()),WIDTH, HEIGHT);


}

void MainClass::run() {

	int tmp=0;
	COORD font;
	font.X = 16;
	font.Y = 16;
	_renderer.SetConsoleFontSize(font);
	init(512, 512);

	//_renderer.removeScrollbar();
	_renderer.ClearScreen();
	
	for (int y = 16;y < 512;y++) {
		for (int x = 0; x < 512;x++) {


			_renderer.drawPixel(x, y, RGB(y/2, x/2, x*32-y*32));

			
		}
	}





	while (true)
	{
		_renderer.changeTextColor(10 + 8*16);
		cout << "Help: number 5 ";
		_renderer.changeTextColor(7);
		cout <<" Type a number: ";

		string line;
		double d = 0;
		while (getline(std::cin, line))
		{
			stringstream ss(line);
			if (ss >> d)
			{
				if (ss.eof())
				{   // Success
					break;
				}
			}
			std::cout << "Invalid number!" << std::endl;
			Sleep(1000);
			_renderer.ClearScreen();
			std::cout << "Type a number: ";
		}
		d = floor(d);
		if (d > 5) {
			std::cout << "Number to big!";
			Sleep(1000);
			_renderer.ClearScreen();
			continue;
		}
		if (d < 0) {
			std::cout << "Number to smal!";
			Sleep(1000);
			_renderer.ClearScreen();
			continue;

		}

		if (d == 0) {
			_renderer.ClearScreen();
			cout << "Color pattern";

			for (int y = 16;y < _height;y++) {
				for (int x = 0; x < _width;x++) {

				

					_renderer.drawPixel(x, y, RGB(y / 2, x / 2, x * 32 - y * 32));


				}
			}
			_renderer.ClearScreen();
			continue;

		}
		if (d == 1) {


			_renderer.changeTextColor(0);
			for (int i = 0;i < (_width*_height) / 32;i++) {

				cout << (char)219;

			}
			_renderer.changeTextColor(7);



			_renderer.ClearScreen();

			cout << "Spirale";

			for (float x = 0;x < _width * 3; x += 0.005f) {

				_renderer.drawPixel(cos(x) * x + 246, sin(x) * x + 246, RGB(0, cos(x * 2) * 128 + 128, 0));

			}

			_renderer.ClearScreen();
			continue;

		}


			if (d == 2) {
				_renderer.ClearScreen();
				cout << "Blur Test   ";
				_renderer.changeTextColor(12 + 8 * 16);
				cout<< " Press esc to exit! ";
				_renderer.changeTextColor(7);
					
				_screenBuffer.clear();
				_screenBuffer.resize(_width*_height);

				for (int y = 16;y < _height;y++) {
					for (int x = 0; x < _width;x++) {


						COLORREF tmp;
						tmp = RGB(floor(rand() * 255), floor(rand() * 255), floor(rand() * 255));
						_renderer.drawPixel(x, y, tmp);
						_screenBuffer[x + y*_width] = tmp;

					}
				}



				while (true) {
					for (int y = 16;y < _height - 1;y++) {
						
						for (int x = 0; x < _width - 1;x++) {
							COLORREF Final = RGB(0, 0, 0);
							


							byte R = 0;
							byte G = 0;
							byte B = 0;


							R += GetRValue(_screenBuffer[x + 1 + y*_width]);
							G += GetGValue(_screenBuffer[x + 1 + y*_width]);
							B += GetBValue(_screenBuffer[x + 1 + y*_width]);


							R += GetRValue(_screenBuffer[x - 1 + y*_width]);
							G += GetGValue(_screenBuffer[x - 1 + y*_width]);
							B += GetBValue(_screenBuffer[x - 1 + y*_width]);



							R += GetRValue(_screenBuffer[x + (y + 1)*_width]);
							G += GetGValue(_screenBuffer[x + (y + 1)*_width]);
							B += GetBValue(_screenBuffer[x + (y + 1)*_width]);


							R += GetRValue(_screenBuffer[x + (y - 1)*_width]);
							G += GetGValue(_screenBuffer[x + (y - 1)*_width]);
							B += GetBValue(_screenBuffer[x + (y - 1)*_width]);

							R /= 4;
							G /= 4;
							B /= 4;

							R = floor(R);
							G = floor(G);
							B = floor(B);


							Final = RGB(R, G, B);


							_renderer.drawPixel(x, y, Final);
							_screenBuffer[x + (y)*_width] = Final;

							if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
								goto MainLoop;
							}


						}
					}
				}
				
			MainLoop:;
				_renderer.ClearScreen();
				continue;

			}



			if (d == 3) {

				int Generation = 0;


				_renderer.changeTextColor(0);
				for (int i = 0;i < (_width*_height) / 32;i++) {

					cout << (char)219;

				}
				_renderer.changeTextColor(7);


				_renderer.ClearScreen();
				cout << "Game Of Life(kinda not)  Generation: 0";

				_screenBuffer.clear();
				_screenBuffer.resize(_width*_height);

				srand(time(NULL) + 1);
				for (int y = 16;y < _height/2;y++) {
					for (int x = 0; x < _width/2;x++) {
						
						if (rand()%21 > 16) {
							_renderer.drawPixel(x, y, RGB(255,255,0));
							_screenBuffer[x + y * _width / 2] = RGB(255, 255, 0);
						}
						

					}
				}
				//goto MainLoop;

				//_renderer.drawPixel(256,256, RGB(255, 255, 0));
				
				while (true)
				{
					_renderer.ClearScreen();
					cout << "Game Of Life(kinda not) Generation:" << Generation << " ";

					_renderer.changeTextColor(12 + 8 * 16);
					cout << " Press esc to exit! ";
					_renderer.changeTextColor(7);
					int neightbars = 0;



					for (int y = 16;y < _height / 2;y++) {
						for (int x = 0; x < _width / 2;x++) {



							//_renderer.drawPixel(x, y, RGB(50, 50, 50));
							if (_screenBuffer[x + y * _width / 2] == RGB(255, 255, 0)) {

								if (_screenBuffer[x + 1 + y * _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + (y + 1) * _width / 2] == RGB(255, 255, 0)) {
									neightbars++;

								}

								if (_screenBuffer[x - 1 + (y)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + (y - 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + 1 + (y + 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;

								}

								if (_screenBuffer[x - 1 + (y + 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x - 1 + (y - 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + 1 + (y - 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (neightbars < 2) {
									_screenBuffer[x + (y)* _width / 2] = RGB(0, 0, 0);

								}
								if (neightbars > 3) {
									_screenBuffer[x + (y)* _width / 2] = RGB(0, 0, 0);
								}
								neightbars = 0;

							}

														if (_screenBuffer[x + (y)* _width / 2] == RGB(0, 0, 0)) {
								if (_screenBuffer[x + 1 + y * _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + (y + 1) * _width / 2] == RGB(255, 255, 0)) {
									neightbars++;

								}

								if (_screenBuffer[x - 1 + (y)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + (y - 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + 1 + (y + 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;

								}

								if (_screenBuffer[x - 1 + (y + 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x - 1 + (y - 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (_screenBuffer[x + 1 + (y - 1)* _width / 2] == RGB(255, 255, 0)) {
									neightbars++;
								}

								if (neightbars == 3) {
									_screenBuffer[x + (y)* _width / 2] = RGB(255, 0, 0);
								}

								neightbars = 0;

							}
														if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
															goto MainLoop;
														}
						}
					}
							



					for (int y = 16;y < _height/2;y++) {
						for (int x = 0; x < _width/2;x++) {

							//_renderer.drawPixel(x, y, RGB(50, 50, 50));
							

							if (_screenBuffer[x + (y)* _width / 2] == RGB(255, 0, 0)) {


								_screenBuffer[x + (y)* _width / 2] = RGB(255, 255, 0);



							}
							
							if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
								goto MainLoop;
							}

						}
					}

					for (int y = 16;y < _height / 2;y++) {
						for (int x = 0; x < _width / 2;x++) {
						

							_renderer.drawPixel(x, y, _screenBuffer[x + (y)* _width / 2]);

							

						}
					}

					Generation++;

				}

				_renderer.ClearScreen();
				continue;

			}

			if (d == 4) {
				_renderer.changeTextColor(0);
				for (int i = 0;i < (_width*_height) / 32;i++) {

					cout << (char)219;

				}
				_renderer.changeTextColor(7);
				_renderer.ClearScreen();
				cout << "Snow Test" << "   ";

_renderer.changeTextColor(12 + 8 * 16);
cout << " Press esc to exit! ";
_renderer.changeTextColor(7);

_screenBuffer.clear();
_screenBuffer.resize(_width * _height);

srand(time(NULL) + 1);
for (int y = 16;y < _height / 2;y++) {
	for (int x = 0; x < _width / 2;x++) {

		if (rand() % 20 > 16) {
			_renderer.drawPixel(x, y, RGB(255, 255, 255));
			_screenBuffer[x + y * _width / 2] = RGB(255, 255, 255);
		}


	}
}

for (int x = 0;x < _width / 2;x++) {

	_renderer.drawPixel(x, 256, RGB(128, 128, 128));

}

while (true) {
	for (int i=0;i < 50;i++) {
		_screenBuffer[floor(rand() % _width) + 16 * _width / 2] = RGB(255, 255, 255);
	}

	for (int y = 16;y < _height / 2;y++) {
		for (int x = 0; x < _width / 2;x++) {

			

			if (_screenBuffer[x + y * _width / 2] == RGB(255, 255, 255)) {
				if (y != _height / 2 - 1) {
					if (_screenBuffer[x + (y + 1) * _width / 2] != RGB(255, 255, 255)) {

						_screenBuffer[x + (y)* _width / 2] = RGB(0, 0, 0);
						_screenBuffer[x + (y + 1) * _width / 2] = RGB(254, 254, 254);

					}


				}
			}

		}
	}


	for (int y = 16;y < _height / 2;y++) {
		for (int x = 0; x < _width / 2;x++) {

			if (_screenBuffer[x + (y)* _width / 2] == RGB(254, 254, 254)) {
				_screenBuffer[x + (y)* _width / 2] = RGB(255, 255, 255);
			}

		}
	}

	for (int y = 16;y < _height / 2;y++) {
		for (int x = 0; x < _width / 2;x++) {

			_renderer.drawPixel(x, y, _screenBuffer[x + (y)* _width / 2]);

			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
				goto MainLoop;
			}
		}
	}
}



continue;

			}



			if (d == 5) {

				_renderer.changeTextColor(0);
				for (int i = 0;i < (_width*_height) / 32;i++) {

					cout << (char)219;

				}
				_renderer.changeTextColor(7);

				_renderer.ClearScreen();

				cout << "Nr. 0: Color Pattern\n";
				cout << "Nr. 1: Spirale\n";
				cout << "Nr. 2: Blur Test\n";
				cout << "Nr. 3: Game Of Life\n";
				cout << "Nr. 4: Snow Test\n";
				cout << "Nr. 5: Help\n\n";
				

			}
		
	}
	
}



