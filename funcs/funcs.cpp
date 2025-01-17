
#include "../PPM/PPM.h"
#include "funcs.h"
#include <functional>
#include <vector>
#include <cmath>

// Prosta funkcja zamieniająca palete 24 bitową na 3 bitową,
//  jak słabo działa zmienić threshold na coś innego niz 192
int quantization24_3(int color) { return color > 192 ? 255 : 0; }

bool IsMono(PPM &img)
{
    pixel tmp = {};
    for (int h = img.GetHeight() - 1; h >= 0; h--)
    {
        for (int w = 0; w < img.GetWidth(); w++)
        {
            tmp = img.GetPixel(w, h);
            if (tmp.RED != tmp.GREEN || tmp.GREEN != tmp.BLUE ||tmp.RED!=tmp.BLUE)
                return false;
        }
    }
    return true;
}

// Świetny opis xD
//  "Ten algorytm nie wykorzystuje komórki. Często jest wykorzystywany w 
// drajwerach printerów i redaktorów graficznych."
void FloydSteinberg(PPM &img, int(quantization)(int))
{
    int RED_ERR, GREEN_ERR, BLUE_ERR;
    pixel tmp{};
    pixel new_px = {};
    for (int h = img.GetHeight() - 1; h >= 0; h--)
    {
        for (int w = 0; w < img.GetWidth(); w++)
        {
            tmp = img.GetPixel(w, h);

            // Zamiana na nową palete
            new_px.RED = quantization(tmp.RED);
            new_px.GREEN = quantization(tmp.GREEN);
            new_px.BLUE = quantization(tmp.BLUE);
            img.SetPixel(w, h, new_px);

            // Obliczanie błędu do rozłożenia na okoliczne piksele
            RED_ERR = tmp.RED - new_px.RED;
            GREEN_ERR = tmp.GREEN - new_px.GREEN;
            BLUE_ERR = tmp.BLUE - new_px.BLUE;

            img.SetPixel(w, h, new_px);

            // Rozłożenie błedu na okoliczne piksele
            // Schemat px
            //  0    [-1,0]     * [0,0]         7/16 [+1,0]
            //  3/16 [-1,-1]    5/16 [0,-1]     1/16 [+1,-1]

            // 7/16
            if (img.In(w + 1, h))
            {
                pixel px = img.GetPixel(w + 1, h);
                px.RED += (RED_ERR * 7 / 16);
                px.GREEN += (GREEN_ERR * 7 / 16);
                px.BLUE += (BLUE_ERR * 7 / 16);
                img.SetPixel(w + 1, h, px);
            }

            // 3/16
            if (img.In(w - 1, h - 1))
            {
                pixel px = img.GetPixel(w - 1, h - 1);
                px.RED += (RED_ERR * 3 / 16);
                px.GREEN += (GREEN_ERR * 3 / 16);
                px.BLUE += (BLUE_ERR * 3 / 16);
                img.SetPixel(w - 1, h - 1, px);
            }

            // 5/16
            if (img.In(w, h - 1))
            {
                pixel px = img.GetPixel(w, h - 1);
                px.RED += (RED_ERR * 5 / 16);
                px.GREEN += (GREEN_ERR * 5 / 16);
                px.BLUE += (BLUE_ERR * 5 / 16);
                img.SetPixel(w, h - 1, px);
            }

            // 1/16
            if (img.In(w + 1, h - 1))
            {
                pixel px = img.GetPixel(w + 1, h - 1);
                px.RED += (RED_ERR * 1 / 16);
                px.GREEN += (GREEN_ERR * 1 / 16);
                px.BLUE += (BLUE_ERR * 1 / 16);
                img.SetPixel(w + 1, h - 1, px);
            }
        }
    }
}


// 0,0 - lewy dolny róg obrazka
void DrawLine(PPM& img,std::pair<int,int> startxy, std::pair<int,int> endxy, pixel px){
    if (!(img.In(startxy.first,startxy.second) && img.In(endxy.first,endxy.second))){
        throw std::string("Linia poza obrazkiem "+
        std::to_string(startxy.first)) + " "
        + std::to_string(startxy.second)+"; "
        +std::to_string(endxy.first) + " "
        + std::to_string(endxy.second);
    }
    int dx = abs(startxy.first-endxy.first);
    int dy = abs(startxy.second-endxy.second);
    std::function<int(int)> fn_x;
    if (dx){
        fn_x = [startxy,dx,dy](int x)->int{ // funkcja xi->yi
        return round((double)dy/dx)*(x-startxy.first) + startxy.second;
        };
    }
    else{
        for (int y=startxy.second;y<endxy.second;y++){
            img.SetPixel(startxy.first, img.GetWidth()-y-1, px);
        }
        return;
    }

    //Potrzebne do pętli uzupełnień
    std::vector<std::pair<int,int>> line_xy;

    for(int x=startxy.first; x<=endxy.first; x++){
        img.SetPixel(x, img.GetWidth()-fn_x(x)-1 , px); // odwrócenie y - 0,0 jest teraz w lewym dolnym rogu
        line_xy.emplace_back(x, img.GetWidth()-fn_x(x)-1 );
    }

    //Pętla uzupełnień
    for (int i=0; i<dx;i++){
        if (line_xy[i].second > line_xy[i+1].second){
            for(int y=line_xy[i+1].second;y<line_xy[i].second;y++){
                img.SetPixel(line_xy[i].first,y,px);
            }
        }
        else{
            for(int y=line_xy[i].second;y<line_xy[i+1].second;y++){
                img.SetPixel(line_xy[i].first,y,px);
            }
        }
    }
}
