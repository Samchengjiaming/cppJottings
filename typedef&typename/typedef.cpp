#include <iostream>
#include <cmath>

using namespace std;

template <typename T>
class Point{
    public:
        T x;
        T y;
        T z;
        typedef int Int; //数据成员，可以直接定义别名
        typedef T::ptr* Ptr; //歧义
        /*
        如果T::ptr是一个结构体或者类，那么T::ptr*就是一个指针
        class T{
            struct ptr{
                //...
            }
        }
        如果T::ptr是一个变量，那么T::ptr* Ptr相当于一个成员变量进行乘法，但是未定义Ptr这个变量
        class T{
            int ptr;
        }
        */




        Point(T _x,T _y,T _z){
            x=_x;
            y=_y;
            z=_z;
        }

        void printInfo(){
            cout<<"x is : "<<x<<" y is : "<<y<<" z is : "<<z<<endl;
        }
};


int main()
{

    system("pause");
    return 0;
}