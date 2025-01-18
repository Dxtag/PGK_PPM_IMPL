#include "..\PPM\PPM.h"

#ifndef funcs
#define funcs



int quantization24_3(int color);
void FloydSteinberg(PPM& img,int (quantization)(int) );
void DrawLine(PPM& img, point startxy, point endxy, color px);
void DrawCircle(PPM& img, point startxy, int rad, color px);
void DrawCircle_(PPM &img, point start, int rad, color px);
bool IsMono(PPM &img);

#endif 
