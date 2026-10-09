#include <stdint.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct Array {
        size_t size;
        int *data;
} Array;

typedef struct Tests {
        size_t n;
        Array *arrays;
} Tests;

#endif