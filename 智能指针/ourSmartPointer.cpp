#include <iostream>
#include <cmath>
using namespace std;

//更具创建指针的方式不同选择释放指针的方式
// malloc()创建
template<class T>
struct Free
{
    void operator()(T* ptr){free(ptr);} //重载()运算符
};

// new一个指针
template<typename T>
struct Delete
{
    void operator()(T* ptr){delete ptr;}
};

// new一个数组指针
template<typename T>
struct DeleteAsrr
{
   void operator()(T* ptr){delete[] ptr;}
};

template<class T,class Del=Delete<T>> //T是某个类型的指针 Del是释放指针的结构指针
class SmartPointer{
public:
    SmartPointer(T* ptr = nullptr){
        ptr_=ptr;    
    }

    ~SmartPointer(){
        Del del;
        del(ptr);
    }

    //重载解除引用符 访问ptr指向的资源
    T& operator *(){
        return *ptr_;
    }

    //重载成员变量访问符  访问ptr指向的资源
    T* operator ->(){
        return ptr_;
    }

    //实现浅拷贝和深拷贝

private:
    T* ptr_; //维护的指针变量
};

int main()
{
    
    system("pause");
    return 0;
}
