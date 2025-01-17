//
// Created by Dxtag on 16.01.2025.
//

#ifndef UNTITLED4_PPM_H
#define UNTITLED4_PPM_H

#include <istream>

struct pixel
{
    int RED;
    int GREEN;
    int BLUE;
};
std::ostream &operator<<(std::ostream &out, pixel &px);
const pixel COLOR_BLACK = {0, 0, 0};
const pixel COLOR_WHITE = {255, 255, 255};
const pixel COLOR_RED = {255, 0, 0};
const pixel COLOR_GREEN = {0, 255, 0};
const pixel COLOR_BLUE = {0, 0, 255};
const pixel COLOR_YELLOW = {255, 255, 0};
const pixel COLOR_CYAN = {0, 255, 255};
const pixel COLOR_MAGENTA = {255, 0, 255};
const pixel COLOR_GRAY = {128, 128, 128};
const pixel COLOR_DARK_GRAY = {64, 64, 64};
const pixel COLOR_LIGHT_GRAY = {192, 192, 192};
const pixel COLOR_ORANGE = {255, 165, 0};
const pixel COLOR_PURPLE = {128, 0, 128};
const pixel COLOR_PINK = {255, 192, 203};
const pixel COLOR_BROWN = {165, 42, 42};

class PPM
{
public:
    PPM(std::istream &in);
    PPM(int w, int h, int max_color = 255, pixel bg=COLOR_WHITE);
    ~PPM();
    void SetPixel(int w, int h, pixel px);
    pixel GetPixel(int w, int h);
    bool In(int w, int h); // Sprawdz czy piksel mieści sie w obrazku
    int GetWidth() { return this->size.first; };
    int GetHeight() { return this->size.second; };
    int GetMaxColor() { return this->max_color; };
    void SetMaxColor(int max_color);
    friend std::ostream &operator<<(std::ostream &out, PPM &img);

private:
    pixel **image;
    std::pair<int, int> size;
    std::string type;
    int max_color;
};

#endif // UNTITLED4_PPM_H
