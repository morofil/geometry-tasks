#include "file_reader.h"
#include <fstream>
#include <sstream>
#include <iostream>

int timeToSeconds(const std::string& timeStr) {
    int hh, mm, ss;
    char c;
    std::istringstream iss(timeStr);
    iss >> hh >> c >> mm >> c >> ss;
    return hh * 3600 + mm * 60 + ss;
}

void loadParticipants(std::vector<Participant>& data, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file\n";
        return;
    }

    Participant p;
    std::string start, finish;
    while (file >> p.number >> p.lastName >> p.firstName >> p.patronymic >> start >> finish >> p.club) {
        p.startSeconds = timeToSeconds(start);
        p.finishSeconds = timeToSeconds(finish);
        data.push_back(p);
    }
}
