#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>

#include "unwind_bt.h"

static void* (*memcpy_sym)(void*, const void*, size_t) = NULL;
static void load_memcpy_sym()
{
    memcpy_sym = dlsym(RTLD_NEXT, "memcpy");
    if (memcpy_sym == NULL)
        fprintf(stderr, "Failed to load 'memcpy'.\n");
}

void* memcpy(void* dest, const void* src, size_t n)
{
    if (memcpy_sym == NULL)
        load_memcpy_sym();
    if (memcpy_sym == NULL)
        return NULL;

    UNWIND_BT();
    return memcpy_sym(dest, src, n);
}
