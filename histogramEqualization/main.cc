#include"bmp.h"
#include <iostream>

int main()
{
    hkl::BMP controller;
    BYTE* image;
    controller.LoadBmp("map.bmp", &image);

    return 0;
}
