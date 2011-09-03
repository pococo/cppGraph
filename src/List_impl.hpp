#ifndef LIST_H
#define LIST_H

#include "Config.h"
#include "Debug.h"
//#include "type_traits.h"

__BEGIN_EASYGRAPH__

#define TEMPLATE_T template<typename T>

/*-------------------------------------------------------------//
 //	this linked list has cyclic structure.
 //	root node<--->node0<--->node1<--...--nodeN-1--root node
 //  where N: list size
 //  if there're no node, root->next = root->prev = root
 //-------------------------------------------------------------*/

/**
 * lined list class
 */
TEMPLATE_T class List:public Object{
public:
    typedef T data_type;
    typedef T* pointer;
    typedef T& reference;
    typedef unsigned int size_type;
    
    /**
     * linked list node class
     */
    struct Node:public Object{
        Node* prev;
        Node* next;
        data_type data;
        Node():prev(0),next(0){}
    };
    
    typedef typename List<T>::Node node_type;
    
    // forwaed decralation
    class iterator;

    /**
     * constructor
     */
	List();
    
	/**
     * destructor
     */
	~List();
    
    // todo list-->
    /**
     * add new node at the next of the last element (with input a value)
     */
    void push_back( const data_type& data );
    
    /**
     * delete last node
     */
	void pop_back();
    
    /**
     * delete all elements
     */
    void clear();
    
    /**
     * return an element at position "index"
     */
    reference at( size_type index );

    /**
     * return the "index"th element
     */
	reference operator[](unsigned int index);
    
    /**
     * return an iterator to begining element
     */
    iterator begin() const;
    
    /**
     * return an iterator to the last element
     */    
    iterator end() const;
    
    /**
     * is list empty or not
     */
    bool empty() const;
    
    /**
     * return a reference to the first element
     */
    reference front() const;

    /**
     * return a reference to the last element
     */
    reference back() const;
    
    /**
     * get list size
     */
    size_type size() const;
    
    /**
     * insert a node with "data" at the next of position "pos"
     */
    void insert(iterator pos, const data_type& data);
    
    /**
     * erase a node at position "pos"
     */
    iterator erase( iterator pos );
    
    
private:
    
    /**
     * create a new node at the next position of a target node
     */
    node_type* create_next( node_type* target_node, const data_type& data );

    /**
     * create a new node at the previous position of a target node
     */
    node_type* create_prev( node_type* target_node, const data_type& data );
    
    /**
     * erase the target node
     */
    node_type* erase( node_type* target_node );

    
    size_type size_; //<! list size ( the number of total nodes )
    Node*     root_; //<! a root node ( always exists as dummy )
    
public:
    
    /**
     * iterator class with a pointer to linked list nodes
     * @note [todo] for const pointers and references
     */
    class iterator:public Object
    {
    private:
        node_type* ptr_;
    public:
        /**
         * constructor
         */
        iterator( node_type* ptr = 0 ):ptr_( ptr ){}
        /**
         * copy constructor
         */
        iterator( const iterator& itr ):ptr_( itr.ptr_ ){}
        /**
         *  assignment operator
         */
        iterator& operator= ( const iterator& itr ){
            if( this != &itr ){ ptr_ = itr.ptr_; } //  to avoid substitute itself
            return *this;
        }
        
        /**
         * assignment operator for pointer type
         */
        iterator& operator=( const pointer ptr ){
            ptr_ = ptr; return *this;
        }
        
        /**
         * pre increment oprator
         */
        iterator& operator++( int dummy ){
            ptr_ = ptr_ -> next; return *this;
        }
        
        /**
         * post increment oprator
         */
        iterator& operator++(){
            ptr_ = ptr_ -> next; return *this;
        }
        
        /**
         * post decrement oprator
         */
        iterator& operator--(){
            ptr_ = ptr_ -> prev; return *this;
        }
        
        /** 
         * pre decrement oprator
         */
        iterator& operator--( int dummy ){
            ptr_ = ptr_ -> prev; return *this;
        }
        
        /**
         * reference operator
         */
        node_type* operator*() const
        { return ptr_; }
        
        /**
         * equality operator( equal to )
         */
        bool operator== ( const iterator& itr ) const
        { return ptr_ == itr.ptr_ ; }
        
        /**
         * equality operator( not equal to )
         */
        bool operator!= (const iterator& itr) const
        { return ptr_ != itr.ptr_; }
        
        // todo if necessary
        // >, < , >=, <=
        // compare iterator to node_type* directly..
        
        friend struct Test;
    };
    friend struct Test;
};

