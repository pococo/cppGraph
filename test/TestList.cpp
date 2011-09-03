#include "TestList.h"

#include "../src/List.hpp"
__USING_NAMESPACE_THIS__


void Test::testList()
{
    Log( "class implemented by %s\n", IMPL_LIBRARY );
    
#if !USING_BOOST && !USING_STL
    Log("start test List\n");
    typedef int data_type;
    typedef List<data_type> list_t;
    typedef list_t::node_type node_t;
    {   // check root
        typedef int* data_type;
        list_t *testee = new list_t();
        ASSERT ( testee->root_ != 0 ); 
        ASSERT ( testee->root_->next == testee->root_ );
        ASSERT ( testee->root_->prev == testee->root_ );
        delete testee;
    }
    {   // check create next ( in case of next root node )
        list_t *testee = new list_t();
        node_t *new_node = testee -> create_next(testee -> root_, 100);
        ASSERT ( testee->root_->next == new_node );
        ASSERT ( testee->root_->prev == new_node );
        ASSERT ( testee->root_ == new_node->next );
        ASSERT ( testee->root_ == new_node->prev );
        ASSERT ( 100 == new_node->data );
        ASSERT ( testee->size_ == 1 );
        delete testee;
    }
    {   // check create next ( in case of the second node )
        list_t *testee = new list_t();
        node_t *root = testee->root_;
        node_t *new_node1 = testee -> create_next(testee -> root_, 100);
        node_t *new_node0 = testee -> create_next(testee -> root_, 200);
        ASSERT ( new_node0->next == new_node1 );
        ASSERT ( new_node0->prev == root );
        ASSERT ( new_node1->next == root );
        ASSERT ( new_node1->prev == new_node0 );
        ASSERT ( root->next == new_node0 );
        ASSERT ( root->prev == new_node1 );        
        ASSERT ( 200 == new_node0 -> data );
        ASSERT ( 100 == new_node1 -> data );
        ASSERT ( testee->size_ == 2 );
        delete testee;
    }
    {   // check create prev ( in case of prev root node )
        list_t *testee = new list_t();
        testee -> create_next(testee -> root_, 0);
        node_t *new_node = testee -> root_->prev;
        ASSERT ( testee->root_->next == new_node );
        ASSERT ( testee->root_->prev == new_node );
        ASSERT ( testee->root_ == new_node->next );
        ASSERT ( testee->root_ == new_node->prev );
        ASSERT ( testee->size_ == 1 );
        delete testee;
        //delete new_node;
    }
    {   // check clear
        list_t *testee = new list_t();
        //node_t* new_node = new node_t();
        testee -> create_next(testee -> root_, 0);
        testee -> clear();
        ASSERT ( testee->root_->next == testee->root_ );
        ASSERT ( testee->root_->prev == testee->root_ );
        ASSERT( testee -> size_ == 0 );
        delete testee;
    }

    
#endif
    
    
    Log("test ok.\n");
}

