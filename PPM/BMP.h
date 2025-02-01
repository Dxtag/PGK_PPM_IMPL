#include <cstdint>
#include "PPM.h"
#include <fstream>
#include <iostream>

#ifndef UNTITLED4_BPM
#define UNTITLED4_BPM

#pragma pack(push, 1)
struct BITMAPFILEHEADER{
    uint16_t bfType;      // BM
    uint32_t bfSize;      // Wielkośc pliku w bajtach
    uint16_t bfReserved1; // 0
    uint16_t bfReserved2; // 0
    uint32_t bfOffBits;   // offset do startu grafiki
} ;

struct BITMAPINFOHEADER {
    uint32_t biSize;          // 40 
    int32_t  biWidth;         // szerokość
    int32_t  biHeight;        // wysokość
    uint16_t biPlanes;        // 1
    uint16_t biBitCount;      // liczba bitów palety kolorów
    uint32_t biCompression;   // metoda kompresji, musi być 0 bo nie chce mi sie tego implementować
    uint32_t biSizeImage;     // wielkośc obrazka, nie ma znacznia bo nie bedzie obsługiwac dekompresji
    int32_t  biXPelsPerMeter; // pixele na metr na szerokość
    int32_t  biYPelsPerMeter; // pixele na metr na wysokość
    uint32_t biClrUsed;       // kolory, 0 - wszytskie
    uint32_t biClrImportant;  // wazne kolor, 0 - wszystkie
} ;
#pragma pack(pop)


class BMP : public PPM{
    public:
    BMP(std::ifstream& f);
    ~BMP();
    int GetWidth() override;
    int GetHeight() override;
    int GetMaxColor() override;  
    void SetMaxColor(int max_color) override;
    private:
    color** image;
    BITMAPFILEHEADER BFH;
    BITMAPINFOHEADER BIH;
};


std::ostream& operator<<(std::ostream& out, BMP& img);

#endif