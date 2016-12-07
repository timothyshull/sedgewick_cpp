#include <iostream>

// this can be cleaned up
template<typename Item>
bool check_sort_stability(Item *orig[], Item *sorted[], size_t size) {
    for (int i = 0; i < size; i++) {
        Item *current = orig[i];
        int j = i;
        for (; orig[j]->key1 != current->key1 && j < size; j++) {}
        if (j == size) {
            continue;
        }
        Item *next = orig[j];
        j = 0;
        for (; sorted[j] != current; j++) {} // can assume it will not overflow
        for (; sorted[j]->key1 != current->key1 && j < size; j++) {}
        // no need to check for j == size here
        if (next->key2 != sorted[j]->key2) {
            return false;
        }
    }
    return true;
}