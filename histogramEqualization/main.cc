#include"bmp.h"
#include <iostream>

using namespace std;

int main()
{
    hkl::BMP controller;

    controller.LoadBmp("map.bmp");
    controller.SaveBmp("result.bmp", &hkl::BMP::func);
    controller.GarbageCollection();

    return 0;
}
