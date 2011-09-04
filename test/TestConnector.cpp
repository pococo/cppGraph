#include "TestList.h"

#include "Config.h"
#include "Vertex.hpp"

__BEGIN_EASYGRAPH__

void Test::testConnector()
{
    Log( "class implemented by %s\n", IMPL_LIBRARY );
    
#if !USING_BOOST && !USING_STL
    Log("start testConnector\n");
    { //check constructor
        Connector connector;
        ASSERT( connector.vertex_ == 0 );
        //ASSERT( connector.edge_ == 0 );
    }
    
#endif
    
    Log("test ok.\n");
}

__END_EASYGRAPH__

