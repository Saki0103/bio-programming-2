#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void f1(vector<int> data){
    return;
}

void f2(const vector<int>& data){
    return;
}

int main(void){
    int vector_size = 1e7;
    vector<int> temp_vector(vector_size,0);

    clock_t start = clock();
    f1(temp_vector);
    clock_t end = clock();
    cout << "time:" << (double)(end - start) / CLOCKS_PER_SEC << endl;

    start = clock();
    f2(temp_vector);
    end = clock();
    cout << "time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}