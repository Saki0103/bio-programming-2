#include <iostream>
#include <math.h>
using namespace std;

int main(void){
    float a = 1;
    float b = 10000;
    float c = 1;

    if(b>0){
        float result1 = (-1)*(2*c)/(b+sqrt(b*b+(-1)*4*a*c));
        float result2 = (-1)*(b+sqrt(b*b+(-1)*4*a*c))/(2*a);
        cout << "result: " << result1 << "," << result2 <<endl;
    }else{
        float result1 = ((-1)*b+sqrt(b*b+(-1)*4*a*c))/(2*a);
        float result2 = (2*c)/((-1)*b+sqrt(b*b+(-1)*4*a*c));
        cout << "result: " << result1 << "," << result2 <<endl;
    }

    return 0;
}