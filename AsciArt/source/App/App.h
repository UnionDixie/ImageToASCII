#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string_view>

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
	sf::RenderWindow app;
	sf::Sprite asciArt;
	sf::Texture texture;
};

