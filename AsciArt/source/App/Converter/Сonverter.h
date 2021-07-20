#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>

class Ñonverter
{
public:
	Ñonverter() = default;
	~Ñonverter() = default;
	std::vector<sf::Texture> convert(std::queue<std::string>& files);
private:
	void saveToFile(const std::string& name, const std::vector<std::vector<char>>& imageArray);
private:
	sf::Vector2u sizeOfImage;
};

