#include <stdio.h>
#include <libbismuth/libbismuth.h>

#define TRAP    do { printf("Bad opcode: 0x%02x at 0x%02x%04x\n", op, pbr, pcBak); getchar(); } while (0);

void biRunCycles(BiContext* ctx, size_t cycles)
{
    uint8_t op;
    uint16_t pc;
    uint16_t pcBak;
    uint8_t pbr;

    pc = ctx->cpu.pc;
    pbr = ctx->cpu.pbr;

    for (size_t cycleCounter = 0; cycleCounter < cycles; ++cycleCounter)
    {
        pcBak = pc;
        op = biMemoryRead8(ctx, pbr, pc);
        pc++;
        switch (op)
        {
        default:
            TRAP;
            break;
        }
    }

    ctx->cpu.pc = pc;
    ctx->cpu.pbr = pbr;
}
