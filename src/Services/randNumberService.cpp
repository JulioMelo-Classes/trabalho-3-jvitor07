#include "Services/randNumberService.hpp"

int randNumberService::generateNumber(int min, int max) {
    srand((unsigned)time(0));
    return rand()%(max-min+1) + min;
}