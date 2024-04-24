#include <iostream>
#include <cmath>
#include <memory>
using namespace std;

class Man
{
private:
    int age_;

public:
    Man(int,std::string);
    ~Man();
    std::string name_;
    int getAge();
    std::string getName();
};

Man::Man(int age,std::string name)
    :age_(age),name_(name)
{
}
std::string Man::getName(){
    return name_;
}
int Man::getAge(){
    return age_;
}

Man::~Man()
{
}

int main()
{
    std::shared_ptr<Man> manPtr (new Man(25,"demo")); //创建一个共享指针
    std::cout<<manPtr.use_count()<<std::endl; //计数 1
    std::cout<<manPtr->getName().c_str()<<std::endl;

    std::shared_ptr<Man> manPtr1=manPtr; //直接复制
    std::cout<<manPtr1.use_count()<<std::endl; //计数 2

    manPtr->name_="ABC";
    std::cout<<manPtr1->getName().c_str()<<std::endl; // ABC

    //创建一个空的sharedpointer 
    std::shared_ptr<Man> manPtr2;
    manPtr2=manPtr1;
    std::cout<<manPtr1.use_count()<<std::endl; //计数 3

    system("pause");
    return 0;
}
