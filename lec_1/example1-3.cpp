#include <stdio.h>
#include <iostream>
using namespace std;

class Matrix{
public:
    double a,b,c,d;
    Matrix(){}
    Matrix(double x, double y, double z, double w){
        a = x; b = y;
        c = z; d = w;
    }

    Matrix operator + (const Matrix &q) const{
        Matrix m;
        m.a = a + q.a;
        m.b = b + q.b;
        m.c = c + q.c;
        m.d = d + q.d;
        return(m);
    }

    Matrix operator * (const Matrix &q) const{
        Matrix m;
        m.a = a * q.a + b * q.c;
        m.b = a * q.b + b * q.d;
        m.c = c * q.a + d * q.c;
        m.d = c * q.b + d * q.d;
        return(m);
    }

    double trace() const{
        return a + d;
    }

    Matrix inverse() const{
        Matrix m;
        double det = a * d - b * c;
        m.a = d / det;
        m.b = -b / det;
        m.c = -c / det;
        m.d = a / det;
        return(m);
    }

    bool operator==(const Matrix &q) const{
        return (a == q.a && b == q.b && c == q.c && d == q.d);
    }
};

int main(void){
    const Matrix p(3.23, 1.24, 5.13, 1.34);
    const Matrix q(2.22, 4.21, 3.75, 2.18);
    const Matrix r(2.22, 4.21, 3.75, 2.18);

    cout <<"p+qの計算結果: "<< endl;
    cout <<(p+q).a<<" "<<(p+q).b<<endl;
    cout <<(p+q).c<<" "<<(p+q).d<<endl;

    cout <<"p*qの計算結果: "<< endl;
    cout <<(p*q).a<<" "<<(p*q).b<<endl;
    cout <<(p*q).c<<" "<<(p*q).d<<endl;

    cout <<"pのトレース: "<<p.trace()<< endl;
    cout <<"qのトレース: "<<q.trace()<< endl;

    cout <<"pの逆行列: "<<endl;
    cout <<p.inverse().a<<" "<<p.inverse().b<<endl;
    cout <<p.inverse().c<<" "<<p.inverse().d<<endl;
    cout <<"qの逆行列: "<<endl;
    cout <<q.inverse().a<<" "<<q.inverse().b<<endl;
    cout <<q.inverse().c<<" "<<q.inverse().d<<endl;

    if(p==q){
        cout <<"p==q: true"<<endl;
    }else{
        cout <<"p==q: false"<<endl;
    }
    if(r==q){
        cout <<"r==q: true"<<endl;
    }else{
        cout <<"r==q: false"<<endl;
    }

    return 0;
}