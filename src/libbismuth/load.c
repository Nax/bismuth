#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libbismuth/libbismuth.h>

void biLoad(BiContext* ctx, const void* data, size_t size)
{
    uint16_t resetVector;

    if (ctx->cart)
        free(ctx->cart);
    ctx->cart = malloc(size);
    ctx->cartSize = size;
    memcpy(ctx->cart, data, size);

    memset(&ctx->cpu, 0, sizeof(ctx->cpu));
    memset(ctx->wram, 0, WRAM_SIZE);
    ctx->cpu.s = 0x1ff;
    ctx->cpu.e = 1;
    ctx->cpu.p = CPU_FLAG_M | CPU_FLAG_X | CPU_FLAG_I;

    resetVector = biMemoryRead16(ctx, 0, 0xfffc);
    ctx->cpu.pc = resetVector;
    printf("Reset vector at 0x%04x\n", resetVector);
}
