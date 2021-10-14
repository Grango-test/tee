//
// Created by vladislav on 11.10.2021.
//

#include "mytee.h"

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdexcept>

// object constructor
mytee::mytee() {
    this->filename = "";
    this->buffer = "";
    this->appending = false;
    this->ready = false;
}

mytee::mytee(const mytee &other) {
    this->filename = other.filename;
    this->buffer = other.buffer;
    this->appending = other.appending;
    this->ready = other.ready;
}


mytee &mytee::operator=(const mytee &other) {
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
void mytee::parse_args(int argc, char **argv) {
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
        if (append_arg == "-a") this->appending = true;
        else throw std::invalid_argument("Unknown argument(s)");
    }
    this->filename = filename_arg;
    this->ready = true;
}

// writing to file
void mytee::file_output() {
    if (this->ready)
    {
        int fileid;
        if (this->appending) fileid = open(this->filename.data(), O_RDWR | O_CREAT | O_APPEND);
        else fileid = open(this->filename.data(), O_RDWR | O_CREAT | O_TRUNC);

        if (fileid == -1)
        {
            close(fileid);
            throw std::runtime_error("Couldn't open file");
        }

        ssize_t check = 0;

        while (check < sizeof(char)*this->buffer.size())
        {
            ssize_t recall = write(fileid, this->buffer.data() + check/sizeof(char) , sizeof(char)*this->buffer.size()-check);

            if (recall == -1)
            {
                close(fileid);
                throw std::runtime_error("Couldn't write to file");
            }
            check += recall;
        }

        check = fsync(fileid);

        if (check == -1)
        {
            close(fileid);
            throw std::runtime_error("Couldn't write to file");
        }

        close(fileid);
    }
    else
    {
        throw std::invalid_argument("Something went wrong with argument parsing");
    }
}

// writing std output
void mytee::std_output() {
    if (this->ready)
    {
        ssize_t check = 0;

        while (check < sizeof(char)*this->buffer.size())
        {
            ssize_t recall = write(STDOUT_FILENO, this->buffer.data() + check/sizeof(char),
                                                        sizeof(char)*this->buffer.size()-check);

            if (recall == -1)
            {
                throw std::runtime_error("Couldn't write to stdout");
            }
            check += recall;
        }
    }
    else
    {
        throw std::invalid_argument("Something went wrong with argument parsing");
    }
}

// reading std input. wasteful approach with a buffer for full input, possible better solutions
void mytee::std_input() {
    char ch;
    while (read(STDIN_FILENO, &ch, sizeof(char)) != 0)
    {
        this->buffer.push_back(ch);
    }
}
