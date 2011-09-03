/**
 * macro definitons for debugging
 */
#ifndef DEBUG_H
#define DEBUG_H

#include "libc.h"
#if USING_BOOST
    #include "libboost.hpp"
#endif

// output logs, error logs
#define Log libc::printf
#define ErrorLog( str ) libc::printf("error:%s, file:%s, line:%d", str, __FILE__, __LINE__ );

//#define _NDEBUG

// ASSERT
#if USING_BOOST
    #define ASSERT(expression) BOOST_ASSERT(expression)
#else
    #define ASSERT(expression) libc::assert__(expression)
#endif

#endif
