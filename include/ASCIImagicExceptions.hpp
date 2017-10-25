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

class MemoryError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Couldn't allocate memory.";
    }
};

class InvalidArgument : public std::exception {
public:
    const char *what() const noexcept override {
        return "Invalid argument(s) given.";
    }
};

#endif //ASCII_MAGIC_ASCIIMAGICEXCEPTIONS_HPP
