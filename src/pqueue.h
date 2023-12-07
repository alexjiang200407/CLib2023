#pragma once
#include "vector.h"
#include <stdbool.h>

typedef struct pqueue* PQueue;

PQueue PQNew(size_t elemSz, cmpF cmp);

bool PQIsEmpty(PQueue queue);

Item PQInsert(PQueue queue, Item insert);

Item PQPeek(PQueue queue);

Item PQPop(PQueue queue);

Item PQRemove(PQueue queue, size_t i);

void PQFree(PQueue queue);