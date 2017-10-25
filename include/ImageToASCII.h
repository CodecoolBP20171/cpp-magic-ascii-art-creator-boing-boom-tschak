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
    std::string getASCIIString();
    virtual ~ImageToASCII();
protected:
    const static std::string scale;
    pixel** image;
    int width, height;
};

#endif //ASCII_MAGIC_IMAGETOASCII_H
