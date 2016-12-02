#include "Sort_compare.h"
#include "Selection_sort.h"
#include "Insertion_sort.h"
#include "Shell_sort.h"


int main() {
    Sort_compare<Selection_sort, Insertion_sort> sc1;
    sc1.main(1000, 100);
    Sort_compare<Selection_sort, Shell_sort> sc2;
    sc2.main(1000, 100);
    Sort_compare<Insertion_sort, Shell_sort> sc3;
    sc3.main(1000, 100);

    return 0;
}