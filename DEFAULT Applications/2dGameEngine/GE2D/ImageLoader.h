#pragma once

#include "GLTexture.h"
#include <string>

namespace GE2D {
	class ImageLoader
	{
	public:

		static GLTexture loadPNG(std::string filePath);

	};
}

