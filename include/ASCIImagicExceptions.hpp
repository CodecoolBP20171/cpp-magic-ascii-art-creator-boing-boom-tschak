#ifndef ASCII_MAGIC_ASCIIMAGICEXCEPTIONS_HPP
#define ASCII_MAGIC_ASCIIMAGICEXCEPTIONS_HPP

#include <exception>

class DecoderError : public std::exception{
public:
    const char* what() const noexcept override {
        return "The decoder encountered an error.";
    }
};

class NoImageLoaded : public std::exception {
public:
    const char* what() const noexcept override {
        return "No image loaded.";
    }
};

#endif //ASCII_MAGIC_ASCIIMAGICEXCEPTIONS_HPP