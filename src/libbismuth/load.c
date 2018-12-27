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
    resetVector = *(uint16_t*)(ctx->cart + 0x0ffc);
    printf("Reset vector at 0x%04x\n", resetVector);
    ctx->cpu.pc = resetVector;
}
