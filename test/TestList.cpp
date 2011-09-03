#include "TestList.h"

#include "../src/List.hpp"
__USING_NAMESPACE_THIS__


void Test::testList()
{
    //Log( "class implemented by %s\n", implementation_type::name );
    
#if !USING_BOOST && !USING_STL
    Log("start test List\n");
    {   // check root
        typedef int* data_type;
        List<data_type> *testee = new List<data_type>();
        ASSERT ( testee->root_ != 0 ); 
        ASSERT ( testee->root_->next == testee->root_ );
        ASSERT ( testee->root_->prev == testee->root_ );
        delete testee;
    }
    
#endif
    
    
    Log("test ok.\n");
}

