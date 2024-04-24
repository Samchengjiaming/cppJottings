#include <iostream>
#include <cmath>

double  Div(int a,int b){
    if(b==0){
        throw "b is 0";
    }else{
        return a/b;
    }
}

void fun(){
    int* a=new int[10];
    int* b=new int[10];
    
    double c= Div(1,0); //抛出异常 跳出fun a,b指针未释放

    delete[] a;
    delete[] b;
}

int main()
{
    fun(); 
    std::cout<<"over"<<std::endl;
    system("pause");
    return 0;
}
