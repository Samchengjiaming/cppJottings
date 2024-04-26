#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    for(int i=0;i<10;i++){
        srand(i);
        std::cout<<rand()<<std::endl;  //输出的随机数是一样的
    }
    
    system("pause");
    return 0;
}
