// ChallangeEulaproject.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
	/*
	//std::vector<int> Fibonacci = { 1,2 };
	long long sum = 3;
	int lastnum = 1;
	int middlenum = 2;
	int currentnum = 3;
	int savenum = 0;

	while (currentnum < 4000000)
	{

			savenum = currentnum;
			currentnum = lastnum + middlenum;
			lastnum = middlenum;
			middlenum = savenum;
			if (currentnum % 2 == 0)
			{
				sum += currentnum;
			}
			

	}
	sum -= middlenum;
	std::cout << currentnum << "\n" ;

	std::cout << sum;
	std::getchar();
	*/

	std::vector<long long> numbers;

	int num3 = 0;
	int num5 = 0;

	while (true)
	{
		if (num3 >= 1000 && num5 >= 1000)
		{
			break;
		}

		if (num3 < 1000)
		{
			num3 += 3;
		}	
		if (num5 < 1000)
		{
			num5 += 5;
		}	


		
		bool doBreak = false;

		for (long long x : numbers)
		{
			if (x == num3 || x == num5)
			{
				doBreak = true;
				break;
			}

		}

		if (doBreak)
		{
			continue;
		}
		else
		{
			if (num3 < 1000)
			{
				numbers.push_back(num3);
				
			}
			if (num5 < 1000)
			{
				numbers.push_back(num5);
			}

		}
	}

	long long sum= 0;

	for (long long x : numbers)
	{
		sum += x;
		std::cout << x << " " << sum << "  ";
	}

	std::cout << sum;

	std::getchar();

	return 0;
}

