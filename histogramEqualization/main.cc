#include"bmp.h"
#include <iostream>

using namespace std;

int main()
{
    hkl::BMP controller;
    /*
    BYTE* image;
    hkl::BMP::BITMAPFILEHEADER* file_h;
    hkl::BMP::BITMAPINFOHEADER* info_h;
    hkl::BMP::RGBQUAD* rgbPal;

    controller.LoadBmp("map.bmp", &image, &file_h, &info_h, &rgbPal);
    controller.SaveBmp("result.bmp",image,*file_h,*info_h, rgbPal);

    delete[] file_h;
    delete[] info_h;
    delete[] rgbPal;
    */

    controller.LoadBmp("map.bmp");
    controller.SaveBmp("result.bmp");
    controller.GarbageCollection();

    return 0;
}
