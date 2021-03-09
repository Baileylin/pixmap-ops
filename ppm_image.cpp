#include "ppm_image.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace agl;
using namespace std;

ppm_image::ppm_image() 
{
    format = "P3";
    columns = 0;
    rows = 0;
    maxColor = 255;
    for (int onePixel : pixels) 
    {
        onePixel = 0;
    }
}

ppm_image::ppm_image(int w, int h) 
{
    format = "P3";
    columns = w;
    rows = h;
    maxColor = 255;
    for (int onePixel : pixels)
    {
        onePixel = 0;
    }
}

ppm_image::ppm_image(const ppm_image& orig)
{
    format = orig.format;
    columns = orig.columns;
    rows = orig.rows;
    maxColor = orig.maxColor;
    pixels = orig.pixels;
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{
   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }
   format = orig.format;
   columns = orig.columns;
   rows = orig.rows;
   maxColor = orig.maxColor;
   pixels = orig.pixels;
   return *this;   
}

ppm_image::~ppm_image()
{
}

bool ppm_image::load(const std::string& filename)
{
    ifstream readFile(filename);
    string ppmText;
    int index =6;
    if (!readFile) 
    {
        return false;
    }
    while (readFile)
    {
        string text;
        readFile >> text;
        ppmText.append(text+" ");
    }
    readFile.close();
    format = ppmText.substr(0, 2);
    columns = stoi(ppmText.substr(3,1));
    rows = stoi(ppmText.substr(5, 1));
    while(index < ppmText.size())
    {
        string temporary;
        while (ppmText.substr(index, 1) != " " && index < ppmText.size())
        {
            temporary.append(ppmText.substr(index, 1));
            index++;
        }
        
        if (temporary != "") 
        {
            pixels.push_back(stoi(temporary));
        }
        index++;
    }
    for (int onePixel : pixels)
    {
        cout << onePixel<<" ";
    }
    return true;
}

bool ppm_image::save(const std::string& filename) const
{
   return false;
}

 ppm_image ppm_image::resize(int w, int h) const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result;
    return result;
}

ppm_image ppm_image::subimage(int startx, int starty, int w, int h) const
{
    ppm_image result;
    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{
}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
   ppm_image result;
   return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result;
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
   return ppm_pixel{ 0,0,0 };
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
}

int ppm_image::height() const
{
   return rows;
}

int ppm_image::width() const
{
    return columns;
}
