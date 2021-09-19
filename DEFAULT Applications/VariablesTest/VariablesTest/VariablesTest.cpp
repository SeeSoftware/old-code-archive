// VariablesTest.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include<windows.h>
#include<string>


int main()
{
	int Count = 0;
	
	Sleep(1000);
	
	while (true) {

		Count++;
		
		if (Count % 10 == 0) {
			std::cout << Count << std::endl;
		}

		if (Count == 1000000) {
			break;
		}
	}

    return 0;
}

