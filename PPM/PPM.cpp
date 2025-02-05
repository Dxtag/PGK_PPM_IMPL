//
// Created by Dxtag on 16.01.2025.
//

#include <fstream>
#include <iostream>
#include "PPM.h"


PPM::PPM(std::istream &in){
    //Uwaga nie obsługuje komentarzy w plikach
    in >> this->type;
    if (this->type!="P3") throw std::string("Nieobslugiwany typ");
    std::string tmp;
    in>>this->size.first;
    in>>this->size.second;
    in>>this->max_color;
    this->image = reinterpret_cast<color**>(malloc(sizeof(color*) * this->GetHeight()));
    for(int i=0;i<this->GetHeight();i++) {
        this->image[i] = reinterpret_cast<color*>(malloc(sizeof(color) * this->GetWidth()));
        for (int j = 0; j < this->GetWidth(); j++) {
            color px{};
            in>>px.RED;
            in>>px.GREEN;
            in>>px.BLUE;
            this->image[i][j] = px;
        }
    }
}

PPM::~PPM() {
    for(int i=0;i<this->GetHeight();i++) {
        free(this->image[i]);
    }
    free(this->image);
}

PPM::PPM(int w, int h, int max_color, color bg) {
    this->size = std::pair<int,int>(w,h);
    this->max_color = max_color;
    this->type = "P3";
    this->image = reinterpret_cast<color**>(malloc(sizeof(color*) * this->GetHeight()));
    for(int i=0;i<this->GetHeight();i++) {
        this->image[i] = reinterpret_cast<color*>(malloc(sizeof(color) * this->GetWidth()));
        for (int j = 0; j < this->GetWidth(); j++) {
            this->image[i][j] = bg;
        }
    }
}

void PPM::SetPixel(int w, int h, color clr) {
    if (!this->In(w,h))
        throw ("Piksel poza obrazkiem"+ std::to_string(w)+" "+std::to_string(h));
    this->image[h][w]=clr;
}

void PPM::SetPixel(point p, color clr)
{
    this->SetPixel(p.x,p.y,clr);
}

color PPM::GetPixel(int w, int h) {
    if (!this->In(w,h))
        throw ("Piksel poza obrazkiem "+ std::to_string(w)+" "+std::to_string(h));
    return this->image[h][w];
}

std::ostream& operator<<(std::ostream& out, PPM& img){
    out<<img.type
       <<"\n"<<
       img.size.first
       <<" "
       <<img.size.second
       <<"\n"
       <<img.max_color;
    for(int i=0;i<img.size.second;i++){
        out<<"\n";
        for (int j = 0; j < img.size.first; j++) {
            out<<img.image[i][j]<<" ";
        }
    }
    return out;
}

void PPM::SetMaxColor(int max_color_) {
    for(int i=0;i<this->size.second;i++){
        for (int j = 0; j < this->size.first; j++) {
            if (this->image[i][j].RED>max_color||
                this->image[i][j].GREEN>max_color||
                this->image[i][j].BLUE>max_color
                ) throw std::string("W obrazku wystepuja kolory ponad max_color");
        }
    }
    this->max_color = max_color_;
}

bool PPM::In(int w, int h) {
    return w<GetWidth()&&h<GetHeight()&&h>=0&&w>=0;
}

bool PPM::operator==(PPM &img) {
    if (this->GetHeight()!=img.GetHeight() || this->GetWidth()!=img.GetWidth()) return false;
    for(int i=0;i<this->GetHeight();i++){
        for (int j = 0; j < this->GetWidth(); j++) {
            if (!((img.GetPixel(j, i)) == this->GetPixel(j, i))) return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, color& px){
    out<<px.RED<<" "<<px.GREEN<<" "<<px.BLUE;
    return out;
}

color::color() {

}

bool color::operator==(color c) {
    return c.RED==this->RED && c.BLUE==this->BLUE && this->GREEN == c.GREEN;
}

point::point() {

}

bool point::operator==(point p) {
    return p.x==this->x && p.y == this->y;
}
