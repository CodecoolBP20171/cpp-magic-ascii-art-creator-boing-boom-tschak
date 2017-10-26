#include <cmath>
#include <ASCIImagicExceptions.hpp>
#include <fstream>
#include <iostream>
#include "ImageToASCII.h"

const std::string ImageToASCII::scale = "@#8&o:*. ";

ImageToASCII::ImageToASCII()
        : image(nullptr),
          width(0),
          height(0) {}

std::string ImageToASCII::getASCIIString() {
    if (image) {
        std::string ascii;
        auto slen = scale.length() - 1;
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                auto val = image[row][col].red;
                auto normVal = round(val / 255.0 * slen);
                ascii += scale[normVal];
            }
            ascii += '\n';
        }
        return ascii;
    }
    throw NoImageLoaded();
}

ImageToASCII::~ImageToASCII() {
    if (image) {
        for (int i = 0; i < height; ++i) {
            delete[] image[i];
        }
        delete[] image;
    }
}

bool ImageToASCII::allocateImage() {
    try {
        image = new pixel *[height];
        for (int i = 0; i < height; ++i) {
            image[i] = new pixel[width];
        }
    } catch (std::bad_alloc &e) {
        return false;
    }
    return true;
}

void ImageToASCII::convertToGrayscale() {
    if (image) {
        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                auto val = static_cast<ubyte>(round(
                        image[row][col].red * 0.3 +
                        image[row][col].green * 0.59 +
                        image[row][col].blue * 0.11));
                image[row][col].red = val;
                image[row][col].green = val;
                image[row][col].blue = val;
            }
        }
    } else {
        throw NoImageLoaded();
    }
}

void ImageToASCII::saveASCIIToFile(const std::string &filename) {
    std::ofstream txtFile;
    txtFile.open(filename, std::ios_base::trunc);
    if (!txtFile.is_open() || txtFile.fail()) {
        throw saveASCIIToFileError();
    }
    txtFile << getASCIIString();
    txtFile.close();
}
