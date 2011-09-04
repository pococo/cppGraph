#ifndef LIST_H
#define LIST_H

#include "Config.h"
#include "Debug.h"
//#include "type_traits.h"

__BEGIN_EASYGRAPH__


/**
 * linked list node class
 */
template < class T >
struct Node:public Object{
    typedef T data_type;
    Node* prev;
    Node* next;
    T data;
    Node():prev(0),next(0){
    }
    ~Node(){
    }
};

/**
 * linked list node class for pointer type
 */
template < class T >
struct PtrNode:public Object{
    typedef T* data_type;
    PtrNode* prev;
    PtrNode* next;
    T* data;
    PtrNode():prev(0),next(0),data(0){
    }
    ~PtrNode(){
        if ( data ) {
            delete data;
            data = 0;
        }
    }
};

/*-------------------------------------------------------------//
 //	this linked list has cyclic structure.
 //	root node<--->node0<--->node1<--...--nodeN-1--root node
 //  where N: list size
 //  if there're no NodeType, root->next = root->prev = root
 //-------------------------------------------------------------*/

#define TEMPLATE_TN template<class T, class NodeType >

/**
 * lined list class
 */
TEMPLATE_TN
class ListTemplate:public Object{
public:
    typedef NodeType Node;
    typedef typename Node::data_type data_type;
    typedef data_type* pointer;
    typedef data_type& reference;
    typedef unsigned int size_type;

    /**
     * constructor
     */
	ListTemplate();
    
	/**
     * destructor
     */
	~ListTemplate();
    
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
     * create a new node at the next position of a target node
     */
    Node* create_next( Node* target_node, const data_type& data );

    /**
     * create a new node at the previous position of a target node
     */
    Node* create_prev( Node* target_node, const data_type& data );
    
    /**
     * erase the target NodeType
     */
    virtual Node* erase( Node* target_node );

private:
    size_type size_; //<! list size ( the number of total nodes )
    Node*     root_; //<! a root node ( always exists as dummy )
public:
    /**
     * iterator class with a pointer to linked list nodes
     * @note [todo] for const pointers and references
     */
    class iterator:public Object{
    private:
        Node* ptr_;
    public:
        /**
         * constructor
         */
        iterator( Node* ptr = 0 ):ptr_( ptr ){}
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
        Node* operator*() const
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
        // compare iterator to NodeType_type* directly..
        friend class Test;
    };
    
    
    /**
     * insert a node with "data" at the next of position "pos"
     */
    void insert(iterator pos, const data_type& data);
    
    /**
     * erase a node at position "pos"
     */
    iterator erase( iterator pos );
    /**
     * return an iterator to begining element
     */
    iterator begin() const;
    
    /**
     * return an iterator to the last element
     */    
    iterator end() const;
    
    friend class Test;
};

// constructor
TEMPLATE_TN ListTemplate< T, NodeType >::ListTemplate(){
	root_ = new Node();
	root_ -> next = root_ -> prev = root_;
	size_ = 0;
}

//destructor
TEMPLATE_TN ListTemplate< T, NodeType >::~ListTemplate(){
	clear();
    if( root_ ){
        delete root_;
        root_ = 0;
    }
}

// delete all elements
TEMPLATE_TN void ListTemplate< T, NodeType >::clear(){
	iterator itr_current = iterator( root_ -> next );
    iterator itr_end = iterator( root_ );
	while( itr_current != itr_end ){
		itr_current = erase( itr_current );
	}
	root_ -> next = root_;
	root_ -> prev = root_;
	size_ = 0;
}

// create a new node at the next position of a target node
TEMPLATE_TN  NodeType* ListTemplate< T, NodeType >::create_next( NodeType* target_node, const data_type& data )
{
	if( target_node == 0 ) return 0;
	Node* new_node = new Node();
	new_node -> prev = target_node;
	new_node -> next = target_node -> next;
	target_node -> next -> prev = new_node;
	target_node -> next = new_node;

    ( new_node -> data ) = data;
    size_++;
    return new_node;
}

// create a new node at the previous position of a target node
TEMPLATE_TN NodeType* ListTemplate< T, NodeType >::create_prev( NodeType* target_node,const data_type& data )
{
	if( target_node == 0 ) return 0;
    
	Node* new_node = new Node;
	new_node -> prev = target_node -> prev;
	new_node -> next = target_node;
	target_node -> prev -> next = new_node;
	target_node -> prev = new_node;
    
	( new_node -> data ) = data;
    size_++;
    return new_node;
}

// erase the target node
TEMPLATE_TN NodeType* ListTemplate< T, NodeType >::erase( NodeType* target_node )
{
	if( target_node == root_ || target_node == 0 ) return 0;
    Node* next_node = target_node -> next;
	target_node -> prev -> next = target_node -> next;
	target_node -> next -> prev = target_node -> prev;
	delete target_node;
    size_--;
    return next_node;
}

// return iterator to beginning node
TEMPLATE_TN typename ListTemplate< T, NodeType >::iterator ListTemplate< T, NodeType >::begin() const
{
    return iterator( root_ -> next );
}

// return iterator to end node( = root )
TEMPLATE_TN typename ListTemplate< T, NodeType >::iterator ListTemplate< T, NodeType >::end() const
{
    return iterator( root_ );
}

// push back data
TEMPLATE_TN void ListTemplate< T, NodeType >::push_back(const data_type& data)
{
	create_prev( root_, data );
}

// pop back data
TEMPLATE_TN void ListTemplate< T, NodeType >::pop_back()
{
    erase( root_ -> prev );
}

TEMPLATE_TN void ListTemplate< T, NodeType >::insert(iterator pos, const data_type& data )
{
    create_prev( *pos, data );
}

TEMPLATE_TN typename ListTemplate< T, NodeType >::iterator ListTemplate< T, NodeType >::erase( iterator pos )
{
    return iterator( erase( *pos ) );
}

TEMPLATE_TN typename ListTemplate< T, NodeType >::data_type& ListTemplate< T, NodeType >::operator[]( size_type index )
{
	iterator itr_current( root_-> next );
	iterator itr_end( root_ );
	while( itr_current != itr_end ){
		if( index == 0 ){
            Node* node = *itr_current;
			return ( node -> data );
		}
		itr_current++;
        index--;
	}
	return ( root_->data );
}

TEMPLATE_TN typename ListTemplate< T, NodeType >::data_type& ListTemplate< T, NodeType >::at( size_type index )
{
    return this->operator[]( index );
}

TEMPLATE_TN bool ListTemplate< T, NodeType >::empty() const
{
    return ( size_ == 0 );
}

TEMPLATE_TN typename ListTemplate< T, NodeType >::reference ListTemplate< T, NodeType >::front() const
{
    return ( root_ -> next -> data );
}

TEMPLATE_TN typename ListTemplate< T, NodeType >::reference ListTemplate< T, NodeType >::back() const
{
    return ( root_ -> prev -> data );
}

TEMPLATE_TN typename ListTemplate< T, NodeType >::size_type ListTemplate< T, NodeType >::size() const
{
    return size_;
}

template< class T >
class List:public ListTemplate< T, Node<T> >{
};

template< class T >
class ptr_list:public ListTemplate< T, PtrNode<T> >{
};

__END_EASYGRAPH__

#endif

