#include "Сonverter.h"

std::vector<sf::Sprite>* Сonverter::convert(std::queue<std::string>& files)
{
    if (!files.empty()) {
        auto path = files.front();
        if (!image.loadFromFile(path)) {
            std::cerr << "Error open File\n";
        }
        else {
            getNameFile(path);
            imageToGray();
            grayImageToAsci();
            image.saveToFile(currentNameImage + ".png");

            sf::Texture texture;
            texture.loadFromImage(image);
            imageTextures.push_back(std::move(texture));
        }
        files.pop();
    }
    texturesToSprites();    

    return &images;
}

void Сonverter::imageToGray()
{
    auto sizeOfImage = image.getSize();
    for (size_t i = 0; i < sizeOfImage.x; i++)
    {
        for (size_t j = 0; j < sizeOfImage.y; j++)
        {
            auto pixel = image.getPixel(i, j);
            int avg = (pixel.r + pixel.g + pixel.b) / 3;
            image.setPixel(i, j, sf::Color(avg, avg, avg, pixel.a));
        }
    }
}

float Сonverter::matching(float value, float firstLow, 
                          float firstHigh, float secondLow, float secondHigh)
{
    //(⊃｡•́‿•̀｡)⊃━✿✿✿✿✿✿
    return ((value - firstLow) / (firstHigh - firstLow)) * (secondHigh - secondLow) + secondLow;
}

void Сonverter::grayImageToAsci()
{
    auto sizeOfImage = image.getSize();

    constexpr std::string_view asciTabel = ".,:+*?%S#@";

    std::vector<std::vector<char>> imageArray(sizeOfImage.x, std::vector<char>(sizeOfImage.y, 0));

    for (size_t i = 0; i < sizeOfImage.x; i++)
    {
        for (size_t j = 0; j < sizeOfImage.y; j++)
        {
            auto pixel = image.getPixel(i, j);
            auto index = static_cast<int>(matching(pixel.r, 0, 255, 0, 9));
            imageArray[i][j] = asciTabel[index];
        }
    }

    for (size_t i = 0; i < sizeOfImage.x; i++)
    {
        for (size_t j = 0; j < sizeOfImage.y; j++)
        {
            std::cout << imageArray[j][i];//rotate image
        }
        std::cout << '\n';
    }
    fileWrapp.saveImageToFile(currentNameImage + ".txt", imageArray);
}

void Сonverter::getNameFile(const std::string& path)
{
    std::filesystem::path filePath(path);
    currentNameImage = filePath.stem().string();
}

void Сonverter::texturesToSprites()
{
    images.clear();
    images.resize(imageTextures.size());
    for (size_t i = 0; i < images.size(); i++)
    {
        images[i].setTexture(imageTextures[i]);
        if (i) {
            auto [x, y] = images[i - 1].getPosition();
            auto [w, h] = imageTextures[i - 1].getSize();
            int row = 0;
            images[i].move(x + w, y + row * h);
            if (i != 0 && i % 4 == 0)// :D
                row++;
        }

    }
}




