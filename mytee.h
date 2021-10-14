//
// Created by vladislav on 11.10.2021.
//

#ifndef TEE_MYTEE_H
#define TEE_MYTEE_H

#include <string>

class mytee {
private:
    bool appending;
    bool ready;
    std::string filename, buffer;
public:
    mytee();
    mytee(const mytee& other);

    ~mytee() = default;

    mytee& operator=(const mytee& other);

    void parse_args(int argc, char** argv);

    void file_output();
    void std_output();

    void std_input();
};


#endif //TEE_MYTEE_H
