#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <random>

Game::Game()
{
}


Game::~Game()
{
}



void Game::run() {
	int tmp;
	bool customcolor;

	std::cout << "Maze Size: ";
	std::cin >> _mazeWidth;
//	std::cout << "\nMaze Height: ";
//	std::cin >> _mazeHeight;
	std::cout << "\nPixel Size: ";
	std::cin >> _pixelsize;
	std::cout << "\nSlow Mode (1 = true 0 = false): ";
	std::cin >> _slowGeneration;
	if (_slowGeneration) {
		std::cout << "\nGenerationSpeed: ";
		std::cin >> _generationspeed;
	}
	std::cout << "\nCustomizeable Color (1 = true 0 = false): ";
	std::cin >> customcolor;

	if (customcolor) {
		std::cout << "\nMaze Color R: ";
		std::cin >> tmp;
		_MazeColor.r = tmp;
		std::cout << "\nMaze Color G: ";
		std::cin >> tmp;
		_MazeColor.g = tmp;
		std::cout << "\nMaze Color B: ";
		std::cin >> tmp;
		_MazeColor.b = tmp;

		std::cout << "\nWall Color R: ";
		std::cin >> tmp;
		_bgColor.r = tmp;
		std::cout << "\nWall Color G: ";
		std::cin >> tmp;
		_bgColor.g = tmp;
		std::cout << "\nWall Color B: ";
		std::cin >> tmp;
		_bgColor.b = tmp;
	}


	std::cout << "\n\nPress Enter for solution";

	_mazeHeight = _mazeWidth;

	init((_mazeWidth+1)*_pixelsize, (_mazeHeight+1)*_pixelsize);
	gameloop();
}


void Game::init(int width, int height) {
	_width = width;
	_height = height;
	
	_window.create(sf::VideoMode(width, height), "MazeGenerator");
	//_window.setVerticalSyncEnabled(true);
	_window.setFramerateLimit(_generationspeed);


}

void Game::gameloop() {



	generateMaze(_mazeWidth, _mazeHeight, _MazeColor);
	_canvas.setScale(_pixelsize, _pixelsize);
	_canvas.setPosition(sf::Vector2f(_pixelsize, _pixelsize));
	

	while (_window.isOpen())
	{
		input();

		_window.clear(_bgColor);
		_window.draw(_canvas);
		_window.display();
	}

}

void Game::input() {
	sf::Event event;

	if (_window.pollEvent(event)) {
		switch (event.type) {
		
		case sf::Event::Closed:
			_window.close();
			exit(0);
			break;
			
		case sf::Event::KeyPressed:
			_keyboard.pressKey(event.key.code);
			break;
		case sf::Event::KeyReleased:
			_keyboard.releaseKey(event.key.code);
			break;

		}
	}
	if (_keyboard.getKey(sf::Keyboard::Escape)) {
		_window.close();
		exit(0);
	}

	if (_keyboard.getKey(sf::Keyboard::Return)) {
		showSolution();
	}
}

void Game::generateMaze(int width, int height, sf::Color color) {
	_generating = true;

	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.

	pixels = new sf::Uint8[width*height*4];

	_posStack.reserve(width*height);

	_posStack.push_back(sf::Vector2i(0, 0));

	//for (int i = 0; i < floor((width*height) / 2) - 1; i++) {
	while(!_posStack.empty()){

		int x = _posStack.back().x;
		int y = _posStack.back().y;

		if (getPixelColor(XYtoPtr(x, y, height), height, pixels) != color) {
			setPixelColor(XYtoPtr(x, y, height), height, pixels, color);
		}


		
	
		if (x <= width - 3) {
			if (getPixelColor(XYtoPtr(x + 2, y, height), height, pixels) != color) {
				_possibledirection.push_back(1);
				_possiblePoints.push_back(sf::Vector2i(x + 2, y));
			}
		}

		if (x >= 2) {
			if (getPixelColor(XYtoPtr(x - 2, y, height), height, pixels) != color) {
				_possibledirection.push_back(2);
				_possiblePoints.push_back(sf::Vector2i(x - 2, y));
			}
		}

		if (y <= height - 3) {
			if (getPixelColor(XYtoPtr(x, y + 2, height), height, pixels) != color) {
				_possibledirection.push_back(3);
				_possiblePoints.push_back(sf::Vector2i(x, y + 2));
			}
		}


		if (y >= 2) {
			if (getPixelColor(XYtoPtr(x, y - 2, height), height, pixels) != color) {
				_possibledirection.push_back(4);
				_possiblePoints.push_back(sf::Vector2i(x, y - 2));
			}
		}

		srand(GetTickCount());

		int randomnum = 0;
		if (!_possibledirection.empty()) {
			randomnum = gen() % _possibledirection.size();

			

				switch (_possibledirection[randomnum])
				{
				case 1:
					setPixelColor(XYtoPtr(x + 1, y, height), height, pixels, color);
					break;
				case 2:
					setPixelColor(XYtoPtr(x - 1, y, height), height, pixels, color);
					break;
				case 3:
					setPixelColor(XYtoPtr(x, y + 1, height), height, pixels, color);
					break;
				case 4:
					setPixelColor(XYtoPtr(x, y - 1, height), height, pixels, color);
					break;


				default:
					break;
				}
			
		}


		if (!_possiblePoints.empty()) {
			_posStack.push_back(_possiblePoints[randomnum]);

			if (_slowGeneration) {
				_mazeTexture = _tools.createTextuerPixelData(width, height, pixels);
				_canvas.setTexture(_mazeTexture);

				_canvas.setScale(_pixelsize, _pixelsize);
				_canvas.setPosition(sf::Vector2f(_pixelsize, _pixelsize));


				input();

				_window.clear(_bgColor);
				_window.draw(_canvas);
				_window.display();
			}

		}
		else {

			_posStack.pop_back();

		}

		_possibledirection.clear();
		_possiblePoints.clear();




	}



	setPixelColor(XYtoPtr(0, 0, height), height, pixels, sf::Color(0, 255, 0, 255));
	setPixelColor(XYtoPtr(width - 2, height - 2, height), height, pixels, sf::Color(255, 0, 0, 255));


		_mazeTexture = _tools.createTextuerPixelData(width,height,pixels);
		_canvas.setTexture(_mazeTexture);
	
		_generating = false;

}

