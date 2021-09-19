// MakeDotInMiddle.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//



#include <Windows.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Mmsystem.h>

#include "Image.h"


int main()
{


	Image pic("picture.bmp");


	//for (int i = 0; i < ayyLmao.getWidth() * ayyLmao.getHeight() * 3; i++)
	//ayyLmao.getData()[i] = rand() % 255;

	BITMAPINFO bi24BitInfo = { { 0 } };
	bi24BitInfo.bmiHeader.biBitCount = 24;
	bi24BitInfo.bmiHeader.biCompression = BI_RGB;
	bi24BitInfo.bmiHeader.biPlanes = 1;
	bi24BitInfo.bmiHeader.biSize = sizeof(bi24BitInfo.bmiHeader);
	bi24BitInfo.bmiHeader.biWidth = pic.getWidth();
	bi24BitInfo.bmiHeader.biHeight = pic.getHeight();

	HDC hdc = CreateCompatibleDC(0);
	HBITMAP bitmap = CreateDIBSection(hdc, &bi24BitInfo, DIB_RGB_COLORS, 0, 0, 0);
	SelectObject(hdc, bitmap);

	SetDIBits(hdc, bitmap, 0, pic.getHeight(), pic.getData(), &bi24BitInfo, DIB_RGB_COLORS);


	while (true)
	{
		//Sleep(10);

		//std::cout << idlecount << std::endl;

		//if (idlecount > idlemax)
		{
			//SetCursorPos(300, 300);
			BitBlt(GetDC(0),(GetSystemMetrics(SM_CXSCREEN)/2)-pic.getWidth()/2,(GetSystemMetrics(SM_CYSCREEN)/2) - pic.getHeight() / 2,
				pic.getWidth(), pic.getHeight(), hdc, 0, 0, SRCCOPY);

		}
	}

	//ReleaseDC(GetConsoleWindow(), console);
	return 0;
}