#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
    printf("kernel panic!\n");
#else
    printf("aborting...");
#endif
    while (1) { }
    __builtin_unreachable();
}