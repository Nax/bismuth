#include <stdlib.h>
#include <libbismuth/libbismuth.h>

#define zalloc(x)   calloc(1, x)

BiContext* biCreateContext(void)
{
    BiContext* ctx;
    ctx = zalloc(sizeof(*ctx));
    return ctx;
}

void biDestroyContext(BiContext* ctx)
{
    free(ctx);
}
