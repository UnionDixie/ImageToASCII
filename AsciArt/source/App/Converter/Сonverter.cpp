#include "Ñonverter.h"


std::vector<sf::Texture> Ñonverter::convert(std::queue<std::string>& files)
{
    std::vector<sf::Texture> textures;
    if (!files.empty()) {
        auto path = files.front();
        sf::Image image;
        if (!image.loadFromFile(path))
            std::cerr << "Error open File\n";
        else {
            sizeOfImage = image.getSize();
            char asciTabel[] = { '.',',',':','+','*','?','%','S','#','@' };

            auto toGrayScale = [&]() {
                for (size_t i = 0; i < sizeOfImage.x; i++)
                {
                    for (size_t j = 0; j < sizeOfImage.y; j++)
                    {
                        auto pixel = image.getPixel(i, j);
                        int avg = (pixel.r + pixel.g + pixel.b) / 3;
                        image.setPixel(i, j, sf::Color(avg, avg, avg, pixel.a));
                    }
                }
            };
            std::vector<std::vector<char>> imageArray(sizeOfImage.x, std::vector<char>(sizeOfImage.y, 0));
            auto map = [](float f1, float s1, float st1, float s2, float st2) {
                return ((f1 - s1) / (st1 - s1)) * (st2 - s2) + s2;
            };
            auto toAsci = [&]() {
                for (size_t i = 0; i < sizeOfImage.x; i++)
                {
                    for (size_t j = 0; j < sizeOfImage.y; j++)
                    {
                        auto pixel = image.getPixel(i, j);
                        auto index = static_cast<int>(map(pixel.r, 0, 255, 0, 10 - 1));
                        imageArray[i][j] = asciTabel[index];
                    }
                }
            };
            toGrayScale();
            toAsci();

            sf::Texture texture;
            texture.loadFromImage(image);
            textures.push_back(std::move(texture));

            //or use c++17|FileSystem
            auto posDot = path.find('.');
            auto posLastSlach = path.find_last_of('\\');
            auto name = path.substr(posLastSlach + 1, posDot - posLastSlach - 1);

            image.saveToFile(name + ".png");
            saveToFile(name + ".txt", imageArray);
        }
        files.pop();
    }
    return textures;
}

#include <fstream>

void Ñonverter::saveToFile(const std::string& name, const std::vector<std::vector<char>>& imageArray)
{
    system("clear");
    std::ofstream image(name);
    for (size_t i = 0; i < sizeOfImage.x; i++)
    {
        for (size_t j = 0; j < sizeOfImage.y; j++)
        {
            std::cout << imageArray[j][i];//rotate image
            image << imageArray[j][i];
        }
        std::cout << '\n';
        image << '\n';
    }
    image.close();


}
