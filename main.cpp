#include <iostream>
#include <fstream>
#include "funcs/funcs.h"
#include "PPM/PPM.h"


void fs();
void dl();
int main() {
    std::cout<<"1: Algorytm Floyda-Steinberga (24bity do 3 bitów)\n2: Rysowanie linii\nopcja:";
    int opt;
    std::cin>>opt;
    switch (opt){
        case 1:
        fs();
        break;
        case 2:
        dl();
        break;
        default:
            break;
    }
     
}


void fs(){
     std::ifstream f;
     std::string in,out;
     std::cout<<"Podaj sciezke do plik wejsc: ";
     std::cin>>in;
     std::cout<<"\nPodaj sciezke do plik wyjsc: ";
     std::cin>>out;
     f.open(in);
     if (!f.is_open()){
         std::cout<<"\nOtwarcie sie nie powiodlo";
         return;
     }
     PPM img(f);
     f.close();
     FloydSteinberg(img, quantization24_3);
     std::ofstream o;
     o.open(out);
        if (!o.is_open()){
            std::cout<<"\nOtwarcie sie nie powiodlo";
            return;
        }
     o<<img;
     if(o.good()){std::cout<<"\nZapisanie powiodlo sie";}
     o.close();
}
void dl(){
    std::cout<<"Rysowanie lini\n";
    std::cout<<"Podaj sciezke do plik wyjsc: ";
    std::string out;
    std::cin>>out;
    int x,y,lsx,lsy,lex,les;
    std::cout<<"Podaj rozmiar x, rozmiar y, poczatek x poczatek y koniec x koniex y\n";
    std::cin>>x>>y>>lsx>>lsy>>lex>>les;
    PPM img(x, y);
    try{
        DrawLine(img, std::pair<int,int>(lsx,lsy), std::pair<int,int>(lex,les),COLOR_BLUE);
    }
    catch (std::string& e){
        std::cout<<e<<"\n";
        return;
    }

    std::ofstream o;
    o.open(out);
    if (!o.is_open()){
        std::cout<<"\nOtwarcie sie nie powiodlo";
        return;
    }
    o<<img;
    if(o.good()){std::cout<<"\nZapisanie powiodlo sie";}
    o.close();
}
