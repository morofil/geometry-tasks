#include "sort.h"
#include <algorithm>

void bubbleSort(Participant** arr, int size, int (*cmp)(const Participant*, const Participant*)) {
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - 1 - i; ++j)
            if (cmp(arr[j], arr[j + 1]) > 0)
                std::swap(arr[j], arr[j + 1]);
}

void quickSortRecursive(Participant** arr, int left, int right, int (*cmp)(const Participant*, const Participant*)) {
    if (left >= right) return;
    Participant* pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (cmp(arr[i], pivot) < 0) ++i;
        while (cmp(arr[j], pivot) > 0) --j;
        if (i <= j) std::swap(arr[i++], arr[j--]);
    }
    if (left < j) quickSortRecursive(arr, left, j, cmp);
    if (i < right) quickSortRecursive(arr, i, right, cmp);
}

void quickSort(Participant** arr, int size, int (*cmp)(const Participant*, const Participant*)) {
    quickSortRecursive(arr, 0, size - 1, cmp);
}
