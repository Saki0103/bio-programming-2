#include "image.hpp"
#include <iostream>
#include <math.h>

using namespace std;
typedef unsigned char uchar;

int main(void){
    Image sample("sample.png");
    Image gray_img(sample.w, sample.h, 3);

    for(int y = 0; y < sample.h; y++){
        for(int x = 0; x < sample.w; x++){
            uchar r = sample.GetPixel(y, x, 0);
            uchar g = sample.GetPixel(y, x, 1);
            uchar b = sample.GetPixel(y, x, 2);
            uchar gray = (r+g+b)/3;
            for(int c = 0; c < 3; c++){
                gray_img.SetPixel(y, x, c, gray);
            }
        }
    }
    gray_img.save("gray.png");

    int histogram[256] = {0};

    for(int y = 0; y < gray_img.h; y++){
        for(int x = 0; x < gray_img.w; x++){
            uchar gray = gray_img.GetPixel(y, x, 0);
            histogram[gray]++;
        }
    }

    int black[256] = {0};
    int white[256] = {0};
    int black_count[256] = {0};
    int white_count[256] = {0};
    double black_average[256] = {0.0};
    double white_average[256] = {0.0};
    double whole_average = 0.0;
    double spread[256] = {0.0};
    int max_t;

    for(int i = 0; i < 256; i++){
       for(int j = 0; j <= i; j++){
           black[i] += j*histogram[j];
           black_count[i] += histogram[j];
        }
        if(black_count[i] != 0){
            black_average[i] = (double)black[i]/black_count[i];
        }
       for(int j = i+1; j < 256; j++){
           white[i] += j*histogram[j];
           white_count[i] += histogram[j];
        }
        if(white_count[i] != 0){
            white_average[i] = (double)white[i]/white_count[i];
        }
        whole_average = (double)(black[i]+white[i])/(black_count[i]+white_count[i]);

        spread[i] = (double)((black_count[i]*(black_average[i]-whole_average)*(black_average[i]-whole_average))+(white_count[i]*(white_average[i]-whole_average)*(white_average[i]-whole_average)))/(black_count[i]+white_count[i]);

        if(i == 0){
            max_t = i;
        }else if(spread[i] > spread[max_t]){
            max_t = i;
        }
    }
    cout << "闘値：" << max_t << endl;

    return 0;
}