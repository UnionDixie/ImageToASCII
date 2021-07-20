#include "App.h"
#include <Windows.h>//for drag and drop
#include <queue>
#include <iostream>
#include <string>

std::queue<std::string> Task;
LONG_PTR sfmlCallBack = 0x0;

LRESULT CALLBACK dragDropCallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DROPFILES)
    {
        HDROP hdrop = reinterpret_cast<HDROP>(wParam);
        const UINT filescount = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
        for (UINT i = 0; i < filescount; ++i)
        {
            const UINT bufsize = DragQueryFile(hdrop, i, NULL, 0);
            std::wstring str;
            str.resize(bufsize + 1);
            if (DragQueryFile(hdrop, i, &str[0], bufsize + 1))
            {
                std::string stdstr;
                sf::Utf8::fromWide(str.begin(), str.end(), std::back_inserter(stdstr));
                std::cout << stdstr << std::endl;
                Task.push(stdstr);
            }
        }
        DragFinish(hdrop);
        std::cout << "-------------" << std::endl;
    }
    return CallWindowProcW(reinterpret_cast<WNDPROC>(sfmlCallBack), handle, message, wParam, lParam);
}

App::App(std::string_view title, sf::VideoMode size) : app(size,title.data())
{
    HWND handle = app.getSystemHandle();
    DragAcceptFiles(handle, true);
    sfmlCallBack = SetWindowLongPtrW(handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(dragDropCallback)); 
}

void App::run()
{
    std::cout << "Running...\nDrop files and Enter for next convert\n";
    bool next = false;
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                app.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                next = true;
        }
        if (!Task.empty() && next) {
            convertImage();
            next = false;
        }
        app.clear();
        app.draw(asciArt);
        app.display();
    }
}

void App::convertImage()
{
    textures = converter.convert(Task);
    for (const auto& it : textures)
        asciArt.setTexture(it);
}





