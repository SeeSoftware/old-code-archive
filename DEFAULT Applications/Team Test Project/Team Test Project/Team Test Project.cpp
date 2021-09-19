// Team Test Project.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include "stdafx.h"
#include <iostream>
#include <vector>

int main()
{
	std::vector<std::vector<int> > sorted_array = { { 2,3 },{ 5,7 } };

	for (std::vector<int> l : sorted_array)
	{
		std::cout << l[0];
	}

	std::getchar();
    return 0;
}

