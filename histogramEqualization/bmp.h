#ifndef __BMP_H__
#define __BMP_H__

#include<cstdio>
#include<cstdlib>
#include<iostream>

typedef unsigned short WORD;    // 2byte
typedef unsigned int   DWORD;   // 4byte
typedef unsigned int   LONG;    // 4byte
typedef unsigned char  BYTE;    // 1byte

#ifndef BI_RGB
#define BI_RGB  0
#endif

#define LOG(_str_) std::cout<<_str_<<std::endl

namespace hkl
{
class BMP 
{
    public:
        // BMP 파일 헤더
        typedef struct tagBITMAPFILEHEADER
        {
            WORD    bfType;         // 매직 넘버
            DWORD   bfSize;         // BMP 파일 크기
            WORD    bfReserved1;    // 준비
            WORD    bfReserved2;    // 준비
            DWORD   bfOffBits;      // 비트맵 데이터의 시작 위치
        } __attribute__((packed)) BITMAPFILEHEADER;

        // 비트맵 정보(DIB헤더)
        typedef struct tagBITMAPINFOHEADER
        {
            DWORD   biSize;         // 이 헤더의 크기
            LONG    biWidth;        // 비트맵 가로
            LONG    biHeight;       // 비트맵 세로
            WORD    biPlanes;       // 사용하는 color plane의 수
            WORD    biBitCount;     // 한 화소에 들어가는 비트 수
            DWORD   biCompression;  // 압축 방식
            DWORD   biSizeImage;    // 그림 크기
            LONG    biXPelsPerMeter;// 그림의 가로 해상도
            LONG    biYPelsPerMeter;// 그림의 세로 해상도
            DWORD   biClrUsed;      // 색 팔레트의 색 수
            DWORD   biClrImportant; // 중요한 색의 수. 모든 색이 중요할 경우 0
        } __attribute__((packed)) BITMAPINFOHEADER;

        // 팔레트 정보
        typedef struct tagRGBQUAD
        {
            BYTE rgbBlue;
            BYTE rgbGreen;
            BYTE rgbRed;
            BYTE rgbReserved;
        } __attribute__((packed)) RGBQUAD;

        char szRawName[80];
        char szBmpName[80];
        DWORD nWidth, nHeight;

        BMP();
        ~BMP();
        DWORD getnWidth();
        DWORD getnHeight();
        bool LoadBmp(const char* filename);
        bool SaveBmp(const char* filename);
        BYTE DebugBlackDot(int px, int number);
        BYTE DebugWhiteDot(int px, int number);
        bool GarbageCollection();

    private:
        BYTE* image;
        BITMAPFILEHEADER* file_h;
        BITMAPINFOHEADER* info_h;
        RGBQUAD* rgbPal;
}; //BMP
}  //hkl

#endif
