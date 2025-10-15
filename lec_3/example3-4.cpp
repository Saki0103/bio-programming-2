#include <iostream>
#include <math.h>
using namespace std;

int main(void){
    double x1 = 0;
    double x2 = 2;

    double allowable_error = 1e-12;
    double error = 1;
    int count = 0;
    while(error>allowable_error){
        double xn = x2 - (exp(x2) + x2 - 5)*(x2-x1)/(exp(x2) +x2 - exp(x1) -x1);
        if(xn>x2){
            error = xn - x2;
        }else{
            error = x2 - xn;
        }
        x1 = x2;
        x2 = xn;
        count++;
        if(error<allowable_error){
            cout << "x = " << x2 << endl;
            cout << "count = " << count << endl;
        }
    }

    return 0;
}
