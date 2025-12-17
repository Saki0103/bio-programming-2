#include "image.hpp"

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

    return 0;
}