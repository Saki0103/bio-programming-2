#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    //strandom((unsigned)time(NULL));
    const int loop = 1024, n = 1024;
    float a[n][n], b[n], c[n];

    for(int i = 0; i < n; i++){
        b[i] = (float)rand() / RAND_MAX;
        c[i] = 0.0;

        for(int j = 0; j<n; j++){
            a[i][j] = (float)rand() / RAND_MAX;
        }
    }

    clock_t start = clock();

    for(int l = 0; l < loop; l++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                c[i] += a[i][j] * b[j];
            }
        }
    }
    clock_t end = clock();
    printf("Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}