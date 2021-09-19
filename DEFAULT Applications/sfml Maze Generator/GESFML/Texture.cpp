#include "Texture.h"
#include <iostream>
namespace GESFML {

	Texture::Texture(sf::Texture texture)
	{
		setTexture(texture);
	}
	Texture::Texture()
	{
		createEmptyTexture(256, 256);
	}

	Texture::~Texture()
	{
		//delete[] _pixels;
	}
	/*
	void Texture::createEmptyTextureold(int width, int height, sf::Color color) {
		_width = width;
		_height = height;

		//delete[] _pixels;

		_pixels = new sf::Uint8[width * height * 4];

		_texture.create(width, height);

		for (register int i = 0; i < width*height * 4; i += 4) {
			_pixels[i] = color.r;
			_pixels[i + 1] = color.g;
			_pixels[i + 2] = color.b;
			_pixels[i + 3] = color.a;
			
		}

		//_texture.update(_pixels);


	}
	/*
	void Texture::createTexturePixelData(int width, int height, sf::Uint8 *pixels) {
		_width = width;
		_height = height;

		delete[] _pixels;

		_pixels = pixels;

		_texture.create(width, height);



		_texture.update(_pixels);


	}
	void Texture::updateWithPixelData(sf::Uint8 *pixels) {
		delete[] _pixels;
		_pixels = pixels;
		_texture.update(_pixels);
	}
	*/
	void Texture::setTexture(sf::Texture texture) {
		//delete[] _pixels;
		_texture = texture;

	}

	void Texture::openPng(std::string path) {
		_texture = sf::Texture();
		_texture.loadFromFile(path);

	}
	void Texture::createEmptyTexture(int width, int height) {
		_width = width;
		_height = height;

		_texture.create(width, height);
	}

	/*
	void Texture::update() {

		_texture.update(_pixels);
	}
	*/
}