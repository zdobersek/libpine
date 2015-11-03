#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>

#include "unwind_bt.h"

static void* (*malloc_sym)(size_t) = NULL;
static void load_malloc_sym()
{
    malloc_sym = dlsym(RTLD_NEXT, "malloc");
    if (malloc_sym == NULL)
        fprintf(stderr, "Failed to load 'malloc'\n");
}

void* malloc(size_t size)
{
    if (malloc_sym == NULL)
        load_malloc_sym();
    if (malloc_sym == NULL)
        return NULL;

    UNWIND_BT();
    return malloc_sym(size);
}
