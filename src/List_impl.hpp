#ifndef LIST_H
#define LIST_H

#include "Config.h"
#include "Debug.h"
#include "type_traits.h"

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
    
    /**
     * add new node at the next of the last element (with input a value)
     */
    void push_back(const data_type& data);
    
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
     * return the "i"th element
     */
	reference operator[](unsigned int i);
    
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
     * insert a node with "value" at the next of position "pos"
     */
    void insert(iterator pos, const data_type& value);
    
    /**
     * erase a node at position "pos"
     */
    iterator erase( iterator pos );
private:
    
    /**
     * insert node
     */
    void insert_next(Node* node, const data_type& data);
    
    
    size_type size_; //<! list size ( the number of nodes )
    Node*     root_; //<! a root node for dummy
    
public:
    typedef typename List<T>::Node node_type;
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
        iterator& operator++(int dummyForPreOperator){
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
        iterator& operator--(int dummyForPreOperator){
            ptr_ = ptr_ -> prev; return *this;
        }
        
        /**
         * reference operator
         */
        T operator*() const
        { return ptr_ -> data; }
        
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
        
        friend struct Test;
    };
    friend struct Test;
};


TEMPLATE_T
List<T>::List(){
	root_ = new List<T>::Node();
	root_ -> next = root_;
	root_ -> prev = root_;
	size_ = 0;
}

//destructor
TEMPLATE_T
List<T>::~List(){
	clear();
    if(root_){
        delete root_;
        root_ = 0;
    }
}

TEMPLATE_T void List<T>::clear()
{
    //iterator itr = begin();
    if( is_pointer<T>::ret ){
        Log("pointer type");
        // delete 
    }
}
// define null pointer
//TEMPLATE_T const typename List<T>::node_type* List<T>::null = 0;

__END_EASYGRAPH__

#endif

