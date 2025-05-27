#pragma once
#include <string>

struct Participant {
    int number;
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    int startSeconds;
    int finishSeconds;
    std::string club;
};
