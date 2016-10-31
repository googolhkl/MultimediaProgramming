#include"bmp.h"
#include <iostream>

using namespace std;

int main()
{
    hkl::BMP controller;

    controller.LoadBmp("map.bmp");
    //controller.ShowHeaders();
    //controller.SaveBmp("result.bmp");
    controller.SaveBmp("result.bmp", &hkl::BMP::histogramEQ);
    controller.GarbageCollection();
    return 0;
}
