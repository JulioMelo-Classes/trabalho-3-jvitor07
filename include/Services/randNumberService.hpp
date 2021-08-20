#ifndef RAND_NUMBER_SERVICE_HPP
#define RAND_NUMBER_SERVICE_HPP

#include <cstdlib>
#include <ctime>

class randNumberService
{
    public:
        static int generateNumber(int min, int max);
};

#endif