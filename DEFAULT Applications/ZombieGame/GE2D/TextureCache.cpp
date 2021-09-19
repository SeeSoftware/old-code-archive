#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace GE2D {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texturePath) {

		//or use auto
		std::map<std::string, GLTexture>::iterator mit = _textureMap.find(texturePath);

		//check if its not in the map
		if (mit == _textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(texturePath);

			//std::pair<std::string, GLTexture> newPair(texturePath, newTexture);

			_textureMap.insert(make_pair(texturePath, newTexture)); // or use make_pair

			//std::cout << "loaded Texture\n";
			return newTexture;
		}
		//std::cout << "loaded Texture Cache\n";
		return mit->second;

	}
}