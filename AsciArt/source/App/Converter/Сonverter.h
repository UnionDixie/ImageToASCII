#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>
#include <filesystem>

#include "../saveFileWrapper/SaveFileWrapper.h"

class Ñonverter
{
public:
	Ñonverter() = default;
	~Ñonverter() = default;
	std::vector<sf::Sprite>* convert(std::queue<std::string>& files);
private:
	void imageToGray();
	float matching(float f1, float s1, float st1, float s2, float st2);
	void grayImageToAsci();
	void getNameFile(const std::string& path);
	void texturesToSprites();
private:
	std::string currentNameImage;
	sf::Image image;
	SaveFileWrapper fileWrapp;
	std::vector<sf::Texture> imageTextures;
	std::vector<sf::Sprite> images;
};

