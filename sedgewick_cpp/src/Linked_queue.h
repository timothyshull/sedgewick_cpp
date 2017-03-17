#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "Queue.h"

template<typename T>
using Linked_queue_iterator = Queue_iterator<T>;

template<typename T>
using Linked_queue = Queue<T>;

#endif // LINKED_QUEUE_H
