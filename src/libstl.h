#ifndef LIB_STL_H
#define LIB_STL_H

struct libstl{ static const char *name; };
const char *libstl::name = "stl";
typedef libstl implementation_type;

#include <vector>
#include <list>

#endif
