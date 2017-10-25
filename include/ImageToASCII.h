#ifndef ASCII_MAGIC_IMAGETOASCII_H
#define ASCII_MAGIC_IMAGETOASCII_H

#include <string>
#include <memory>

using byte = unsigned char;
struct pixel {
    byte red, green, blue, alpha;
};

class ImageToASCII {
public:
    ImageToASCII();
    std::string getASCIIString();
    virtual void loadImage() = 0;
    virtual ~ImageToASCII();
protected:
    const static std::string scale;
    pixel** image;
    int width, height;
};

#endif //ASCII_MAGIC_IMAGETOASCII_H
