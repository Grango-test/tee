//
// Created by vladislav on 11.10.2021.
//

#include "tee.h"
#include <stdio.h>
#include <stdexcept>

// object constructor
tee::tee() {
    this->filename = "";
    this->buffer = "";
    this->appending = false;
    this->ready = false;
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
        FILE* outfile;
        if (this->appending) outfile = fopen(this->filename.data(), "a");
        else outfile = fopen(this->filename.data(), "w");

        size_t check = fwrite(this->buffer.data(), sizeof(char), this->buffer.size(), outfile);

        if (check != this->buffer.size())
        {
            throw std::runtime_error("Couldn't write to file");
        }
        fclose(outfile);

    }
    else
    {
        throw std::invalid_argument("Something went wrong with argument parsing");
    }
}

// writing std output
void tee::std_output() {
    if (this->ready)
    {
        printf("%s", this->buffer.data());
    }
    else
    {
        throw std::invalid_argument("Something went wrong with argument parsing");
    }
}

// reading std input. wasteful approach with a buffer for full input, possible better solutions
void tee::std_input() {
    char ch;
    while ((ch=getchar())!= EOF)
    {
        this->buffer.push_back(ch);
    }
}
