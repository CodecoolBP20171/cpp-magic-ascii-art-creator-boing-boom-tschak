#include <iostream>
#include <cstring>
#include <BMPToASCII.h>
#include <PNGToASCII.h>
#include <ASCIImagicExceptions.hpp>

namespace {
    const std::string acceptedFileTypes[] = {
            "bmp", "png", "jpg" // TODO: other jpeg extensions
    };

    bool validateFileNameAndType(const std::string& fname, const std::string& ftype) {
        bool flag = false;
        for (auto& type : acceptedFileTypes) {
            if (type == ftype) {
                flag = true;
                break;
            }
        }
        if (!flag) return false;
        return fname.substr(fname.length() - ftype.length()) == ftype;
    }

    bool validateCommandLineArguments(int argc, char* const* argv) {
        return argc == 5 &&
               strcmp(argv[1], "-f") == 0 &&
               strcmp(argv[3], "-t") == 0;
    }
}



int main(int argc, char* argv[]) {
    // TODO: case sensitivity?
    if (!validateCommandLineArguments(argc, argv)) {
        std::cout << "Usage:\nascii_magic -f <file_name> -t <file_type>" << std::endl;
        return 1;
    }
    std::string filename(argv[2]);
    std::string filetype(argv[4]);
    if (!validateFileNameAndType(filename, filetype)) {
        std::cout << "Invalid filename or type." << std::endl;
        return 1;
    }
    PNGToASCII image(filename);
    try {
        image.loadImage();
        std::cout << image.getASCIIString() << std::endl;
    } catch (DecoderError& e){
        std::cerr << e.what() << std::endl;
    } catch (NoImageLoaded& e){
        std::cerr << e.what() << std::endl;
    } catch(...){
        std::cerr << "SOmething unexpected happened" << std::endl;
    }
    return 0;
}