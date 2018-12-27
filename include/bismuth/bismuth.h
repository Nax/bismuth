#ifndef BISMUTH_H
#define BISMUTH_H

#include <stddef.h>

#if defined(__cplusplus)
# define BISMUTH_API    extern "C"
#else
# define BISMUTH_API
#endif

typedef struct BiContext_ BiContext;

BISMUTH_API BiContext*  biCreateContext(void);
BISMUTH_API void        biDestroyContext(BiContext* ctx);
BISMUTH_API void        biLoad(BiContext* ctx, const void* data, size_t size);
BISMUTH_API void        biRunCycles(BiContext* ctx, size_t cycles);

#endif
