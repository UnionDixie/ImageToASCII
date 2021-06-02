#include "App.h"

#include <iostream>
#include <Windows.h>
#include <queue>
#include <string>


std::queue<std::string> Task;

LONG_PTR sfmlCallBack = 0x0;

LRESULT CALLBACK dragDropCallback(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DROPFILES)
    {
        HDROP hdrop = reinterpret_cast<HDROP>(wParam);
        POINT p;
        p.x = 0;
        p.y = 0;
        if (DragQueryPoint(hdrop, &p)) {
            std::printf("Point is %d, %d\n", p.x, p.y);
        }
        else
            std::cout << "Failed to get point" << std::endl;

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
    }//if WM_DROPFILES
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
    if (!Task.empty()) {
        auto path = Task.front();
        sf::Image image;
        if (!image.loadFromFile(path))
            std::cerr << "Error open File\n";
        else {
            auto size = image.getSize();
            char asciTabel[] = { '.',',',':','+','*','?','%','S','#','@' };
            auto toGrayScale = [&](){
                for (size_t i = 0; i < size.x; i++)
                {
                    for (size_t j = 0; j < size.y; j++)
                    {
                        auto pixel = image.getPixel(i, j);
                        int avg = (pixel.r + pixel.g + pixel.b) / 3;
                        image.setPixel(i, j, sf::Color(avg, avg, avg, pixel.a));
                    }
                }
            };
            std::vector<std::vector<char> > a(size.x, std::vector<char>(size.y, 0));
            auto map = [](float f1, float s1, float st1, float s2, float st2) {
                return ((f1 - s1) / (st1 - s1)) * (st2 - s2) + s2;
            };
            auto toAsci = [&]() {
                for (size_t i = 0; i < size.x; i++)
                {
                    for (size_t j = 0; j < size.y; j++)
                    {
                        auto pixel = image.getPixel(i, j);
                        auto index = static_cast<int>(map(pixel.r, 0, 255, 0, 10 - 1));
                        a[i][j] = asciTabel[index];
                    }
                }
            };

            toGrayScale();
            toAsci();

            texture.loadFromImage(image);
            asciArt.setTexture(texture);

            system("clear");
            for (size_t i = 0; i < size.x; i++)
            {
                for (size_t j = 0; j < size.y; j++)
                {
                    std::cout << a[j][i];
                }
                std::cout << '\n';
            }

        }
        Task.pop();
    }
}





