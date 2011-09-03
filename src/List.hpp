#ifndef LIST_HPP
#define LIST_HPP

#include "Config.h"

// select linked list implementation
#if USING_BOOST
#include "List_boost_impl.hpp"
#elif USING_STL
#include "List_stl_impl.hpp"
#else
#include "List_impl.hpp"
#endif


#endif