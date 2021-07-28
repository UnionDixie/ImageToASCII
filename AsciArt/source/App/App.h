#pragma once

#include <SFML/Graphics.hpp>
#include <string_view>

#include "Core/Core.h"

class App
{
public:
	App(std::string_view title, sf::VideoMode size);
	App() = delete;
	~App() = default;
public:
	void run();
private:
	Core core;
	sf::RenderWindow app;
	std::vector<sf::Sprite>* images;
};

