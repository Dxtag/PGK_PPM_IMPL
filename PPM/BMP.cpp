#include "BMP.h"

BMP::BMP(std::ifstream &f)
{
    if (!f.good())
    {
        throw std::string("Błędny strumień");
    }
    f.read(reinterpret_cast<char *>(&this->BFH), sizeof(this->BFH));
    f.read(reinterpret_cast<char *>(&this->BIH), sizeof(this->BIH));
    if (this->BIH.biSize != 40)
    {
        throw std::string("Nieobsługiwany format headera - obsługiwany tylko BITMAP INFO HEADER");
    }
    f.seekg(this->BFH.bfOffBits);
    
    
    char r, g, b;

    this->image = reinterpret_cast<color **>(malloc(BIH.biHeight * sizeof(color *)));
    for (int h = 0; h < this->BIH.biHeight; h++)
    {
        this->image[h] = reinterpret_cast<color *>(malloc(BIH.biWidth * sizeof(color)));
        for (int w = 0; w < this->BIH.biWidth; w++)
        {
            f.read(&r, this->BIH.biBitCount/24);
            f.read(&g, this->BIH.biBitCount/24);
            f.read(&b, this->BIH.biBitCount/24);
            this->image[h][w] = color(int(r), int(g), int(b));
        }
    }
}

BMP::~BMP()
{
}

int BMP::GetWidth()
{
    return 0;
}

int BMP::GetHeight()
{
    return 0;
}

int BMP::GetMaxColor()
{
    return 0;
}

void BMP::SetMaxColor(int max_color)
{
}


std::ostream& operator<<(std::ostream& out, BMP& img){
}