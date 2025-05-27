#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <windows.h>

#include "constants.h"
#include "participant.h"
#include "file_reader.h"

void printParticipant(const Participant& p) {
    int duration = p.finishSeconds - p.startSeconds;
    std::cout << std::setw(2) << std::setfill('0') << p.number << " "
        << p.lastName << " " << p.firstName << " " << p.patronymic << " "
        << duration / 3600 << ":" << (duration % 3600) / 60 << ":" << duration % 60
        << " " << p.club << '\n';
}

bool compareByTime(const Participant& a, const Participant& b) {
    return (a.finishSeconds - a.startSeconds) < (b.finishSeconds - b.startSeconds);
}

bool compareByClubThenName(const Participant& a, const Participant& b) {
    if (a.club != b.club) return a.club < b.club;
    return a.lastName < b.lastName;
}

void bubbleSort(std::vector<Participant>& data, bool (*cmp)(const Participant&, const Participant&)) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j + 1 < data.size(); ++j) {
            if (cmp(data[j + 1], data[j])) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

void filterByClub(const std::vector<Participant>& data, const std::string& clubName) {
    for (const auto& p : data) {
        if (p.club == clubName) {
            printParticipant(p);
        }
    }
}

void filterByTime(const std::vector<Participant>& data, int maxSeconds) {
    for (const auto& p : data) {
        int duration = p.finishSeconds - p.startSeconds;
        if (duration < maxSeconds) {
            printParticipant(p);
        }
    }
}

void filterParticipants(const std::vector<Participant>& data) {
    std::cout << "Выберите фильтр:\n";
    std::cout << "1 - По названию клуба\n";
    std::cout << "2 - По времени (меньше заданного)\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Введите название клуба:\n";
        std::string club;
        std::cin.ignore(); // на случай оставшегося символа от предыдущего ввода
        std::getline(std::cin, club);
        filterByClub(data, club);
    }
    else if (choice == 2) {
        std::cout << "Введите максимальное время (в формате HH:MM:SS):\n";
        std::string timeStr;
        std::cin >> timeStr;
        int maxSeconds = timeToSeconds(timeStr);
        filterByTime(data, maxSeconds);
    }
    else {
        std::cout << "Некорректный выбор.\n";
    }
}

int main() {
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "Rus");
    SetConsoleCP(65001);
    std::vector<Participant> participants;
    loadParticipants(participants, "input.txt");

    std::cout << "1 - Bubble sort, 2 - Quick sort\n";
    int sortChoice;
    std::cin >> sortChoice;

    std::cout << "1 - By time, 2 - By club and last name\n";
    int critChoice;
    std::cin >> critChoice;

    bool (*cmp)(const Participant&, const Participant&) = nullptr;
    if (critChoice == 1) cmp = compareByTime;
    else cmp = compareByClubThenName;

    if (sortChoice == 1)
        bubbleSort(participants, cmp);
    else
        std::sort(participants.begin(), participants.end(), cmp);

    std::cout << "Sorted list:\n";
    for (const auto& p : participants) {
        printParticipant(p);
    }

    std::cout << "Фильтрация:\n";
    filterParticipants(participants);

    return 0;
}
