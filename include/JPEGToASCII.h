#ifndef ASCII_MAGIC_JPEGTOASCII_H
#define ASCII_MAGIC_JPEGTOASCII_H

#include "ImageToASCII.h"

class JPEGToASCII : public ImageToASCII {
public:
    explicit JPEGToASCII(const std::string& filename);
    void loadImage() override;
private:
    std::string filename;
};

#endif //ASCII_MAGIC_JPEGTOASCII_H
