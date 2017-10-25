#ifndef ASCII_MAGIC_IMAGETOASCII_H
#define ASCII_MAGIC_IMAGETOASCII_H

#include <string>
#include <memory>

using ubyte = unsigned char;
struct pixel {
    ubyte red, green, blue, alpha;
};

class ImageToASCII {
public:
    ImageToASCII();
    std::string getASCIIString();
    virtual void loadImage() = 0;
    void convertToGrayscale();
    virtual ~ImageToASCII();
protected:
    const static std::string scale;
    pixel** image;
    int width, height;
    bool allocateImage();
};

#endif //ASCII_MAGIC_IMAGETOASCII_H
