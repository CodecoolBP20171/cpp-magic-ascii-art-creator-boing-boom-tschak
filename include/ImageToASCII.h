#ifndef ASCII_MAGIC_IMAGETOASCII_H
#define ASCII_MAGIC_IMAGETOASCII_H

#include <string>

class ImageToASCII {
public:
    virtual std::string getASCIString() = 0;
protected:
    const static std::string scale;
};

#endif //ASCII_MAGIC_IMAGETOASCII_H
