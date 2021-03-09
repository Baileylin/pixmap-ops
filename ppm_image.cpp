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
    columns = w;
    rows = h;
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
    vector<string> temporaryVector;
    int index =0;
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
            temporaryVector.push_back(temporary);
        }
        index++;
    }
    format = temporaryVector[0];
    columns = stoi(temporaryVector[1]);
    rows = stoi(temporaryVector[2]);
    maxColor = stoi(temporaryVector[3]);
    for (int i = 4; i < temporaryVector.size(); i++) 
    {
        pixels.push_back(stoi(temporaryVector[i]));
    }
    return true;
}

bool ppm_image::save(const std::string& filename) const
{
    string outputString = "";
    outputString = outputString + format + "\n";
    outputString = outputString + to_string(columns) + " ";
    outputString = outputString + to_string(rows) + "\n";
    outputString = outputString + to_string(maxColor) + "\n";
    for (int i = 0; i < pixels.size(); i++) 
    {
        outputString = outputString + to_string(pixels[i])+" ";
    }
    ofstream writeFile(filename);
    writeFile << outputString;
    return true;
}

 ppm_image ppm_image::resize(int w, int h) const
{
     ppm_image result = new ppm_image( 2, 3);
    return ppm_image(w,h);
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
    int pixelNum, index;
    if (row == 1) 
    {
        pixelNum = col;
    }
    else 
    {
        pixelNum = (row - 1) * columns + col;
    }
    index = pixelNum * 3 - 1;
    return ppm_pixel{ (unsigned char) pixels[index-2], (unsigned char) pixels[index-1], (unsigned char) pixels[index] };
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
    int pixelNum, index;
    if (row == 1)
    {
        pixelNum = col;
    }
    else
    {
        pixelNum = (row - 1) * columns + col;
    }
    index = pixelNum * 3 - 1;
    pixels[index - 2] = c.r;
    pixels[index - 1] = c.g;
    pixels[index] = c.b;
}

int ppm_image::height() const
{
   return rows;
}

int ppm_image::width() const
{
    return columns;
}
