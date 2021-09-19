#pragma once

#include <vector>

namespace GE2D {

	class IOManager
	{
	public:

		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

	};

}