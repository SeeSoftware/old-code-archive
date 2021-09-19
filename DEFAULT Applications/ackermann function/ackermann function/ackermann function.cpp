// ackermann function.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "Ackerman.h"

int main()
{
	int j;
	int k;
	Ackerman ackerman;
	
	for (j = 0; j < 6;j++) {
		for (k = 0; k < 6; j++) {
			std::printf("ack(%d,%d) = %d \n", j, k, ackerman.ack(j, k));
		}
	}
	

    return 0;
}



