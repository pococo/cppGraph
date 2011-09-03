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
    {   // check create next ( in case of first creation )
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
    {   // check create next ( in case of the second creation )
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
    {   // check create prev ( in case of first creation )
        list_t *testee = new list_t();
        node_t *new_node = testee -> create_next(testee -> root_, 0);
        ASSERT ( testee->root_->next == new_node );
        ASSERT ( testee->root_->prev == new_node );
        ASSERT ( testee->root_ == new_node->next );
        ASSERT ( testee->root_ == new_node->prev );
        ASSERT ( testee->size_ == 1 );
        delete testee;
    }
    {   // check create prev ( in case of second creation )
        list_t *testee = new list_t();
        node_t *root = testee->root_;
        node_t *new_node0 = testee -> create_prev(testee -> root_, 100);
        node_t *new_node1 = testee -> create_prev(testee -> root_, 200);
        ASSERT ( new_node0->next == new_node1 );
        ASSERT ( new_node0->prev == root );
        ASSERT ( new_node1->next == root );
        ASSERT ( new_node1->prev == new_node0 );
        ASSERT ( root->next == new_node0 );
        ASSERT ( root->prev == new_node1 );
        ASSERT ( testee->size_ == 2 );
        delete testee;
    }
    {   // check erase
        list_t *testee = new list_t();
        // create 2 nodes
        node_t *new_node0 = testee -> create_prev(testee -> root_, 100);
        node_t *new_node1 = testee -> create_prev(testee -> root_, 200);
        // erase 1 node
        node_t *ret_node = testee->erase( new_node0 );
        ASSERT ( ret_node == new_node1 );
        ASSERT ( testee->size_ == 1 );
        delete testee;
    }
    {   // check erase ( in case of no node )
        list_t *testee = new list_t();
        // erase a node
        node_t *ret_node = testee->erase( testee->root_ );
        ASSERT ( ret_node == 0 );
        ASSERT ( testee->size_ == 0 );
        delete testee;
    }
    {   // check begin end front back
        list_t testee;
        node_t* new_node0 = testee.create_prev(testee.root_, 100);
        testee.create_prev(testee.root_, 200);
        ASSERT ( testee.begin() == list_t::iterator(new_node0) );
        ASSERT ( testee.end() == testee.root_ );
        ASSERT ( testee.front() == 100 );
        ASSERT ( testee.back() == 200 );
    }
    {   // check push_back
        list_t *testee = new list_t();
        testee->push_back( 100 );
        testee->push_back( 200 );
        ASSERT ( testee->root_->next->data == 100 );
        ASSERT ( testee->root_->prev->data == 200 );
        ASSERT ( testee->size_ == 2 );
        delete testee;
    }
    {   // check pop_back
        list_t *testee = new list_t();
        testee->push_back( 100 );
        testee->push_back( 200 );
        testee->pop_back();
        ASSERT ( testee->root_->next->data == 100 );
        ASSERT ( testee->size() == 1 );
        delete testee;
    }
    {   // check insert
        list_t *testee = new list_t();
        testee->push_back( 200 );
        list_t::iterator itr = testee->begin();
        testee->insert( itr , 100 );
        ASSERT ( testee->root_->next->data == 100 );
        ASSERT ( testee->size() == 2 );
        delete testee;
    }
    {   // check erase
        list_t *testee = new list_t();
        testee->push_back( 100 );
        testee->push_back( 200 );
        list_t::iterator itr = testee->begin();
        testee->erase( itr );
        ASSERT ( testee->root_->next->data == 200 );
        ASSERT ( testee->size() == 1 );
        delete testee;
    }
    {   // check size
        list_t *testee = new list_t();
        ASSERT ( testee->size() == 0 );
        testee -> create_prev(testee -> root_, 100);
        testee -> create_prev(testee -> root_, 200);
        ASSERT ( testee->size() == 2 );
        delete testee;
    }
    {   // check is empty
        list_t *testee = new list_t();
        testee -> create_prev(testee -> root_, 100);
        testee -> create_prev(testee -> root_, 200);
        ASSERT ( testee->size() == 2 );
        delete testee;
    }
    {   // check operator[i], at
        list_t testee;
        node_t* new_node0 = testee.create_prev(testee.root_, 100);
        node_t* new_node1 = testee.create_prev(testee.root_, 200);
        ASSERT ( testee[0] == new_node0->data );
        ASSERT ( testee[1] == new_node1->data );
        ASSERT ( testee.at(0) == new_node0->data );
        ASSERT ( testee.at(1) == new_node1->data );
    }
#endif
    
    
    Log("test ok.\n");
}

