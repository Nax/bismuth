#ifndef LIBBISMUTH_H
#define LIBBISMUTH_H

#include <stdint.h>
#include <bismuth/bismuth.h>

typedef struct {
    uint16_t    a;
    uint16_t    x;
    uint16_t    y;
    uint16_t    d;
    uint16_t    p;
    uint8_t     dbr;
    uint8_t     e:1;
} BiCPU;

struct BiContext_ {
    BiCPU   cpu;
};

#endif
