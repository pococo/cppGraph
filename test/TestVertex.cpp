#include "TestList.h"


#include "Config.h"
#include "List.hpp"
#include "Vertex.hpp"

__BEGIN_EASYGRAPH__

void Test::testVertex()
{
    Log( "class implemented by %s\n", IMPL_LIBRARY );
    
#if !USING_BOOST && !USING_STL
    Log("start testVertex\n");
    
    {   // check constructor
        //Vertex testee;
        //ASSERT( testee.connectivity_ == 0 );
    }
#endif
    
    Log("test ok.\n");
}

__END_EASYGRAPH__

