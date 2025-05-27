#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include "participant.h"
#include "constants.h"
#include "file_reader.h"
#include "sort.h"
#include "compare.h"

void printParticipant(const Participant& p) {
    int duration = p.finishSeconds - p.startSeconds;
    std::cout << p.number << " " << p.lastName << " " << p.firstName << " "
        << p.patronymic << " " << duration / 3600 << ":"
        << (duration % 3600) / 60 << ":" << duration % 60 << " "
        << p.club << '\n';
}

void filterByClub(const std::vector<Participant>& data, const std::string& clubName) {
    for (const auto& p : data) {
        if (p.club == clubName) printParticipant(p);
    }
}

void filterByTime(const std::vector<Participant>& data, int maxSeconds) {
    for (const auto& p : data) {
        int duration = p.finishSeconds - p.startSeconds;
        if (duration < maxSeconds) printParticipant(p);
    }
}

void filterParticipants(const std::vector<Participant>& data) {
    std::cout << "1 - Filter by club\n2 - Filter by time\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter club name: ";
        std::string club;
        std::cin.ignore();
        std::getline(std::cin, club);
        filterByClub(data, club);
    }
    else if (choice == 2) {
        std::cout << "Enter max time (HH:MM:SS): ";
        std::string timeStr;
        std::cin >> timeStr;
        int maxSec = timeToSeconds(timeStr);
        filterByTime(data, maxSec);
    }
}

int main() {
    SetConsoleOutputCP(65001);
    std::vector<Participant> data;
    loadParticipants(data, "input.txt");

    std::cout << "1 - Bubble Sort\n2 - Quick Sort\n";
    int sortMethod;
    std::cin >> sortMethod;

    std::cout << "1 - By time\n2 - By club and last name\n";
    int sortCriteria;
    std::cin >> sortCriteria;

    int (*compareFuncs[])(const Participant*, const Participant*) = {
        compareByTime, compareByClubThenName
    };

    void (*sortFuncs[])(Participant**, int, int (*)(const Participant*, const Participant*)) = {
        bubbleSort, quickSort
    };

    std::vector<Participant*> ptrs;
    for (auto& p : data) ptrs.push_back(&p);

    sortFuncs[sortMethod - 1](ptrs.data(), ptrs.size(), compareFuncs[sortCriteria - 1]);

    std::cout << "Sorted list:\n";
    for (auto p : ptrs) printParticipant(*p);

    std::cout << "Now filtering:\n";
    filterParticipants(data);

    return 0;
}
