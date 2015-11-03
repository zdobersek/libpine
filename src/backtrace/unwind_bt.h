#include <libunwind.h>
#include <stdio.h>

#define UNWIND_BT() \
    { \
        unw_cursor_t cursor; \
        unw_context_t context; \
        unsigned i = 0; \
        unsigned frame_count = 32; \
    \
        unw_getcontext(&context); \
        unw_init_local(&cursor, &context); \
    \
        while (unw_step(&cursor) > 0 && i < frame_count) { \
            unw_word_t ip, sp, offp; \
            char name[256]; \
            name[0] = '\0'; \
    \
            unw_get_proc_name(&cursor, name, 256, &offp); \
            unw_get_reg(&cursor, UNW_REG_IP, &ip); \
            unw_get_reg(&cursor, UNW_REG_SP, &sp); \
    \
            fprintf(stderr, "#%u: %s (offp %lx) ip %lx sp %lx\n", \
                i, name, offp, ip, sp); \
    \
            ++i;\
        } \
        fprintf(stderr, "\n"); \
    }
