#include "Errors.h"

#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

namespace GE2D {

	//Prints out an error message and exits the game
	void fatalError(std::string errorString) {
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(69);
	}

}