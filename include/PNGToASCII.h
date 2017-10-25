#ifndef ASCII_MAGIC_PNGTOASCII_H
#define ASCII_MAGIC_PNGTOASCII_H

#include "ImageToASCII.h"

class PNGToASCII : public ImageToASCII {
public:
    explicit PNGToASCII(const std::string& filename);
};

#endif //ASCII_MAGIC_PNGTOASCII_H
