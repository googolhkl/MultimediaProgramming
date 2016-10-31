#include "bmp.h"
#include <iostream>
#include <cstdio>

namespace hkl
{
    BMP::BMP(){}
    BMP::~BMP(){}

    DWORD BMP::getnWidth(){ return this->nWidth; }
    DWORD BMP::getnHeight(){ return this->nHeight; }

    bool BMP::LoadBmp(const char* filename, BYTE** pImage, BITMAPFILEHEADER** BMFH, BITMAPINFOHEADER** BMIH, RGBQUAD** rgbPal)
    {
        FILE* fp;
        int readSize=0;

        *BMFH = new BITMAPFILEHEADER;
        *BMIH = new BITMAPINFOHEADER;
        *rgbPal = new RGBQUAD[256];

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

        fread(*BMFH, sizeof(BITMAPFILEHEADER), 1, fp);
        if( (*BMFH)->bfType != 0x4d42)
        {
            fclose(fp);
            LOG("BMP 파일이 아닙니다...");
            return false;
        }
        else
        {
            LOG("BMP 파일 확인 완료...");
        }

        fread(*BMIH, sizeof(BITMAPINFOHEADER), 1, fp);
        if((*BMIH)->biBitCount != 8 || (*BMIH)->biCompression != BI_RGB)
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

        fread(*rgbPal, sizeof(RGBQUAD)*256, 1, fp);

        LONG Width = (*BMIH)->biWidth;  //512
        LONG Height = (*BMIH)->biHeight;    //512
        DWORD dwLine = ((((Width * (*BMIH)->biBitCount) + 31) &~31) >>3);   //512
        DWORD size = (*BMFH)->bfSize;   // 263222
        DWORD dwRawSize = (*BMIH)->biWidth * (*BMIH)->biHeight; //262144

        *pImage = new BYTE[(*BMIH)->biSizeImage];
        //*pImage += dwLine * Height;
        readSize = fread(*pImage, 1, (*BMIH)->biSizeImage, fp);
        std::cout<<"읽어들인 이미지 크기 "<<readSize<<"..."<<std::endl;
        
        fclose(fp);
        return true;
    }

    bool BMP::SaveBmp(const char* filename, BYTE* pImage, BITMAPFILEHEADER file_h, BITMAPINFOHEADER info_h, RGBQUAD* rgbPal)
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
        for(i=0; i< info_h.biSizeImage; i++)
        {
            printf("%d\n", pImage[i++]);
        }

        fwrite((char*)&file_h, 1, sizeof(BITMAPFILEHEADER), fp);
        fwrite((char*)&info_h, 1, sizeof(BITMAPINFOHEADER), fp);
        fwrite((char*)rgbPal, 1, sizeof(RGBQUAD)*256, fp);
        fwrite(pImage, 1, info_h.biSizeImage, fp);

        fclose(fp);
        return true;
    }
}// hkl
