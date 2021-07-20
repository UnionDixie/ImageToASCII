#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string_view>
#include "../App/Converter/�onverter.h"

class App
{
public:
	App(std::string_view title, sf::VideoMode size);
	void run();
	App() = delete;
	~App() = default;
private:
	void convertImage();
private:
	�onverter converter;
	sf::RenderWindow app;
	sf::Sprite asciArt;
	std::vector<sf::Texture> textures;
};

