#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

int main(void){
    const int N = 10e7;
    vector<double> a(N, 1.0);
    //シャッフル用のインデックス
    vector<int> indices(N);
    for(int i = 0; i < N; i++){
        indices[i] = i;
    }
    mt19937 rng(0);
    shuffle(indices.begin(), indices.end(), rng);//indicesをシャッフル

    double sum1 = 0; clock_t start = clock();
    for(size_t i = 0; i < N; i++){
        sum1 += a[i];
    }
    clock_t end = clock();
    cout << sum1 <<" " <<(double)(end-start)/CLOCKS_PER_SEC << "s" << endl;
    
    double sum2 = 0; start = clock();
    for(size_t i = 0; i < N; i++){
        sum2 += a[indices[i]];
    }
    end = clock();
    cout << sum2 <<" " <<(double)(end-start)/CLOCKS_PER_SEC << "s" << endl;
    
    return 0;
}