#include <iostream>
#include <cstring>
#include <BMPToASCII.h>
#include <PNGToASCII.h>
#include <ASCIImagicExceptions.hpp>
#include <JPEGToASCII.h>
#include <fstream>

namespace {

    enum fileType {
        TBMP,
        TPNG,
        TJPG,
        INVALID_TYPE
    };

    struct options {
        std::string filename;
        bool color;
        fileType type;
        double resize;

        options()
                : color(false),
                  type(INVALID_TYPE),
                  resize(1) {}
    };

    fileType parseType(const std::string &filetype) {
        // TODO: other jpeg extensions
        if (filetype == "bmp") {
            return TBMP;
        } else if (filetype == "png") {
            return TPNG;
        } else if (filetype == "jpg") {
            return TJPG;
        } else {
            return INVALID_TYPE;
        }
    }

    options parseArgs(int argc, char *const *argv) {
        options result;
        for (int i = 1; i < argc; i += 2) {
            if (argv[i][0] != '-') throw InvalidArgument();
            switch (argv[i][1]) {
                case 'f' :
                    result.filename = std::string(argv[i + 1]);
                    break;
                case 't' :
                    result.type = parseType(argv[i + 1]);
                    break;
                case 'r' :
                    try {
                        result.resize = std::stod(argv[i + 1]);
                    } catch (...) {
                        throw InvalidArgument();
                    }
                    break;
                case 'c' :
                    result.color = true;
                    --i;
                    break;
                default :
                    throw InvalidArgument();
            }
        }
        return result;
    }

    bool isFileExists(const std::string &name) {
        std::ifstream f(name.c_str());
        return f.good();
    }

    fileType guessType(const std::string &filename) {
        auto ext = filename.substr(filename.rfind('.') + 1);
        return parseType(ext);
    }

    void printUsage() {
        std::cout << "Usage: ascii_magic  -f <file_name>"
                "\n\t\t\t\t\t[-t <file_type>]"
                "\n\t\t\t\t\t[-color]"
                "\n\t\t\t\t\t[-r <resize_ratio>]" << std::endl;
    }
}



int main(int argc, char *argv[]) {
    // TODO: case sensitivity?
    options settings;
    try {
        settings = parseArgs(argc, argv);
    } catch (InvalidArgument &err) {
        printUsage();
        return 1;
    } catch (...) {
        std::cerr << "This should never happen." << std::endl;
        return 1;
    }
    if (settings.filename.empty()) {
        printUsage();
        return 1;
    }
    if (settings.type == INVALID_TYPE) {
        try {
            settings.type = guessType(settings.filename);
        } catch (std::out_of_range &err) {
            std::cout << "Invalid filename.\n";
            return 1;
        }
        if (settings.type == INVALID_TYPE) {
            std::cout << "Unknown filetype :-(\n";
            return 1;
        }
    }
    if (!isFileExists(settings.filename)) {
        std::cout << "File does not exists.\n";
        return 1;
    }
    std::unique_ptr<ImageToASCII> image;
    switch (settings.type) {
        case TBMP :
            image = std::unique_ptr<ImageToASCII>(new BMPToASCII(settings.filename));
            break;
        case TPNG :
            image = std::unique_ptr<ImageToASCII>(new PNGToASCII(settings.filename));
            break;
        case TJPG :
            image = std::unique_ptr<ImageToASCII>(new JPEGToASCII(settings.filename));
            break;
        default :
            std::cerr << "This should never happen." << std::endl;
            return 1;
    }
    try {
        image->loadImage();
        std::cout << image->getASCIIString() << std::endl;
    } catch (DecoderError &e) {
        std::cerr << e.what() << std::endl;
    } catch (NoImageLoaded &e) {
        std::cerr << e.what() << std::endl;
    } catch (MemoryError &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Something unexpected happened" << std::endl;
    }
    return 0;
}