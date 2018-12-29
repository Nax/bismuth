#ifndef LIBBISMUTH_H
#define LIBBISMUTH_H

#include <stdint.h>
#include <bismuth/bismuth.h>
#include <libbismuth/op.h>

#define WRAM_SIZE   0x20000

#define CPU_FLAG_C 0x01
#define CPU_FLAG_Z 0x02
#define CPU_FLAG_I 0x04
#define CPU_FLAG_D 0x08
#define CPU_FLAG_X 0x10
#define CPU_FLAG_M 0x20
#define CPU_FLAG_V 0x40
#define CPU_FLAG_N 0x80

typedef union {
    uint16_t    u16;
    int16_t     i16;
    struct {
        union {
            uint8_t     lo_u8;
            int8_t      lo_i8;
        };
        union {
            uint8_t     hi_u8;
            int8_t      hi_i8;
        };
    };
} BiReg;

typedef struct {
    uint16_t    pc;
    BiReg       ac;
    BiReg       x;
    BiReg       y;
    uint16_t    d;
    uint16_t    s;
    uint8_t     pbr;
    uint8_t     dbr;
    uint8_t     p;
    uint8_t     e:1;
} BiCPU;

struct BiContext_ {
    BiCPU       cpu;
    uint8_t*    wram;
    size_t      cartSize;
    uint8_t*    cart;
};

uint8_t     biMemoryRead8(BiContext* ctx, uint8_t bank, uint16_t addr);
uint16_t    biMemoryRead16(BiContext* ctx, uint8_t bank, uint16_t addr);
void        biMemoryWrite8(BiContext* ctx, uint8_t bank, uint16_t addr, uint8_t value);
void        biMemoryWrite16(BiContext* ctx, uint8_t bank, uint16_t addr, uint16_t value);

uint8_t     biMemoryLinearRead8(BiContext* ctx, uint32_t vaddr);
uint16_t    biMemoryLinearRead16(BiContext* ctx, uint32_t vaddr);
void        biMemoryLinearWrite8(BiContext* ctx, uint32_t vaddr, uint8_t value);
void        biMemoryLinearWrite16(BiContext* ctx, uint32_t vaddr, uint16_t value);

#endif
