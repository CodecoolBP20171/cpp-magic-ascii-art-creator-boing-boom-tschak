#include "BMPToASCII.h"

BMPToASCII::BMPToASCII(std::string filename) {
    image.ReadFromFile(filename.c_str());
}

std::string BMPToASCII::getASCIString() {
    std::string ascii;
    auto slen = scale.length() - 1;
    for (int i = 0; i < image.TellHeight(); ++i) {
        for (int j = 0; j < image.TellWidth(); ++j) {
            auto val = image(j, i)->Red;
            auto normVal = round(val / 255.0 * slen);
            ascii += scale[normVal];
        }
        ascii += '\n';
    }
    return ascii;
}
