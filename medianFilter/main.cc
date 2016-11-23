#include"bmp.h"
#include <iostream>

using namespace std;

int main()
{
    hkl::BMP controller;
    int filterSize;

    controller.LoadBmp("akiyo_noise.bmp");
    //controller.ShowHeaders();
    //controller.DebugBlackDotSave("test.bmp",false, 42);
    //controller.SaveBmp("result.bmp", &hkl::BMP::histogramEQ);
    //
    cout<<"Please enter the filter size:";
    cin>>filterSize;
    if(filterSize%2 ==0)
    {
        cout<<"Please enter only odd numbers"<<endl;
        return -1;
    }

    controller.MedianFilter("result.bmp",filterSize,filterSize);

    //controller.GarbageCollection();
    return 0;
}
