#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "Config.h"
#include "Debug.h"

__BEGIN_EASYGRAPH__

#define TEMPLATE_T template<typename T>

/**
 * iterator class with a pointer to linked list nodes
 * @note [todo] for const pointers and references
 */
TEMPLATE_T class iterator:public Object
{
public:
    typedef T data_type;
    typedef T* pointer;
    typedef T& reference;
    
    static const pointer null;
private:
    pointer ptr_;
    
    /**
     * constructor
     */
    iterator( const pointer ptr = null ):ptr_( ptr ){}
    
    /**
     * copy constructor
     */
    iterator( const iterator& itr ){
        ptr_ = itr.ptr_;
    }
    
    /**
     *  assignment operator
     */
    iterator& operator= ( const iterator& itr ){
        if( this != &itr ){  //  to avoid substitute itself
            ptr_ = itr.ptr_;
        }
        return *this;
    }
    
    /**
     * assignment operator for pointer type
     */
    iterator& operator=( const pointer ptr ){
        ptr_ = ptr;
        return *this;
    }
    
    /**
     * pre increment oprator
     */
    iterator& operator++(int dummyForPreOperator){
        ptr_ = ptr_ -> next;
        return *this;
    }
    
    /**
     * post increment oprator
     */
    iterator& operator++(){
        ptr_ = ptr_ -> next;
        return *this;
    }
    
    /**
     * post decrement oprator
     */
    iterator& operator--(){
        ptr_ = ptr_ -> prev;
        return *this;
    }
    /** 
     * pre decrement oprator
     */
    iterator& operator--(int dummyForPreOperator){
        ptr_ = ptr_ -> prev;
        return *this;
    }
    
    /**
     * reference operator
     */
    reference operator*() const
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

// define null pointer
TEMPLATE_T const typename iterator<T>::pointer iterator<T>::null = 0;

__END_EASYGRAPH__

#endif

