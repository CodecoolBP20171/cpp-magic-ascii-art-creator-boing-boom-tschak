#ifndef ASCII_MAGIC_BMPTOASCII_H
#define ASCII_MAGIC_BMPTOASCII_H

#import <EasyBMP/EasyBMP.h>
#include "ImageToASCII.h"

class BMPToASCII : public ImageToASCII{
public:
    explicit BMPToASCII(const std::string &filename);
    void loadImage() override;
private:
    std::string filename;
};

#endif //ASCII_MAGIC_BMPTOASCII_H
