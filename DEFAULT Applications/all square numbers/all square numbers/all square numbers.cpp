// all square numbers.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	long long a=0;

			for (int i = 0;i < 1024;i++) {
				for (int i = 0;i < 1024;i++) {
					for (int i = 0;i < 1024;i++) {
						for (int i = 0;i < 1024;i++) {
							for (int i = 0;i < 1024;i++) {

								a++;
							}
						}
					}
				}
			}

	std::cout << a;
	std::getchar();
	return 0;
}

