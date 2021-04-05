#include "Utility.h"

std::random_device rd;

int getRandomNumber(int max) 
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> randomNumber(0, max);
    return randomNumber(gen);
}

int getRandomNumber(int min, int max) 
{
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> int_distribution(min, max);
    return int_distribution(gen);
}
