all: \
	libpine_backtrace_malloc \
	libpine_backtrace_memcpy

LIBUNWIND_CFLAGS	:= `pkg-config --cflags libunwind`
LIBUNWIND_LIBS		:= `pkg-config --libs libunwind`

libpine_backtrace_malloc:
	gcc -shared -fPIC -o libpine_backtrace_malloc.so src/backtrace/malloc.c ${LIBUNWIND_CFLAGS} ${LIBUNWIND_LIBS}

libpine_backtrace_memcpy:
	gcc -shared -fPIC -o libpine_backtrace_memcpy.so src/backtrace/memcpy.c ${LIBUNWIND_CFLAGS} ${LIBUNWIND_LIBS}
