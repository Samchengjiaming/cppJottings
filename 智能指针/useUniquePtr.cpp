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
    std::unique_ptr<Man> manPtr(new Man(25 ,"cjm"));//创建一个Man类的独占指针
    int cjmAge=manPtr->getAge(); //访问成员
    // std::unique_ptr<Man> manPtr1= manPtr;//不能直接复制 无法通过编译

    std::unique_ptr<Man> manPtrMove =std::move(manPtr);
    if(manPtrMove!=nullptr){
        std::cout<<"manPtrMove not null and its name is "<<manPtrMove->name_.c_str()<<std::endl;
        // std::cout<<manPtrMove->getName()<<std::endl;
    }
    if(manPtr == nullptr){
        std::cout<<"manPtr is null now!"<<std::endl;
    }
    std::cout<<cjmAge<<std::endl;
    system("pause");
    return 0;
}   
