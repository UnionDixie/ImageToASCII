#include "Core.h"

#include <Windows.h>//windows.h has min,max function - be carefully


void Core::setHWND(HWND appHWND)
{
    std::cout << "Running...\nDrop files and Enter for next convert Image\n";
	dragDropWrapper.SetHandle(appHWND);
}

void Core::getEvent(sf::Event event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        if (!dragDropWrapper.haveImages()) {
            system("clear");
            images = *converter.convert(dragDropWrapper.getImageToConvert());//warn
        }
    }
}

bool Core::hasDraw() const
{
    return !images.empty();
}

std::vector<sf::Sprite>& Core::getImages()
{
    return images;
}


