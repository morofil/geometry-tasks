#pragma once
#include "participant.h"

void bubbleSort(Participant** arr, int size, int (*cmp)(const Participant*, const Participant*));
void quickSort(Participant** arr, int size, int (*cmp)(const Participant*, const Participant*));
#pragma once
