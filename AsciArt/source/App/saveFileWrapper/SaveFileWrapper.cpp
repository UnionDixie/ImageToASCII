#include "SaveFileWrapper.h"

void SaveFileWrapper::saveImageToFile(std::string_view nameFile, const std::vector<std::vector<char>>& imageArray)
{
    std::ofstream image(nameFile.data());
    for (size_t i = 0; i < imageArray.size(); i++)
    {
        for (size_t j = 0; j < imageArray[i].size(); j++)
        {
            image << imageArray[j][i];//rotate image
        }
        image << '\n';
    }
    image.close();
}
