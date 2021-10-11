//
// Created by vladislav on 11.10.2021.
//

#include "tee.h"
#include <iostream>
#include <fstream>

// object constructor
tee::tee() {
    this->filename = "";
    this->buffer = "";
    this->appending = false;
    this->ready = false;
}


// parsing command-line arguments
void tee::parse_args(int argc, char **argv) {
    std::string filename_arg, append_arg;

    if (argc < 2)
    {
        throw std::invalid_argument("No filename_arg");
    }
    else if (argc > 3)
    {
        throw std::invalid_argument("Unknown argument(s)");
    }
    else
    {
        filename_arg = argv[argc - 1];
    }

    if (argc == 3)
    {
        append_arg = argv[1];
        if (append_arg == "--a") this->appending = true;
        else throw std::invalid_argument("Unknown argument(s)");
    }
    this->filename = filename_arg;
    this->ready = true;
}

// writing to file
void tee::file_output() {
    if (this->ready)
    {
        std::ofstream file;
        if (this->appending) file.open(this->filename, std::ios::app | std::ios::out);
        else file.open(this->filename, std::ios::out);

        file << this->buffer;

        file.close();

    }
    else
    {
        std::cout << "Something went wrong with argument parsing." << std::endl;
    }
}

// writing std output
void tee::std_output() {
    if (this->ready)
    {
        std::cout << this->buffer;
    }
    else
    {
        std::cout << "Something went wrong with argument parsing." << std::endl;
    }
}

// reading std input. wasteful approach with a buffer for full input, possible better solutions
void tee::std_input() {
    std::string line;
    while (std::getline(std::cin, line))
    {
        this->buffer.append(line);
        this->buffer.append("\n");
    }
}

tee::tee(const tee &other) {
    this->filename = other.filename;
    this->buffer = other.buffer;
    this->appending = other.appending;
    this->ready = other.ready;
}

tee &tee::operator=(const tee &other) {
    if (this != &other)
    {
        this->filename = other.filename;
        this->buffer = other.buffer;
        this->appending = other.appending;
        this->ready = other.ready;
    }
    return *this;
}

