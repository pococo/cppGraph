#include "TestList.h"

#include "../src/List.hpp"

__USING_NAMESPACE_THIS__

void Test::testListIterator()
{
    Log( "class implemented by %s\n", IMPL_LIBRARY );
    
#if !USING_BOOST && !USING_STL
    Log("start test ListIterator\n");
    
    {   // check node
        List<int>::Node node;
        ASSERT( node.prev == 0 );
        ASSERT( node.next == 0 );
        ASSERT( node.data == 0 );
    }
    {   // check constructor
        List<int>::iterator testee;
        ASSERT ( 0 == testee.ptr_ );    }

    {   // check constructor
        List<int>::Node node;
        List<int>::iterator testee(&node);
        ASSERT ( &node == testee.ptr_ );    }

    {   // check copy constructor
        List<int>::Node src;
        List<int>::iterator itr_src(&src);
        List<int>::iterator itr_dest(itr_src);
        ASSERT ( itr_dest.ptr_ == itr_dest.ptr_ );    }

    {   // check assignment operator
        List<int>::Node src;
        List<int>::iterator itr_src(&src);
        List<int>::iterator itr_dest = itr_src;
        ASSERT ( itr_dest.ptr_ == itr_dest.ptr_ );    }

    {   // check pre increment oprator
        List<int>::Node node1;
        List<int>::Node node2;
        node1.next = &node2;
        List<int>::iterator testee(&node1);
        ASSERT ( (++testee).ptr_ == &node2 );    }
    
    {   // check post increment oprator
        List<int>::Node node1;
        List<int>::Node node2;
        node1.next = &node2;
        List<int>::iterator testee(&node1);
        ASSERT ( (testee++).ptr_ == &node2 );    }
    
    {   // check pre decrement oprator
        List<int>::Node node1;
        List<int>::Node node2;
        node2.prev = &node1;
        List<int>::iterator testee(&node2);
        ASSERT ( (--testee).ptr_ == &node1 );    }
    
    {   // check post decrement oprator
        List<int>::Node node1;
        List<int>::Node node2;
        node2.prev = &node1;
        List<int>::iterator testee(&node2);
        ASSERT ( (testee--).ptr_ == &node1 );    }
    
    {   // check reference oprator
        List<int>::Node node;
        node.data = 10;
        List<int>::iterator testee(&node);
        ASSERT ( *testee == 10 );               }
    
    {   // check equal to
        List<int>::Node node1;
        List<int>::iterator testee1(&node1);
        List<int>::iterator testee2(&node1);
        ASSERT ( testee1 == testee2 );          }
    
    {   // check non equal
        List<int>::Node node1;
        List<int>::Node node2;
        List<int>::iterator testee1(&node1);
        List<int>::iterator testee2(&node2);
        ASSERT ( testee1 != testee2 );          }
    
#endif
    
    Log("test ok.\n");
}

