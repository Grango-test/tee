//
// Created by vladislav on 11.10.2021.
//

#ifndef TEE_TEE_H
#define TEE_TEE_H

#include <string>

class tee {
private:
    bool appending;
    bool ready;
    std::string filename, buffer;
public:
    tee();
    tee(const tee& other);

    ~tee() = default;

    tee& operator=(const tee& other);

    void parse_args(int argc, char** argv);

    void file_output();
    void std_output();

    void std_input();
};


#endif //TEE_TEE_H
