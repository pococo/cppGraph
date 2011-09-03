#ifndef LIB_C_H
#define LIB_C_H

/**
 * libc wrapper
 */
struct libc{
    typedef int (*printf_t)(const char*, ...);
    static printf_t printf;
    static void assert__(bool expression);
};

#define IMPL_LIBRARY "libc"

#endif
