#include "App.h"

App::App(std::string_view title, sf::VideoMode size) 
    : app(size,title.data())
{
    core.setHWND(app.getSystemHandle());
    app.setFramerateLimit(60);
}

void App::run()
{
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                app.close();
            core.getEvent(event);
        } 
        app.clear();
        if (core.hasDraw()) {
            for (const auto& image : core.getImages())
                app.draw(image);
        }
        app.display();
    }
}






