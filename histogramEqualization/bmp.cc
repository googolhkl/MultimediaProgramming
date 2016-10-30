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
        int i;

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
        printf("읽어들인 사이즈 : %d\n",fread(*pImage, 1, (*BMIH)->biSizeImage, fp));
        printf("%d\n", (*pImage)[0]);
        

        /*
        printf("------------------------------\n");
        printf("bfType= %c\n", (*BMFH)->bfType);
        printf("bfSize= %d\n", (*BMFH)->bfSize);
        printf("bfReserved1= %d\n", (*BMFH)->bfReserved1);
        printf("bfReserved2= %d\n", (*BMFH)->bfReserved2);
        printf("bfOffBits= %d\n\n", (*BMFH)->bfOffBits);

        printf("biSize= %d\n", (*BMIH)->biSize);
        printf("biWidth= %d\n", (*BMIH)->biWidth);
        printf("biHeight= %d\n", (*BMIH)->biHeight);
        printf("biPlanes= %d\n", (*BMIH)->biPlanes);
        printf("biBitCount= %d\n", (*BMIH)->biBitCount);
        printf("biCompression= %d\n", (*BMIH)->biCompression);
        printf("biSizeImage= %d\n", (*BMIH)->biSizeImage);
        printf("biXPelsPerMeter= %d\n", (*BMIH)->biXPelsPerMeter);
        printf("biYPelsPerMeter= %d\n", (*BMIH)->biYPelsPerMeter);
        printf("biClrUsed= %d\n", (*BMIH)->biClrUsed);
        printf("biClrImportant= %d\n", (*BMIH)->biClrImportant);
        printf("------------------------------\n");

        for(i = 0; i <256; i++)
        {
            printf("red=%d, green=%d, blue=%d\n",(*rgbPal)[i].rgbRed, (*rgbPal)[i].rgbGreen, (*rgbPal)[i].rgbBlue);
        }
        */


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


        printf("------------------------------\n");
        printf("bfType= %c\n", file_h.bfType);
        printf("bfSize= %d\n", file_h.bfSize);
        printf("bfReserved1= %d\n", file_h.bfReserved1);
        printf("bfReserved2= %d\n", file_h.bfReserved2);
        printf("bfOffBits= %d\n\n", file_h.bfOffBits);

        printf("biSize= %d\n", info_h.biSize);
        printf("biWidth= %d\n", info_h.biWidth);
        printf("biHeight= %d\n", info_h.biHeight);
        printf("biPlanes= %d\n", info_h.biPlanes);
        printf("biBitCount= %d\n", info_h.biBitCount);
        printf("biCompression= %d\n", info_h.biCompression);
        printf("biSizeImage= %d\n", info_h.biSizeImage);
        printf("biXPelsPerMeter= %d\n", info_h.biXPelsPerMeter);
        printf("biYPelsPerMeter= %d\n", info_h.biYPelsPerMeter);
        printf("biClrUsed= %d\n", info_h.biClrUsed);
        printf("biClrImportant= %d\n", info_h.biClrImportant);
        printf("------------------------------\n");

        for(i = 0; i <256; i++)
        {
            printf("red=%d, green=%d, blue=%d\n",(rgbPal)[i].rgbRed, (rgbPal)[i].rgbGreen, (rgbPal)[i].rgbBlue);
        }
        

        /*
        for(i = 0; i <256; i++)
        {
            printf("red=%d, green=%d, blue=%d\n",rgbPal[i].rgbRed, rgbPal[i].rgbGreen, rgbPal[i].rgbBlue);
        }
        */
        i = 0;
        for(i=0; i< info_h.biSizeImage; i++)
        {
            printf("%d\n", pImage[i++]);
        }
        printf("i = %d\n", i);
        printf("rgbPal = %d\n", sizeof(rgbPal));
        printf("RGBQUA = %d\n", sizeof(RGBQUAD));
        

        fwrite((char*)&file_h, 1, sizeof(BITMAPFILEHEADER), fp);
        fwrite((char*)&info_h, 1, sizeof(BITMAPINFOHEADER), fp);
        fwrite((char*)rgbPal, 1, sizeof(RGBQUAD)*256, fp);
        fwrite(pImage, 1, info_h.biSizeImage, fp);

        fclose(fp);
        return true;
    }
}// hkl
