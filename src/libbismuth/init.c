#include <stdlib.h>
#include <libbismuth/libbismuth.h>

#define zalloc(x)   calloc(1, x)

BiContext* biCreateContext(void)
{
    BiContext* ctx;
    ctx = zalloc(sizeof(*ctx));
    ctx->wram = zalloc(WRAM_SIZE);
    return ctx;
}

void biDestroyContext(BiContext* ctx)
{
    if (ctx)
    {
        free(ctx->wram);
        free(ctx);
    }
}
