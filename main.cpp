#include <iostream>
#include "PPM.h"
#include <fstream>

//Prosta funkcja zamieniająca palete 24 bitową na 3 bitową, jak słabo działa zmienić threshold na coś innego niz 192
int quantization8_3(int color){return  color > 192 ? 255 : 0;}

void FloydSteinberg(PPM& img,int (quantization)(int) ){
    int RED_ERR, GREEN_ERR, BLUE_ERR;
    pixel tmp{};
    pixel new_px = {};
    for(int h =img.GetHeight()-1; h>=0; h--){
    for(int w =0; w<img.GetWidth(); w++)
    {
        tmp = img.GetPixel(w,h);

        //Zamiana na nową palete
        new_px.RED =    quantization(tmp.RED);
        new_px.GREEN =  quantization(tmp.GREEN);
        new_px.BLUE =   quantization(tmp.BLUE);
        img.SetPixel(w,h,new_px);

        // Obliczanie błędu do rozłożenia na okoliczne piksele
        RED_ERR =   tmp.RED   - new_px.RED  ;
        GREEN_ERR = tmp.GREEN - new_px.GREEN;
        BLUE_ERR =  tmp.BLUE  - new_px.BLUE ;

        img.SetPixel(w,h,new_px);

        // Rozłożenie błedu na okoliczne piksele
        //Schemat px
        //  0    [-1,0]     * [0,0]         7/16 [+1,0]
        //  3/16 [-1,-1]    5/16 [0,-1]     1/16 [+1,-1]

        // 7/16
        if (img.In(w+1,h)){
            pixel px = img.GetPixel(w+1,h);
            px.RED  +=(RED_ERR  *7/16);px.GREEN+=(GREEN_ERR*7/16);px.BLUE +=(BLUE_ERR *7/16);
            img.SetPixel(w+1,h,px);
        }

        // 3/16
        if (img.In(w-1,h-1)){
            pixel px = img.GetPixel(w-1,h-1);
            px.RED  +=(RED_ERR  *3/16);px.GREEN+=(GREEN_ERR*3/16);px.BLUE +=(BLUE_ERR *3/16);
            img.SetPixel(w-1,h-1,px);
        }

        // 5/16
        if (img.In(w,h-1)){
            pixel px = img.GetPixel(w,h-1);
            px.RED  +=(RED_ERR  *5/16);px.GREEN+=(GREEN_ERR*5/16);px.BLUE +=(BLUE_ERR *5/16);
            img.SetPixel(w,h-1,px);
        }

        // 1/16
        if (img.In(w+1,h-1)){
            pixel px = img.GetPixel(w+1,h-1);
            px.RED  +=(RED_ERR  *1/16);px.GREEN+=(GREEN_ERR*1/16);px.BLUE +=(BLUE_ERR *1/16);
            img.SetPixel(w+1,h-1,px);
        }
    }
    }
}


int main() {
     std::ifstream f;
     std::string in,out;
     std::cout<<"Podaj sciezke do plik wejsc: ";
     std::cin>>in;
     std::cout<<"\nPodaj sciezke do plik wyjsc: ";
     std::cin>>out;
     f.open(in);
     if (!f.is_open()){
         std::cout<<"\nOtwarcie sie nie powiodlo";
         return -1;
     }
     PPM img(f);
     f.close();
     FloydSteinberg(img, quantization8_3);
     std::ofstream o;
     o.open(out);
        if (!o.is_open()){
            std::cout<<"\nOtwarcie sie nie powiodlo";
            return -1;
        }
     o<<img;
     if(o.good()){std::cout<<"\nZapisanie powiodlo sie";}
     o.close();
}
