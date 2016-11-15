#include "bmp.h"
#include <iostream>
#include <cstdio>

namespace hkl
{
    BMP::BMP(){}
    BMP::~BMP(){}

    DWORD BMP::getnWidth(){ return this->nWidth; }
    DWORD BMP::getnHeight(){ return this->nHeight; }

    void BMP::ShowHeaders()
    {
        std::cout<<"-----Bitmap File Header-----"<<std::endl;
        std::cout<<"bfType :"<<file_h->bfType<<std::endl;
        std::cout<<"bfSize :"<<file_h->bfSize<<std::endl;
        std::cout<<"bfReserved1 :"<<file_h->bfReserved1<<std::endl;
        std::cout<<"bfReserved2 :"<<file_h->bfReserved2<<std::endl;
        std::cout<<"bfOffBits :"<<file_h->bfOffBits<<std::endl<<std::endl;

        std::cout<<"-----Bitmap Info Header-----"<<std::endl;
        std::cout<<"biSize :"<<info_h->biSize<<std::endl;
        std::cout<<"biWidth :"<<info_h->biWidth<<std::endl;
        std::cout<<"biHeight :"<<info_h->biHeight<<std::endl;
        std::cout<<"biPlanes :"<<info_h->biPlanes<<std::endl;
        std::cout<<"biBitCount :"<<info_h->biBitCount<<std::endl;
        std::cout<<"biCompression :"<<info_h->biCompression<<std::endl;
        std::cout<<"biSizeImage :"<<info_h->biSizeImage<<std::endl;
        std::cout<<"biXPelsPerMeter :"<<info_h->biXPelsPerMeter<<std::endl;
        std::cout<<"biYPelsPerMeter :"<<info_h->biYPelsPerMeter<<std::endl;
        std::cout<<"biClrUsed :"<<info_h->biClrUsed<<std::endl;
        std::cout<<"biClrImportant :"<<info_h->biClrImportant<<std::endl;
    }


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

        // Bitmap File Header 가져오기
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

        // Bitmap Info Header 가져오기
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

        // 팔레트 정보 가져오기
        fread(rgbPal, sizeof(RGBQUAD)*256, 1, fp);

        LONG Width = (info_h)->biWidth;      //512
        LONG Height = (info_h)->biHeight;    //512
        DWORD dwLine = ((((Width * (info_h)->biBitCount) + 31) &~31) >>3);   //512
        DWORD size = (file_h)->bfSize;      // 263222
        DWORD dwRawSize = (info_h)->biWidth * (info_h)->biHeight; //262144

        image = new BYTE*[(info_h)->biHeight];
        for(int i=0; i<(info_h)->biHeight; i++)
        {
            image[i] = new BYTE[(info_h)->biWidth];
            memset(image[i], 0, (sizeof(BYTE))*((info_h)->biWidth));
        }
        //readSize = fread(image, 1, (info_h)->biSizeImage, fp);
        for(int i=0; i<(info_h)->biHeight; i++)
        {
                readSize += fread(image[i],1, (info_h)->biWidth, fp);
                for(int j=0; j< (info_h)->biWidth; j++)
                {
                }
        }

        std::cout<<"읽어들인 이미지 크기 "<<readSize<<"..."<<std::endl;
        
