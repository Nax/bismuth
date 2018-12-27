#include <bismuth/bismuth.h>

int main(int argc, char** argv)
{
    BiContext* ctx;

    ctx = biCreateContext();
    biDestroyContext(ctx);
    return 0;
}