sf::Color Game::getPixelColor(long long ptr,int height, sf::Uint8 *pixels) {
	int R = pixels[ptr * 4];
	int G = pixels[ptr * 4 + 1];
	int B = pixels[ptr * 4 + 2];
	int A = pixels[ptr * 4 + 3];

	return sf::Color(R, G, B, A);

}

void Game::setPixelColor(long long ptr, int height, sf::Uint8 *pixels,sf::Color color) {
	pixels[ptr * 4] = color.r;
	pixels[ptr * 4 + 1] = color.g;
	pixels[ptr * 4 + 2] = color.b;
	pixels[ptr * 4 + 3] = color.a;

}

long long Game::XYtoPtr(int x, int y, int height) {
	long long ptr;

	ptr = x + y * height;

	return ptr;
}

void Game::showSolution() {
	if (!_generating) {
		if (!_showedSolution) {
			_showedSolution = true;
			_possiblePoints.clear();
			_posStack.clear();

			_posStack.push_back(sf::Vector2i(0, 0));

			while(!_posStack.empty()){
				int x = _posStack.back().x;
				int y = _posStack.back().y;

				if (getPixelColor(XYtoPtr(x , y, _mazeHeight), _mazeHeight, pixels) == _MazeColor) {
					setPixelColor(XYtoPtr(x, y, _mazeHeight), _mazeHeight, pixels, sf::Color(50, 50, 255, 255));
				}


				if (x <= _mazeWidth - 2) {
					if (getPixelColor(XYtoPtr(x + 1, y, _mazeHeight), _mazeHeight, pixels) == sf::Color(255, 0, 0, 255)) {
						break;
					}
				}
				if (x >= 1) {
					if (getPixelColor(XYtoPtr(x - 1, y, _mazeHeight), _mazeHeight, pixels) == sf::Color(255, 0, 0, 255)) {
						break;
					}
				}
				if (y <= _mazeHeight - 2) {
					if (getPixelColor(XYtoPtr(x, y + 1, _mazeHeight), _mazeHeight, pixels) == sf::Color(255, 0, 0, 255)) {
						break;
					}
				}
				if (y >= 1) {
					if (getPixelColor(XYtoPtr(x, y - 1, _mazeHeight), _mazeHeight, pixels) == sf::Color(255, 0, 0, 255)) {
						break;
					}
				}


				if (x <= _mazeWidth - 2) {
					if (getPixelColor(XYtoPtr(x + 1, y, _mazeHeight), _mazeHeight, pixels) == _MazeColor) {
						_possiblePoints.push_back(sf::Vector2i(x + 1, y));
					}
				}

				if (x >= 1) {
					if (getPixelColor(XYtoPtr(x - 1, y, _mazeHeight), _mazeHeight, pixels) == _MazeColor) {
						_possiblePoints.push_back(sf::Vector2i(x-1, y));
					}
				}

				if (y <= _mazeHeight - 2) {
					if (getPixelColor(XYtoPtr(x, y +1, _mazeHeight), _mazeHeight, pixels) == _MazeColor) {
						_possiblePoints.push_back(sf::Vector2i(x, y+ 1));
					}
				}

				if (y >= 1) {
					if (getPixelColor(XYtoPtr(x, y - 1, _mazeHeight), _mazeHeight, pixels) == _MazeColor) {
						_possiblePoints.push_back(sf::Vector2i(x, y - 1));
					}
				}

				if (!_possiblePoints.empty()) {
					_posStack.push_back(_possiblePoints[0]);
				}
				else {
					_posStack.pop_back();


					setPixelColor(XYtoPtr(x, y, _mazeHeight), _mazeHeight, pixels, sf::Color(220,220,255,255));
					
					
				}

				_possiblePoints.clear();



			}
			

			_mazeTexture = _tools.createTextuerPixelData(_mazeWidth, _mazeHeight, pixels);
			_canvas.setTexture(_mazeTexture);

			
		}
	}
}