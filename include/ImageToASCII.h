#ifndef ASCII_MAGIC_IMAGETOASCII_H
#define ASCII_MAGIC_IMAGETOASCII_H

#include <string>
#include <memory>

using ubyte = unsigned char;
struct pixel {
    ubyte red, green, blue, alpha;
};
struct imageData {
    pixel** image;
    int width, height;
    imageData();
};

class ImageToASCII {
public:
    ImageToASCII();
    std::string getASCIIString();
    virtual void loadImage() = 0;
    void convertToGrayscale();
    void saveASCIIToFile(const std::string &);
    void resizeImage(double ratio);
    virtual ~ImageToASCII();
protected:
    const static std::string scale;
    imageData image;
    bool allocateImage();
    ubyte getNewValue(const imageData& oldImage, int offset, int oldRow, int oldCol) const;
    void deleteOldImage(const imageData& oldImage) const;
    void calculateNewImage(const imageData& oldImage, double stepSize, int offset) const;
};

#endif //ASCII_MAGIC_IMAGETOASCII_H
