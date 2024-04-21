#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double num1=3.14159;
    double num2=3.14158;
    double epsion=0.00001;
    if(num1-num2==epsion){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;  // 输出这个
    }

    const double alpha =1e-3;
    if(fabs(num1-num2)<alpha){
        cout<<"Yes";
    }else{
        cout<<"NO";
    }
    system("pause");
    return 0;
}
