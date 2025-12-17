#ifndef IMAGE_H
#define IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include <iostream>
#include <vector>
#include <string>

class Image{
    public:
    int w, h, ch;
    std::vector<unsigned char> data; // w * h * ch;

    // 画像の読み込み
    explicit Image(const std::string& path){
        unsigned char* tmp = stbi_load(path.c_str(), &w, &h, &ch, 0);
        if(!tmp){
            std::cout  << "Failure: image file lod error" << std::endl;
            exit(1);
        }
        data.assign(tmp, tmp + w * h * ch);
        stbi_image_free(tmp);
    }

    // 画像のサイズ規定
    Image(int _w, int _h, int _ch){
        w = _w; h = _h; ch = _ch;
        data.resize(w*h*ch);    
    }

    //画像の書き出し
    void save(const std::string& path){
        stbi_write_png(path.c_str(), w, h, ch, data.data(), w * ch);
    }

    unsigned char GetPixel(int y, int x, int c) const{
        return data[(y * w + x) * ch + c];
    }
    void SetPixel(int y, int x, int c, unsigned char v){
        data[(y * w + x) * ch + c] = v;
    }
};

#endif
