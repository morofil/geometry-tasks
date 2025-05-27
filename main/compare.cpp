#include "compare.h"

int compareByTime(const Participant* a, const Participant* b) {
    int t1 = a->finishSeconds - a->startSeconds;
    int t2 = b->finishSeconds - b->startSeconds;
    return t1 - t2;
}

int compareByClubThenName(const Participant* a, const Participant* b) {
    if (a->club != b->club) return a->club < b->club ? -1 : 1;
    return a->lastName < b->lastName ? -1 : (a->lastName > b->lastName ? 1 : 0);
}
