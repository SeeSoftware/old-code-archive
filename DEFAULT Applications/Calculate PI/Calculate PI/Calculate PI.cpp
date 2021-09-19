// Calculate PI.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	long double Pi=3;
	long increment= 1;

	for (int i = 0; i < 10;i++) {
		std::cout << increment << "\n\n";
		std::cout << "p: " << Pi << "\n";
		Pi += 4.0 / ((1.0 + increment)*(2.0 + increment)*(3.0 + increment));
		Pi -= 4.0 / ((3.0 + increment)*(4.0 + increment)*(5.0 + increment));
		increment += 5;
	}

	std::cout << Pi;
	std::getchar();
    return 0;
}

