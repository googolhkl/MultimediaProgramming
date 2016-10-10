#include "multimediaProgramming.h"

namespace hkl
{
    RawToBMP::RawToBMP(){}
    RawToBMP::~RawToBMP(){}

    DWORD RawToBMP::getnWidth(){ return this->nWidth; }
    DWORD RawToBMP::getnHeight(){ return this->nHeight; }

    bool RawToBMP::WriteFileInfo()
    {
        std::cout<<"RAW File Name : ";
        std::cin>>szRawName;

        std::cout<<"BMP File Name : ";
        std::cin>>szBmpName;

        std::cout<<"Raw Width : ";
        std::cin>>nWidth;
        
        std::cout<<"Raw Height : ";
        std::cin>>nHeight;

        return true;
    }

    bool RawToBMP::ConvertGray(DWORD nWidth, DWORD nHeight)
    {
        BITMAPFILEHEADER file_h;
        BITMAPINFOHEADER info_h;
        DWORD            dwBmpSize = 0;
        DWORD            dwRawSize = 0;
        DWORD            dwLine = 0;
        long             lCount, i;
        FILE             *in, *out;
        char             *pData = NULL;
        RGBQUAD          rgbPal[256];

        in = fopen(szRawName, "rb");
        if(in == NULL)
        {   
            printf("File Open Error1!\n");
            return false;
        }

        out = fopen(szBmpName, "wb");
        if(out == NULL)
        {
            printf("File Open Error2!\n");
            return false;
        }

        // BMP 파일 헤더
        file_h.bfType   =   0x4D42;     // 매직 넘버(BM)
        file_h.bfReserved1 = 0;         // 준비
        file_h.bfReserved2 = 0;         // 준비
        file_h.bfOffBits = sizeof(rgbPal) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);    // 비트맵 데이터의 시작 위치

        // 비트맵 정보(DIB 헤더)
        info_h.biSize           =   sizeof(BITMAPINFOHEADER);   // 이 헤더의 크기
        info_h.biWidth          =   (DWORD)nWidth;              // 비트맵 가로
        info_h.biHeight         =   (DWORD)nHeight;             // 비트맵 세로
        info_h.biPlanes         =   1;                          // 사용하는 color plane의 수
        info_h.biBitCount       =   8;                          // 한 화소에 들어가는 비트 수(흑백), RGBQUAD사용 됨
        info_h.biCompression    =   BT_RGB;                     // 압축 방식
        info_h.biXPelsPerMeter  =   0;                          // 그림의 가로 해상도
        info_h.biYPelsPerMeter  =   0;                          // 그림의 세로 해상도
        info_h.biClrUsed        =   0;                          // 색 팔레트의 색 수(흑백)
        info_h.biClrImportant   =   0;                          // 중요한 색의 수. 모든 색이 중요할 경우 0

        /* 그림 크기 계산 */
        dwLine =   ((((info_h.biWidth * info_h.biBitCount) + 31) &~ 31) >> 3);  // 256 (비트에 따른 한줄의 크기를 알기 위한 것)
        dwBmpSize = dwLine * info_h.biHeight;                                   // 65536
        info_h.biSizeImage =   dwBmpSize;                                       // DIB 헤더에 있는 그림 크기 : 65536
        file_h.bfSize =   dwBmpSize + file_h.bfOffBits + 2;                     // BMP 파일 크기

        dwRawSize =   info_h.biWidth * info_h.biHeight;                         // 65536

        pData = new char[dwRawSize+16];

        if(pData)
        {
            fread(pData, 1, dwRawSize, in);     // in 파일에서 1바이트씩 dwRawSize만큼 읽어서 pData에 저장

            /*  0~255까지 동일한 값을 채움(흑백)  */
            for(i = 0; i < 256; i++)
            {
                rgbPal[i].rgbRed = (BYTE)(i%256);
                rgbPal[i].rgbGreen = rgbPal[i].rgbRed;
                rgbPal[i].rgbBlue = rgbPal[i].rgbRed;
                rgbPal[i].rgbReserved = 0;
            }

            /*  out 파일에 BMP 파일 붙이기  */
            fwrite((char *)&file_h, 1, sizeof(BITMAPFILEHEADER), out);  // out 파일에 file_h 구조체를 1바이트씩 BITMAPFILEHEADER의 크기만큼 쓴다.
            fwrite((char *)&info_h, 1, sizeof(BITMAPINFOHEADER), out);  // out 파일에 info_h 구조체를 1바이트씩 BITMAPINFOHEADER의 크기만큼 쓴다.
            fwrite((char *)rgbPal, 1, sizeof(rgbPal), out);             // out 파일에 rgbPal구조체를 1바이트씩 rgbPal의 크기만큼 쓴다.
            lCount = dwRawSize;

            /*  out 파일에 한줄씩 거꾸로 채워 넣는다.   */
            for(lCount -= (long)info_h.biWidth; lCount >= 0; lCount -= (long)info_h.biWidth)
            {
                fwrite((pData + lCount), 1, (long)dwLine, out);
            }

            delete[] pData;
        }

        // 파일 닫기
        fclose(in);
        fclose(out);
        return true;
    }

}// hkl
