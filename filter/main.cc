#include"bmp.h"
#include <iostream>

using namespace std;

int main()
{
    hkl::BMP controller;
    int x,y;

    controller.LoadBmp("boats.bmp");

    //controller.ShowHeaders();
    //controller.DebugBlackDotSave("test.bmp",false, 42);
    //controller.SaveBmp("result.bmp", &hkl::BMP::histogramEQ);
    
    
    cout<<"input filter 'x' size :";
    cin>>x;
    cout<<"input filter 'y' size :";
    cin>>y;

    controller.ConvolutionFilter("result.bmp",y,x);
    controller.makeCZP();
    //controller.GarbageCollection();
    return 0;
}
