#include <stdio.h>
#include <stdlib.h>
#include <bismuth/bismuth.h>

int main(int argc, char** argv)
{
    BiContext* ctx;
    FILE* f;
    char* buf;
    size_t size;

    if (argc != 2)
        return 1;

    ctx = biCreateContext();
    f = fopen(argv[1], "r");
    if (!f)
        return 1;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = (char*)malloc(size);
    fread(buf, size, 1, f);
    fclose(f);
    biLoad(ctx, buf, size);
    free(buf);
    for (;;)
    {
        biRunCycles(ctx, 16384);
    }
    biDestroyContext(ctx);
    return 0;
}
