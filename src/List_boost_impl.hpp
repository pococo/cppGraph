#ifndef LIST_BOOST_IMPL_HPP
#define LIST_BOOST_IMPL_HPP

#include "Config.h"
#include "Debug.h"
#include "libboost.hpp"

__BEGIN_EASYGRAPH__

template <class T>
class List: public boost::ptr_vector<T>, public Object
{
    // todo
};


__END_EASYGRAPH__


#endif
