//
// Created by Dxtag on 16.01.2025.
//

#include <fstream>
#include <iostream>
#include "PPM.h"


PPM::PPM(std::ifstream &in){
    //Uwaga nie obsługuje komentarzy w plikach
    in >> this->type;
    if (this->type!="P3") throw std::string("Nieobslugiwany typ");
    std::string tmp;
    in>>this->size.first;
    in>>this->size.second;
    in>>this->max_color;
    this->image = reinterpret_cast<pixel**>(malloc(sizeof(pixel*)*this->GetHeight()));
    for(int i=0;i<this->GetHeight();i++) {
        this->image[i] = reinterpret_cast<pixel*>(malloc(sizeof(pixel)*this->GetWidth()));
        for (int j = 0; j < this->GetWidth(); j++) {
            pixel px{};
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

PPM::PPM(int w, int h, int max_color) {
    this->size = std::pair<int,int>(w,h);
    this->max_color = max_color;
    this->type = "P3";
}

void PPM::SetPixel(int w, int h, pixel px) {
    if (!this->In(w,h))
        throw ("Piksel poza obrazkiem"+ std::to_string(w)+" "+std::to_string(h));
    this->image[h][w]=px;
}

pixel PPM::GetPixel(int w, int h) {
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

std::ostream& operator<<(std::ostream& out, pixel& px){
    out<<px.RED<<" "<<px.GREEN<<" "<<px.BLUE;
    return out;
}

