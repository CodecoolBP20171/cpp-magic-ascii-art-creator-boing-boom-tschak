#include <iostream>
#include <cstring>
#include <BMPToASCII.h>

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
    BMPToASCII bmp(filename);
    std::cout << bmp.getASCIIString() << std::endl;
    return 0;
}