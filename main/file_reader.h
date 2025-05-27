#pragma once
#include <vector>
#include <string>
#include "participant.h"

int timeToSeconds(const std::string& timeStr);
void loadParticipants(std::vector<Participant>& data, const std::string& filename);
#pragma once
