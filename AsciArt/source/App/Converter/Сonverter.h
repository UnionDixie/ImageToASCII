#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>

class �onverter
{
public:
	�onverter() = default;
	~�onverter() = default;
	std::vector<sf::Texture> convert(std::queue<std::string>& files);
private:
	void saveToFile(const std::string& name, const std::vector<std::vector<char>>& imageArray);
private:
	sf::Vector2u sizeOfImage;
};