        fclose(fp);
        return true;
    }

    bool BMP::SaveBmp(const char* filename,void (BMP::*func)(void))
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
        
        // 이미지 수정하는 멤버 함수
        (this->*func)();

        fwrite((char*)file_h, 1, sizeof(BITMAPFILEHEADER), fp);
        fwrite((char*)info_h, 1, sizeof(BITMAPINFOHEADER), fp);
        fwrite((char*)rgbPal, 1, sizeof(RGBQUAD)*256, fp);
        for(int i=0; i<(info_h)->biHeight; i++)
        {
            fwrite(image[i],1, (info_h)->biWidth, fp);
        }

        fclose(fp);
        return true;
    }

    bool BMP::DebugBlackDotSave(const char* filename,bool flag, int num)
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
        for(int i=0; i<info_h->biHeight; i++)
        {
            for(int j=0; j<info_h->biWidth; j++)
            {
                if(flag == true)
                {
                    image[i][j] = DebugBlackDot(image[i][j], num);
                }
                else
                {
                    image[i][j] = DebugWhiteDot(image[i][j], num);
                }
            }
        }

        fwrite((char*)file_h, 1, sizeof(BITMAPFILEHEADER), fp);
        fwrite((char*)info_h, 1, sizeof(BITMAPINFOHEADER), fp);
        fwrite((char*)rgbPal, 1, sizeof(RGBQUAD)*256, fp);
        for(int i=0; i<(info_h)->biHeight; i++)
        {
            fwrite(image[i],1, (info_h)->biWidth, fp);
        }

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
        LOG("필요없는 자원 수거 중...");
        for(int i=0; i<info_h->biHeight; i++)
        {
            delete[] image[i];
        }
        delete[] image;

        for(int i=0; i<filterY; i++)
        {
            delete[] filter[i];
            delete[] makedFilter[i];
        }
        delete[] filter;
        delete[] makedFilter;
        delete[] file_h;
        delete[] info_h;
        delete[] rgbPal;
        LOG("필요없는 자원 수거 완료...");
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

    void BMP::histogramEQ(void)
    {
        LONG Number_of_Pel = 0;
        LONG Max_Pel_Value = 255;
        LONG sum = 0;

        histogram = new int[256];
        normalizedSum = new double[256];
        LONG sumArr[256];

        for(int i=0; i<256; i++)
        {
            histogram[i] = 0;
        }

        int count =0;
        // Histogram 채우기 (픽셀에 해당하는 값 카운트)
        for(int i=0; i<info_h->biHeight; i++)
        {
            for(int j=0; j<info_h->biWidth; j++)
            {
                histogram[image[i][j]]++;
                count++;
            }
        }

        // Histogram의 Sum구하기
        for(int i=0; i<256; i++)
        {
           sum += histogram[i];
           sumArr[i] = sum;
        }
        Number_of_Pel = sumArr[255];
        
        // LUT 만들기
        for(int i=0; i<256; i++)
        {
           normalizedSum[i] = ((double)sumArr[i]*Max_Pel_Value/(info_h->biWidth * info_h->biHeight));
           normalizedSum[i] += 0.5;
           normalizedSum[i] = (BYTE)(normalizedSum[i]);
        }

        // LUT(normalizedSum)을 통한 이미지 변환
        for(int i=0; i<info_h->biHeight; i++)
        {
            for(int j=0; j<info_h->biWidth; j++)
            {
                image[i][j] = normalizedSum[image[i][j]];
            }
        }
        delete[] histogram;
        delete[] normalizedSum;
    }


    double** BMP::makeFilter(int x, int y)
    {
        this->filterX = x;
        this->filterY = y;

        filter = new double*[this->filterY];
        for(int i=0; i<this->filterY; i++)
        {
            filter[i] = new double[this->filterX];
            memset(filter[i], 0, sizeof(double) * this->filterX);
        }

        for(int i=0; i<this->filterY; i++)
        {
            for(int j=0; j<this->filterX; j++)
            {
                printf("filter[%d][%d] :",i,j);
                //scanf("%lf", &filter[i][j]);
                filter[i][j] = scanFraction();
            }
        }
        return (double**)filter;
    }

    double** BMP::makeTempFilter(int i, int j)
    {
        makedFilter= new double*[this->filterY];
        for(int i=0; i<this->filterY; i++)
        {
            makedFilter[i] = new double[this->filterX];
            memset(makedFilter[i],0, sizeof(double)*this->filterY);
        }

        int n = this->filterX/2;
        int tempA = 0;
        int tempB = 0;
        
        for(int a = i-n; a <= i+n; a++)
        {
            for(int b = j-n; b <= j+n; b++)
            {
                tempA = a+n-i;
                tempB = b+n-j;
                if((a<0) || (a>=info_h->biHeight) || (b<0) || (b>=info_h->biWidth))
                {
                    makedFilter[tempA][tempB] = 0;
                }
                else
                {
                    makedFilter[tempA][tempB] = (double)(image[a][b]);
                }
            }
        }

        return (double**)makedFilter;
    }

    BYTE BMP::calcFilter(void)
    {
        int tempResult = 0;

        for(int i=0; i<this->filterY; i++)
        {
            for(int j=0; j<this->filterX; j++)
            {
                double temp = (filter[i][j] * makedFilter[i][j]);
                tempResult += (int)temp;
            }
        }
        BYTE result = 0;
        if(tempResult > MAX_RGB)
        {
            tempResult = MAX_RGB;
        }
        else if(tempResult < MIN_RGB)
        {
            tempResult = MIN_RGB;
        }
        
        result = (BYTE)tempResult;
        
        return result;
    }


    bool BMP::ConvolutionFilter(const char *filename,int y,int x)
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
        
        resultImage= new BYTE*[(info_h)->biHeight];
        for(int i=0; i<(info_h)->biHeight; i++)
        {
            resultImage[i] = new BYTE[(info_h)->biWidth];
            memset(resultImage[i], 0, (sizeof(BYTE))*((info_h)->biWidth));
        }


        makeFilter(y,x);
        for(int i=0; i<info_h->biHeight; i++)
        {
            for(int j=0; j< info_h->biWidth; j++)
            {
                makeTempFilter(i,j);
                resultImage[i][j] = calcFilter();
            }
        }

        fwrite((char*)file_h, 1, sizeof(BITMAPFILEHEADER), fp);
        fwrite((char*)info_h, 1, sizeof(BITMAPINFOHEADER), fp);
        fwrite((char*)rgbPal, 1, sizeof(RGBQUAD)*256, fp);
        for(int i=0; i<(info_h)->biHeight; i++)
        {
            fwrite(resultImage[i],1, (info_h)->biWidth, fp);
        }

        fclose(fp);
        return true;
    }

    double BMP::scanFraction()
    {
        std::string str;
        double result = 0;
        std::cin>>str;

        if(str.find("/") != std::string::npos)
        {
            double temp1 = std::stoi(str.substr(0,str.find("/")));
            double temp2 = std::stoi(str.substr(str.find("/")+1, str.size()));
            result = temp1/temp2;
        }
        else
        {
            result = std::stoi(str);
        }
        return result;
    }
}// hkl
