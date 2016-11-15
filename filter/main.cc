#include"bmp.h"
#include <iostream>

using namespace std;

int main()
{
    hkl::BMP controller;

    controller.LoadBmp("boats.bmp");
    //controller.ShowHeaders();
    //controller.DebugBlackDotSave("test.bmp",false, 42);
    //controller.SaveBmp("result.bmp", &hkl::BMP::histogramEQ);
    controller.ConvolutionFilter("result.bmp",3,3);
    controller.GarbageCollection();
    return 0;
}
