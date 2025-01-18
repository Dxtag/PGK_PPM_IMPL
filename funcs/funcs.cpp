
#include "../PPM/PPM.h"
#include "funcs.h"
#include <functional>
#include <vector>
#include <cmath>
#include <iostream>

// Prosta funkcja zamieniająca palete 24 bitową na 3 bitową,
//  jak słabo działa zmienić threshold na coś innego niz 192
int quantization24_3(int color) { return color > 192 ? 255 : 0; }

bool IsMono(PPM &img)
{
    color tmp = {};
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
    color tmp{};
    color new_px = {};
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
                color px = img.GetPixel(w + 1, h);
                px.RED += (RED_ERR * 7 / 16);
                px.GREEN += (GREEN_ERR * 7 / 16);
                px.BLUE += (BLUE_ERR * 7 / 16);
                img.SetPixel(w + 1, h, px);
            }

            // 3/16
            if (img.In(w - 1, h - 1))
            {
                color px = img.GetPixel(w - 1, h - 1);
                px.RED += (RED_ERR * 3 / 16);
                px.GREEN += (GREEN_ERR * 3 / 16);
                px.BLUE += (BLUE_ERR * 3 / 16);
                img.SetPixel(w - 1, h - 1, px);
            }

            // 5/16
            if (img.In(w, h - 1))
            {
                color px = img.GetPixel(w, h - 1);
                px.RED += (RED_ERR * 5 / 16);
                px.GREEN += (GREEN_ERR * 5 / 16);
                px.BLUE += (BLUE_ERR * 5 / 16);
                img.SetPixel(w, h - 1, px);
            }

            // 1/16
            if (img.In(w + 1, h - 1))
            {
                color px = img.GetPixel(w + 1, h - 1);
                px.RED += (RED_ERR * 1 / 16);
                px.GREEN += (GREEN_ERR * 1 / 16);
                px.BLUE += (BLUE_ERR * 1 / 16);
                img.SetPixel(w + 1, h - 1, px);
            }
        }
    }
}


// 0,0 - lewy górny róg obrazka
void DrawLine(PPM& img, point startxy, point endxy, color px){

    if (!(img.In(startxy.x,startxy.y) && img.In(endxy.x,endxy.y))){
        throw std::string("Linia poza obrazkiem "+
                          std::to_string(startxy.x)) + " "
              + std::to_string(startxy.y)+"; "
              +std::to_string(endxy.x) + " "
              + std::to_string(endxy.y);
    }

    int dx = abs(startxy.x-endxy.x);
    int dy = abs(startxy.y-endxy.y);
    std::function<int(int)> fn_x; // Rysowanie przy użyciu funkcji, do dodania algorytm przyrostowy
    if (dx){
        fn_x = [startxy,dx,dy](int x)->int{ // funkcja xi->yi
            return round(dy/(double)dx*(x-startxy.x) + startxy.y);
        };
    }
    else{
        for (int y=startxy.y;y<endxy.y;y++){
            img.SetPixel(startxy.x, y, px);
        }
        return;
    }

    //Potrzebne do pętli uzupełnień
    std::vector<point> line_xy;
    int y;
    for(int x=startxy.x; x<=endxy.x; x++){
        y = fn_x(x);
        img.SetPixel(x,  y, px);
        line_xy.emplace_back(x, y);
    }

    //Pętla uzupełnień
    for (int i=0; i<dx;i++){
        if (line_xy[i].y > line_xy[i+1].y){
            for(int y=line_xy[i+1].y;y<line_xy[i].y;y++){
                img.SetPixel(line_xy[i].x,y,px);
            }
        }
        else{
            for(int y=line_xy[i].y;y<line_xy[i+1].y;y++){
                img.SetPixel(line_xy[i].x,y,px);
            }
        }
    }
}


//alogrytm ze slajdu ale coś nie działa
void DrawCircle(PPM &img, point start, int rad, color px) {
    int x0_ = 0, y0_=rad; // x0_ = x0' y0_ = x0' ze slajdu
    int xi_=0,yi_=0;

    for(int i=0;i<=rad;i++){
        xi_ = x0_ + i;
        yi_ = y0_ - round(sqrt(rad*rad - i*i));
        std::cout<<"x:"<<xi_<<" y:"<<yi_<<"\n";
        if (img.In(start.x + xi_, start.y + yi_))
            img.SetPixel(start.x + xi_, start.y + yi_,px);
        if (img.In(start.x + xi_, start.y + yi_))
            img.SetPixel(start.x + xi_, start.y + yi_,px);
        if (img.In(start.x - xi_, start.y + yi_))
            img.SetPixel(start.x - xi_, start.y + yi_,px);
        if (img.In(start.x + xi_, start.y - yi_))
            img.SetPixel(start.x + xi_, start.y - yi_,px);
        if (img.In(start.x - xi_, start.y - yi_))
            img.SetPixel(start.x - xi_, start.y - yi_,px);
        if (img.In(start.x + yi_, start.y + xi_))
            img.SetPixel(start.x + yi_, start.y + xi_,px);
        if (img.In(start.x - yi_, start.y + xi_))
            img.SetPixel(start.x - yi_, start.y + xi_,px);
        if (img.In(start.x + yi_, start.y - xi_))
            img.SetPixel(start.x + yi_, start.y - xi_,px);
        if (img.In(start.x - yi_, start.y - xi_))
            img.SetPixel(start.x - yi_, start.y - xi_,px);
    }
}

// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm do testu tego poprzedniego
void DrawCircle_(PPM &img, point start, int rad, color px) {
    int x = 0, y = rad;
    int d = 3 - 2 * rad;
    while (x <= y) {
        std::cout<<"x:"<<x<<" y:"<<y<<"\n";
        if(img.In(start.x + x, start.y + y))
            img.SetPixel(start.x + x, start.y + y,px);
        if(img.In(start.x - x, start.y + y))
            img.SetPixel(start.x - x, start.y + y,px);
        if(img.In(start.x + x, start.y - y))
            img.SetPixel(start.x + x, start.y - y,px);
        if(img.In(start.x - x, start.y - y))
            img.SetPixel(start.x - x, start.y - y,px);
        if(img.In(start.x + y, start.y + x))
            img.SetPixel(start.x + y, start.y + x,px);
        if(img.In(start.x - y, start.y + x))
            img.SetPixel(start.x - y, start.y + x,px);
        if(img.In(start.x + y, start.y - x))
            img.SetPixel(start.x + y, start.y - x,px);
        if(img.In(start.x - y, start.y - x))
            img.SetPixel(start.x - y, start.y - x,px);
        x++;

        if (d > 0) {y--;d += 4 * (x - y) + 10;} else {d += 4 * x + 6;}
    }
}
