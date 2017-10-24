#include <cmath>
#include "ImageToASCII.h"

const std::string ImageToASCII::scale = "@#8&o:*. ";

std::string ImageToASCII::getASCIString() {
    std::string ascii;
    auto slen = scale.length() - 1;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            auto val = image[i][j].red;
            auto normVal = round(val / 255.0 * slen);
            ascii += scale[normVal];
        }
        ascii += '\n';
    }
    return ascii;
}
