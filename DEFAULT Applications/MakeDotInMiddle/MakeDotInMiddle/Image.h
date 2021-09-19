#ifndef image_h
#define image_h



#include <cstdio>
#include <iostream>


#include "stb_image.h"




typedef unsigned char byte;



class Image
{
public:

	Image()
		: data(NULL),
		comp(0),
		width(0),
		height(0),
		ok(false)
	{}

	





	~Image() {
		if (!ok) {
			return;
		}


		if (data != NULL) {
			stbi_image_free(data);
			data = NULL;
			ok = false;
		}

	}




	Image(const char * filename) {

		data = stbi_load(filename, &width, &height, &comp, 3);

		if (data == NULL) {
			std::cout << "cannot load image";
			ok = false;
			return;
		}
		else {
			ok = true;
		}

		byte* copy = new byte[getWidth() * getHeight() * 3];

		for (int i = 0; i < getWidth() * getHeight() * 3; i++)
		{
			copy[i] = getData()[i];
		}

		for (int i = 0; i < getWidth() * getHeight() * 3; i += 3)
		{
			getData()[i] = copy[getWidth() * getHeight() * 3 - i + 2];
			getData()[i + 1] = copy[getWidth() * getHeight() * 3 - i + 1];
			getData()[i + 2] = copy[getWidth() * getHeight() * 3 - i];
		}

		delete[] copy;

		//std::cout << "comp = " << comp << std::endl;
	}



	byte * getData()const { return data; }

	int getCompression()const { return comp; }

	int getWidth() const { return width; }
	int getHeight()const { return height; }

	bool good() { return ok; }




private:

	byte * data;

	int comp;

	int width;
	int height;


	bool ok;

};







#endif

