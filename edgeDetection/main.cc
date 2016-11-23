#include"bmp.h"
#include <iostream>

using namespace std;

int main()
{
    hkl::BMP controller;
    int filterSize;

    controller.LoadBmp("input.bmp");
    //controller.ShowHeaders();
    //controller.DebugBlackDotSave("test.bmp",false, 42);
    //controller.SaveBmp("result.bmp", &hkl::BMP::histogramEQ);

    controller.EdgeDetection("result.bmp");

    //controller.GarbageCollection();
    return 0;
}
