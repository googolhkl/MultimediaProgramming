#include "bmp.h"
#include <iostream>

namespace hkl
{
    BMP::BMP(){}
    BMP::~BMP(){}

    DWORD BMP::getnWidth(){ return this->nWidth; }
    DWORD BMP::getnHeight(){ return this->nHeight; }
    bool BMP::LoadBmp(char* filename, BYTE** pImage)
    {
        FILE* fp;

        BITMAPFILEHEADER BMFH;
        BITMAPINFOHEADER BMIH;

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

        fread(&BMFH, sizeof(BITMAPFILEHEADER), 1, fp);
        if( BMFH.bfType != 0x4d42)
        {
            fclose(fp);
            LOG("BMP 파일이 아닙니다...");
            return false;
        }
        else
        {
            LOG("BMP 파일 확인 완료...");
        }

        fread(&BMIH, sizeof(BITMAPINFOHEADER), 1, fp);
        if(BMIH.biBitCount != 8 || BMIH.biCompression != BI_RGB)
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

        LONG Width = BMIH.biWidth;  //512
        LONG Height = BMIH.biHeight;    //512
        DWORD dwLine = ((((Width * BMIH.biBitCount) + 31) &~31) >>3);   //512
        DWORD size = BMFH.bfSize;   // 263222

        *pImage = new BYTE[size];
        fread(*pImage, size, 1, fp);
        fclose(fp);

        return true;
    }
}// hkl
