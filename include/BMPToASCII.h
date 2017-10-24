#ifndef ASCII_MAGIC_BMPTOASCII_H
#define ASCII_MAGIC_BMPTOASCII_H

#import <EasyBMP/EasyBMP.h>
#include "ImageToASCII.h"

class BMPToASCII : public ImageToASCII{
public:
    explicit BMPToASCII(std::string filename);
    std::string getASCIString() override;

private:
    BMP image;
};

#endif //ASCII_MAGIC_BMPTOASCII_H
