#include <iostream>
#include <math.h>
using namespace std;

int main(void){
    double x = 0;
    double y = -0.1;

    double allowable_error = 1e-12;
    double error = 1;
    int count = 0;
    while(error>allowable_error){
        double x_n = x - (exp(x) + x - 5)/(exp(x) + 1);
        if(x_n>x){
            error = x_n - x;
        }else{
            error = x - x_n;
        }
        x = x_n;
        count++;
        if(error<allowable_error){
            cout << "x = " << x << endl;
            cout << "count = " << count << endl;
        }
    }

    error = 1;
    count = 0;

    while(error>allowable_error){
        double y_nn = (2/3)*(cbrt(cbrt(y)));
        double y_n = y_nn*y_nn*y_nn*y_nn*y_nn*y_nn*y_nn*y_nn*y_nn;
        if(y_n>x){
            error = y_n - y;
        }else{
            error = y - y_n;
        }
        y = y_n;
        count++;
        if(error<allowable_error){
            cout << "y = " << y << endl;
            cout << "count = " << count << endl;
        }
    }

    return 0;

}