#include "..\PPM\PPM.h"

#ifndef funcs
#define funcs



int quantization24_3(int color);
void FloydSteinberg(PPM& img,int (quantization)(int) );
void DrawLine(PPM& img, std::pair<int,int> startxy, std::pair<int,int> endxy, color px);
void DrawCircle(PPM& img, std::pair<int,int> startxy, int rad, color px);
bool IsMono(PPM &img);

#endif 