// constructor
TEMPLATE_T
List<T>::List(){
	root_ = new List<T>::Node();
	root_ -> next = root_ -> prev = root_;
	size_ = 0;
}

//destructor
TEMPLATE_T
List<T>::~List(){
	clear();
    if( root_ ){
        delete root_;
        root_ = 0;
    }
}

// delete all elements
TEMPLATE_T void List<T>::clear(){
	iterator itr_current = iterator( root_ -> next );
    iterator itr_end = iterator( root_ );
	while( itr_current != itr_end ){
		erase( *itr_current++ );
	}
	root_ -> next = root_;
	root_ -> prev = root_;
	size_ = 0;
}

// create a new node at the next position of a target node
TEMPLATE_T typename List<T>::node_type* List<T>::create_next( node_type* target_node, const data_type& data )
{
	if( target_node == 0 ) return 0;
	node_type* new_node = new node_type();
	new_node -> prev = target_node;
	new_node -> next = target_node -> next;
	target_node -> next -> prev = new_node;
	target_node -> next = new_node;

    new_node -> data = data;
    size_++;
    return new_node;
}

// create a new node at the previous position of a target node
TEMPLATE_T typename List<T>::node_type* List<T>::create_prev(node_type* target_node,const data_type& data )
{
	if( target_node == 0 ) return 0;
    
	node_type* new_node = new node_type();
	new_node -> prev = target_node -> prev;
	new_node -> next = target_node;
	target_node -> prev -> next = new_node;
	target_node -> prev = new_node;
    
	new_node -> data = data;
    size_++;
    return new_node;
}

// erase the target node
TEMPLATE_T typename List<T>::node_type* List<T>::erase( node_type* target_node )
{
	if( target_node == root_ || target_node == 0 ) return 0;
    node_type* next_node = target_node -> next;
	target_node -> prev -> next = target_node -> next;
	target_node -> next -> prev = target_node -> prev;
	delete target_node;
    size_--;
    return next_node;
}

// return iterator to beginning node
TEMPLATE_T typename List<T>::iterator List<T>::begin() const
{
    return iterator( root_ -> next );
}

// return iterator to end node( = root )
TEMPLATE_T typename List<T>::iterator List<T>::end() const
{
    return iterator( root_ );
}

// push back data
TEMPLATE_T void List<T>::push_back(const data_type& data)
{
	create_prev( root_, data );
}

// pop back data
TEMPLATE_T void List<T>::pop_back()
{
    erase( root_ -> prev );
}

TEMPLATE_T void List<T>::insert(iterator pos, const data_type& data )
{
    create_prev( *pos, data );
}

TEMPLATE_T typename List<T>::iterator List<T>::erase( iterator pos )
{
    return iterator( erase( *pos ) );
}

TEMPLATE_T typename List<T>::data_type& List<T>::operator[]( size_type index )
{
	iterator itr_current( root_-> next );
	iterator itr_end( root_ );
	while( itr_current != itr_end ){
		if( index == 0 ){
			return ( *itr_current ) -> data;
		}
		itr_current++;
        index--;
	}
	return root_->data;
}

TEMPLATE_T typename List<T>::data_type& List<T>::at( size_type index )
{
    return this->operator[]( index );
}

TEMPLATE_T bool List<T>::empty() const
{
    return ( size_ == 0 );
}

TEMPLATE_T typename List<T>::reference List<T>::front() const
{
    return root_ -> next -> data;
}

TEMPLATE_T typename List<T>::reference List<T>::back() const
{
    return root_ -> prev -> data;
}

TEMPLATE_T typename List<T>::size_type List<T>::size() const
{
    return size_;
}

__END_EASYGRAPH__

#endif

