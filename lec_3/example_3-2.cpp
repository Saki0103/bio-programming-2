#include <iostream>
#include <math.h>
using namespace std;

int main(void){
    double a1 = 0;
    double b1 = 2;
    double c1;

    double a2 = -0.1;
    double b2 = 0.2;
    double c2;

    double allowable_error = 1e-12;

    int count1 = 0;
    double error = b1-a1;
    while(error>allowable_error){
        c1 = (a1+b1)/2;
        double f1 = exp(c1) + c1 - 5;
        if(f1>0){
            b1 = c1;
        }else{
            a1 = c1;
        }
        error = b1-a1;
        count1++;
        if(error<allowable_error){
            cout << "count = " << count1 << endl;
        }
    }


    int count2 = 0;
    error = b2-a2;
    while(error>allowable_error){
        c2 = (a2+b2)/2;
        float f2 = cbrt(c2);
        if(f2>0){
            b2 = c2;
        }else{
            a2 = c2;
        }
        error = b2-a2;
        count2++;
        if(error<allowable_error){
            cout << "count = " << count2 << endl;
        }
    }

    return 0;
}