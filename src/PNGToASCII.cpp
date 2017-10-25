#include "PNGToASCII.h"
#include "lodePNG/lodepng.h"

PNGToASCII::PNGToASCII(const std::string& filename) {
    std::vector<unsigned char> png;
    unsigned w, h;
    unsigned error = lodepng::decode(png, w, h, filename);
    if (error) {
        // TODO: something
        throw "";
    }
    height = h;
    width = w;
    image = new pixel* [height];
    for (int i = 0; i < height; ++i) {
        image[i] = new pixel[width];
    }
    size_t idx = 0;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            image[row][col].red = png[idx];
            image[row][col].green = png[idx + 1];
            image[row][col].blue = png[idx + 2];
            image[row][col].alpha = png[idx + 3];
            idx += 4;
        }
    }
}
