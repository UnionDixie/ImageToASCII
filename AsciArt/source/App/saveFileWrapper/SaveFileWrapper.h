#pragma once

#include <string_view>
#include <vector>
#include <fstream>

class SaveFileWrapper
{
public:
	SaveFileWrapper() = default;
	~SaveFileWrapper() = default;
	void saveImageToFile(std::string_view nameFile, const std::vector<std::vector<char>>& imageArray);
private:

};

