#ifndef CH_6_7_SORTING_OTHER_TYPES_ITEM_H
#define CH_6_7_SORTING_OTHER_TYPES_ITEM_H

#include <iostream.h>
#include <stdlib.h>
#include "Item.h"

typedef struct record { int key; float info; } Item;

int operator<(const Item &, const Item &);

int scan(Item &);

void rand(Item &);

void show(const Item &);

#endif //CH_6_7_SORTING_OTHER_TYPES_ITEM_H
