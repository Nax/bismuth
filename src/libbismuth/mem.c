#include <stdio.h>
#include <libbismuth/libbismuth.h>

static uint16_t badIO(uint8_t bank, uint16_t addr, int write)
{
    printf("Bad IO (%s) at 0x%02x%04x\n", write ? "W" : "R", bank, addr);
    return 0;
}

#define MEMORY_READ(name, type)                                         \
type name (BiContext* ctx, uint8_t bank, uint16_t addr)                 \
{                                                                       \
    if (bank < 0x40)                                                    \
    {                                                                   \
        if (addr < 0x2000) return *(type*)(ctx->wram + addr);           \
        if (addr < 0x8000) return badIO(bank, addr, 0);                 \
        return *(type*)(ctx->cart + bank * 0x8000 + (addr & 0x7fff));   \
    }                                                                   \
    return badIO(bank, addr, 0);                                        \
}

MEMORY_READ(biMemoryRead8, uint8_t);
MEMORY_READ(biMemoryRead16, uint16_t);

#define MEMORY_WRITE(name, type)                                            \
void name (BiContext* ctx, uint8_t bank, uint16_t addr, type value)         \
{                                                                           \
    if (bank < 0x40)                                                        \
    {                                                                       \
        if (addr < 0x2000) { *(type*)(ctx->wram + addr) = value; return; }  \
        badIO(bank, addr, 1);                                               \
    }                                                                       \
    badIO(bank, addr, 1);                                                   \
}

MEMORY_WRITE(biMemoryWrite8, uint8_t);
MEMORY_WRITE(biMemoryWrite16, uint16_t);
