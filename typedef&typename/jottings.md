>文件更新日志
>***-version:0.1***
>***-date:2024/04/19***

参考：
[https://blog.csdn.net/m0_73640344/article/details/136736071](https://blog.csdn.net/m0_73640344/article/details/136736071)
[https://zhuanlan.zhihu.com/p/400426270](https://zhuanlan.zhihu.com/p/400426270)

## tyepdef关键字
在C++中，<b>typedef</b>是一种用于为数据类型定义一个新名字的关键字。它常被用来简化复杂的类型声明，增加代码的可读性，或者为特定的类型提供更具描述性的名称。<b>typedef</b>声明的作用域与变量和函数的作用域规则相同，因此可以在全局作用域、命名空间内、类定义内或局部作用域内使用<b>typedef</b>。

### typedef基本用法
1.定义基本类型的别名
```c++
    typedef unsigned int uint; // 定义unsigned int的别名为uint
    typedef double mat[2][2]; // 定义一个二维数组的别名 mat m1={{1,1},{2,2}};
    typedef void (*funPtr)(int,double);// 定义了FuncPtr作为指向接受一个int和一个double参数且返回void的函数指针的别名
```
2.简化结构体的定义
```c++
typedef struct
{
    double x;
    double y;
    double z;
} Point;
Point p1 =Point();
```
3.配合模板定义，简化泛型的实例化
```c++
template <typename T>
class myVector
{
    //定义
};
typedef myVector<int> myIntVector; //myIntVector是myVector<int>的别名，方便使用
myIntVector vec();
```
## using关键字替代typedef
<b>typedef</b>在C++中是一个非常有用的特性，可以提高代码的可读性和可维护性。它允许程序员为复杂的类型声明创建简短、易于理解的别名。C++11通过引入<b>using</b>声明为类型别名提供了一个更现代的语法，但<b>typedef</b>依然被广泛使用。
```c++
using uint = unsigned int;
using matrix = double[10][10];
using FuncPtr = void (*)(int, double);
```


## typedef typename组合使用
当使用typedef时，其后是可以跟着typename的，只不过一般不需要显式的写出来，可忽略。
但是在编写模板类的时候，涉及模板参数的typedef定义需要强制使用typename，否者编译器无法推断出这个类型是一个变量还是一个类型。例子：
```c++
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
};
```
参考pcl源码：
```C++
template <typename PointT>
class SampleConsensusModel
{
    public:
      
      //typedef定义pcl::PointCloud<PointT>的别称为PointCloud，涉及模板参数PointT因此使用typename关键字
      typedef typename pcl::PointCloud<PointT> PointCloud;
      typedef typename pcl::PointCloud<PointT>::ConstPtr PointCloudConstPtr;
      typedef typename pcl::PointCloud<PointT>::Ptr PointCloudPtr;
      typedef typename pcl::search::Search<PointT>::Ptr SearchPtr;

      //typedef定义boost::shared_ptr<SampleConsensusModel>的别称为Ptr，不涉及模板参数，因此省略typename
      typedef boost::shared_ptr<SampleConsensusModel> Ptr;
      typedef boost::shared_ptr<const SampleConsensusModel> ConstPtr;

      //...
}
```