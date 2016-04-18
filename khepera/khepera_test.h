#ifndef KHEPERA_TEST_H
#define KHEPERA_TEST_H

#include "load_files.h"
#include "transitionmatrix.h"

class Khepera_T
{
public:
    Khepera_T()
{
}

    Load load;
    int size_TPM = 500;
    int num_act = 3;

    void runKhepera_test(int totalsteps, std::string start);

};

#endif // KHEPERA_TEST_H
