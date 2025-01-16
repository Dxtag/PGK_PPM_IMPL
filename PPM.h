//
// Created by Dxtag on 16.01.2025.
//

#ifndef UNTITLED4_PPM_H
#define UNTITLED4_PPM_H

#include <istream>
#include "PPM.h"


struct pixel{
    int RED;
    int GREEN;
    int BLUE;
};
std::ostream& operator<<(std::ostream& out, pixel& px);


class PPM {
public:
    PPM(std::ifstream &in);
    PPM(int w, int h, int max_color = 255);
    ~PPM();
    void SetPixel(int w, int h, pixel px);
    pixel GetPixel(int w, int h);
    bool In(int w, int h); //Sprawdz czy piksel mieści sie w obrazku
    int GetWidth() {return this->size.first;};
    int GetHeight(){return this->size.second;};
    int GetMaxColor(){return this->max_color;};
    void SetMaxColor(int max_color);
    friend std::ostream& operator<<(std::ostream& out, PPM& img);
private:
    pixel** image;
    std::pair<int,int> size;
    std::string type;
    int max_color;
};

#endif //UNTITLED4_PPM_H
