#ifndef LIB_C_H
#define LIB_C_H

struct libc{
    typedef int (*printf_t)(const char*, ...);
    static printf_t printf;
    static void assert__(bool expression);
    static const char *name;
};

typedef libc implementation_type;
#endif
