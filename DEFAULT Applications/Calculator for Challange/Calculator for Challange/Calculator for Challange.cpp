// Calculator for Challange.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include<iostream>


int main()
{

	for (int j = 1; j <= 10 ; j++) {
		for (int k = 1; k <= 10; k++) {
			if (j+1 == k - 1) {
				if (k + 1 == (j-1) * 2) {
					std::cout << j << "|" << k << "\n";
				}
			}
		}
	}

	std::getchar();

    return 0;
}

