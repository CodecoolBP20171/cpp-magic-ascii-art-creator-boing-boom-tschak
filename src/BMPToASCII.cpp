#include "BMPToASCII.h"

BMPToASCII::BMPToASCII(const std::string &filename) {
    BMP bmp;
    bmp.ReadFromFile(filename.c_str());
    width = bmp.TellWidth();
    height = bmp.TellHeight();
    image = new pixel*[height];
    for (int i = 0; i < height; ++i) {
        image[i] = new pixel[width];
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j].red = bmp(j, i)->Red;
            image[i][j].green = bmp(j, i)->Green;
            image[i][j].blue = bmp(j, i)->Blue;
            image[i][j].alpha = bmp(j, i)->Alpha;
        }
    }
}
