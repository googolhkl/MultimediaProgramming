#include "bmp.h"
#include <iostream>
#include <cstdio>

namespace hkl
{
    BMP::BMP(){}
    BMP::~BMP(){}

    DWORD BMP::getnWidth(){ return this->nWidth; }
    DWORD BMP::getnHeight(){ return this->nHeight; }


    bool BMP::LoadBmp(const char* filename)
    {
        FILE* fp;
        int readSize=0;

        file_h = new BITMAPFILEHEADER;
        info_h = new BITMAPINFOHEADER;
        rgbPal = new RGBQUAD[256];

        fp = fopen(filename, "rb");
        if(fp == nullptr)
        {
            LOG("파일오픈 실패...");
            return false;
        }
        else
        {
            LOG("파일 오픈 성공...");
        }

        fread(file_h, sizeof(BITMAPFILEHEADER), 1, fp);
        if( (file_h)->bfType != 0x4d42)
        {
            fclose(fp);
            LOG("BMP 파일이 아닙니다...");
            return false;
        }
        else
        {
            LOG("BMP 파일 확인 완료...");
        }

        fread(info_h, sizeof(BITMAPINFOHEADER), 1, fp);
        if((info_h)->biBitCount != 8 || (info_h)->biCompression != BI_RGB)
        {
            fclose(fp);
            LOG("8비트가 아니거나 압축된 파일이 아닙니다...");
            return false;
        }
        else
        {
            LOG("8비트 파일 확인 완료...");
            LOG("압축된 파일 확인 완료...");
        }

        fread(rgbPal, sizeof(RGBQUAD)*256, 1, fp);

        LONG Width = (info_h)->biWidth;  //512
        LONG Height = (info_h)->biHeight;    //512
        DWORD dwLine = ((((Width * (info_h)->biBitCount) + 31) &~31) >>3);   //512
        DWORD size = (file_h)->bfSize;   // 263222
        DWORD dwRawSize = (info_h)->biWidth * (info_h)->biHeight; //262144

        image = new BYTE[(info_h)->biSizeImage];
        //*pImage += dwLine * Height;
        readSize = fread(image, 1, (info_h)->biSizeImage, fp);
        std::cout<<"읽어들인 이미지 크기 "<<readSize<<"..."<<std::endl;
        
        fclose(fp);
        return true;
    }

    bool BMP::SaveBmp(const char* filename)
    {
        int i;

        FILE* fp = nullptr;
        fp = fopen(filename, "wb");
        if(fp == nullptr)
        {
            LOG("파일 오픈 실패...");
            return false;
        }
        else
        {
            LOG("파일 오픈 성공...");
        }
        
        /*  이미지 파일 수정할 코드 작성 */
        for(i=0; i< info_h->biSizeImage; i++)
        {
            //image[i] = DebugWhiteDot(image[i], 42);
            image[i] = SubClipped(image[i], 20);
            
        }

        fwrite((char*)file_h, 1, sizeof(BITMAPFILEHEADER), fp);
        fwrite((char*)info_h, 1, sizeof(BITMAPINFOHEADER), fp);
        fwrite((char*)rgbPal, 1, sizeof(RGBQUAD)*256, fp);
        fwrite(image, 1, info_h->biSizeImage, fp);

        fclose(fp);
        return true;
    }

    BYTE BMP::DebugBlackDot(int px, int number)
    {
        if(px == number)
        {
            return 0;
        }
        else
        {
            return (BYTE)px;
        }
    }

    BYTE BMP::DebugWhiteDot(int px, int number)
    {
        if(px == number)
        {
            return 255;
        }
        else
        {
            return (BYTE)px;
        }
    }

    bool BMP::GarbageCollection()
    {
        LOG("collection!");
        delete[] image;
        delete[] file_h;
        delete[] info_h;
        delete[] rgbPal;
        return true;
    }

    BYTE BMP::AddClipped(int px, int number)
    {
        px += number;
        if(px > MAX_RGB)
        {
            px = MAX_RGB;
        }
        return (BYTE)px;
    }

    BYTE BMP::SubClipped(int px, int number)
    {
        px -= number;
        if(px < MIN_RGB)
        {
            px = MIN_RGB;
        }
        return (BYTE)px;
    }
}// hkl
