#pragma once

#include <iostream>
#include "../Converter/�onverter.h"
#include "../DragDropWrapper/DragAndDrop.h"

class Core
{
public:
	Core() = default;
	void setHWND(HWND appHWND);
	void getEvent(sf::Event event);
	bool hasDraw() const;
	std::vector<sf::Sprite>& getImages();
	~Core() = default;
private:
	DragAndDrop dragDropWrapper;
	�onverter converter;
	std::vector<sf::Sprite> images;
};

