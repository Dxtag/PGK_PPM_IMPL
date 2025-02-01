#include "..\PPM\PPM.h"
#include <cmath>
#ifndef funcs
#define funcs


enum rotate {
    left = -90,
    right = 90,
    flip_vertically = 180
};
int quantization24_3(int color);
void FloydSteinberg(PPM& img,int (quantization)(int) );
void DrawLine(PPM& img, point startxy, point endxy, color px);
void DrawCircle(PPM& img, point startxy, int rad, color px);
void DrawCircle_(PPM &img, point start, int rad, color px);
bool IsMono(PPM &img);
PPM& Rotate(PPM& img, rotate rad);
PPM& Move(PPM& img, rotate dir, int px_distance); // Przesunięcie równoległe

#endif 
