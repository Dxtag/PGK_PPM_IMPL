//
// Created by Dxtag on 16.01.2025.
//

#ifndef UNTITLED4_PPM_H
#define UNTITLED4_PPM_H

#include <istream>

struct color
{
    int RED;
    int GREEN;
    int BLUE;
    color();
    color(int r, int g, int b) : RED(r),GREEN(g),BLUE(b){};
    bool operator==(color c);
};

// Do użycia zamiast std::pair
struct point{
    int x;
    int y;
    point();
    point(int x_, int y_) : x(x_), y(y_){};
    bool operator==(point p);
};

std::ostream &operator<<(std::ostream &out, color &px);
const color COLOR_BLACK = {0, 0, 0};
const color COLOR_WHITE = {255, 255, 255};
const color COLOR_RED = {255, 0, 0};
const color COLOR_GREEN = {0, 255, 0};
const color COLOR_BLUE = {0, 0, 255};
const color COLOR_YELLOW = {255, 255, 0};
const color COLOR_CYAN = {0, 255, 255};
const color COLOR_MAGENTA = {255, 0, 255};
const color COLOR_GRAY = {128, 128, 128};
const color COLOR_DARK_GRAY = {64, 64, 64};
const color COLOR_LIGHT_GRAY = {192, 192, 192};
const color COLOR_ORANGE = {255, 165, 0};
const color COLOR_PURPLE = {128, 0, 128};
const color COLOR_PINK = {255, 192, 203};
const color COLOR_BROWN = {165, 42, 42};

class PPM
{
public:
    PPM()=default;
    PPM(std::istream &in);
    PPM(int w, int h, int max_color = 255, color bg=COLOR_WHITE);
    virtual ~PPM();
    void SetPixel(int w, int h, color clr);
    void SetPixel(point p, color clr);
    color GetPixel(int w, int h);
    bool In(int w, int h); // Sprawdz czy piksel mieści sie w obrazku
    virtual int GetWidth() { return this->size.first; };
    virtual int GetHeight() { return this->size.second; };
    virtual int GetMaxColor() { return this->max_color; };
    virtual void SetMaxColor(int max_color);
    bool operator==(PPM& img);
    friend std::ostream &operator<<(std::ostream &out, PPM &img);

private:
    color **image;
    std::pair<int, int> size;
    std::string type;
    int max_color;
};

#endif // UNTITLED4_PPM_H
