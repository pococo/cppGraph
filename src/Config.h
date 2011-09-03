#ifndef CONFIG_H
#define CONFIG_H

#define EASY_GRAPH_VERSION_MAJOR 1
#define EASY_GRAPH_VERSION_MINOR 0


#define USING_BOOST 0
#define USING_STL 0
#define USING_LIBC 1

// common macro definitions
#define __BEGIN_EASYGRAPH__ namespace EasyGraph {
#define __END_EASYGRAPH__ }
#define __USING_NAMESPACE_THIS__ using namespace EasyGraph;

class Object{
public:

};

//#define DENY_COPY_INSTANCES(classType)

#endif
