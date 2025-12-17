#include "image.hpp"
#include <iostream>

using namespace std;
typedef unsigned char uchar;

int main(void){
    Image sample("stap.png");
    Image gray_img(sample.w, sample.h, 3);
    Image equalized_img(sample.w, sample.h, 3);

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
    gray_img.save("stap_gray.png");

    int histogram[256] = {0};

    for(int y = 0; y < gray_img.h; y++){
        for(int x = 0; x < gray_img.w; x++){
            uchar gray = gray_img.GetPixel(y, x, 0);
            histogram[gray]++;
        }
    }

    double cdf[256] = {0.0};

    for(int i = 0; i < 256; i++){
        if(i==0){
            cdf[i] = (double)histogram[i]/(gray_img.w*gray_img.h);
        }else{
            cdf[i] = cdf[i-1] + (double)histogram[i]/(gray_img.w*gray_img.h);
        }
        for(int y = 0; y < sample.h; y++){
            for(int x = 0; x < sample.w; x++){
                if(gray_img.GetPixel(y, x, 0) == i){
                    for(int c = 0; c < 3; c++){
                        equalized_img.SetPixel(y, x, c, (uchar)(cdf[i]*255));
                    }
                }
            }
        }
        
    }

    equalized_img.save("stap_equalized.png");

    return 0;
}