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
    //double ** p1 = controller.makeFilter(3,3);
    //double ** p2 = controller.makeTempFilter(0,0);
    //controller.calcFilter(p1,p2);
    //controller.SaveBmp("result.bmp", &hkl::BMP::ConvolutionFilter);
    controller.ConvolutionFilter("result.bmp");
    controller.GarbageCollection();
    return 0;
}
