#include <cmath>
#include <ASCIImagicExceptions.hpp>
#include <fstream>
#include <iostream>
#include "ImageToASCII.h"

const std::string ImageToASCII::scale = "@#8&o:*. ";

imageData::imageData()
        : image(nullptr),
          width(0),
          height(0) {}

ImageToASCII::ImageToASCII() : image() {}

std::string ImageToASCII::getASCIIString() {
    if (image.image) {
        std::string ascii;
        auto slen = scale.length() - 1;
        for (int row = 0; row < image.height; ++row) {
            for (int col = 0; col < image.width; ++col) {
                auto val = image.image[row][col].red;
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
    if (image.image) {
        for (int i = 0; i < image.height; ++i) {
            delete[] image.image[i];
        }
        delete[] image.image;
    }
}

bool ImageToASCII::allocateImage() {
    try {
        image.image = new pixel* [image.height];
        for (int i = 0; i < image.height; ++i) {
            image.image[i] = new pixel[image.width];
        }
    } catch (std::bad_alloc& e) {
        return false;
    }
    return true;
}

void ImageToASCII::convertToGrayscale() {
    if (image.image) {
        for (int row = 0; row < image.height; ++row) {
            for (int col = 0; col < image.width; ++col) {
                auto val = static_cast<ubyte>(round(
                        image.image[row][col].red * 0.3 +
                        image.image[row][col].green * 0.59 +
                        image.image[row][col].blue * 0.11));
                image.image[row][col].red = val;
                image.image[row][col].green = val;
                image.image[row][col].blue = val;
            }
        }
    } else {
        throw NoImageLoaded();
    }
}

void ImageToASCII::saveASCIIToFile(const std::string& filename) {
    std::ofstream txtFile;
    txtFile.open(filename, std::ios_base::trunc);
    if (!txtFile.is_open() || txtFile.fail()) {
        throw saveASCIIToFileError();
    }
    txtFile << getASCIIString();
    txtFile.close();
}

void ImageToASCII::resizeImage(double ratio) {
    if (image.image) {
        auto oldImage = image;
        image.width = static_cast<int>(floor(image.width * ratio));
        image.height = static_cast<int>(floor(image.height * ratio));
        auto stepSize = 1 / ratio;
        auto offset = static_cast<int>(ceil(stepSize / 2));
        if (!allocateImage()) throw MemoryError();
        calculateNewImage(oldImage, stepSize, offset);
        deleteOldImage(oldImage);
    } else {
        throw NoImageLoaded();
    }
}

void ImageToASCII::calculateNewImage(const imageData& oldImage, double stepSize, int offset) const {
    for (int row = 0; row < image.height; ++row) {
        auto oldRow = static_cast<int>(round(row * stepSize));
        for (int col = 0; col < image.width; ++col) {
            auto oldCol = static_cast<int>(round(col * stepSize));
            ubyte newVal = getNewValue(oldImage, offset, oldRow, oldCol);
            image.image[row][col].red = newVal;
            image.image[row][col].green = newVal;
            image.image[row][col].blue = newVal;
        }
    }
}

void ImageToASCII::deleteOldImage(const imageData& oldImage) const {
    for (int i = 0; i < oldImage.height; ++i) {
        delete[] oldImage.image[i];
    }
    delete[] oldImage.image;
}

ubyte ImageToASCII::getNewValue(const imageData& oldImage, int offset, int oldRow, int oldCol) const {
    int cnt = 0;
    int sum = 0;
    for (int currRow = std::max(0, oldRow - offset);
         currRow < std::min(oldImage.height, oldRow + offset + 1);
         ++currRow) {
        for (int currCol = std::max(0, oldCol - offset);
             currCol < std::min(oldImage.width, oldCol + offset + 1);
             ++currCol) {
            ++cnt;
            sum += oldImage.image[currRow][currCol].red;
        }
    }
    auto newVal = static_cast<ubyte>(sum / cnt);
    return newVal;
}
