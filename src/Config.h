#ifndef CONFIG_H
#define CONFIG_H
// basic configurations, common decralations

#define USING_BOOST 0
#define USING_STL 0
#define USING_LIBC 1

#define __BEGIN_EASYGRAPH__ namespace EasyGraph {
#define __END_EASYGRAPH__ }
#define __USING_NAMESPACE_THIS__ using namespace EasyGraph;


class Object{
public:
    virtual ~Object(){}
};

template <class T>
class tmp_auto_ptr:public Object{
public:
    tmp_auto_ptr(T* ptr):ptr_(ptr){}
    ~tmp_auto_ptr(){
        if (ptr_) {
            delete ptr_;
            ptr_ = 0;
        }
    }
private:
    T* ptr_;
};


#endif
