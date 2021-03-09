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
    pixels.clear();
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
    ppm_image result(w,h);
    int pixelRow, pixelColumn;
    ppm_pixel originalPixel;
    result.format = format;
    result.maxColor = maxColor;
    for (float i = 0; i < result.rows; i++) 
    {
        for (float j = 0; j < result.columns; j++)
        {   
            pixelRow = (i / (result.rows-1)) * (rows-1);
            pixelColumn = (j / (result.columns - 1)) * (columns - 1);
            originalPixel = get(pixelRow, pixelColumn);
            result.pixels.push_back(originalPixel.r);
            result.pixels.push_back(originalPixel.g);
            result.pixels.push_back(originalPixel.b);
        }
    }
    return result;
}


ppm_image ppm_image::flip_horizontal() const
{
    ppm_image result(columns,rows);
    ppm_pixel originalPixel;
    int pixelRow;
    float middleRow = (rows-1) / 2.0;
    result.format = format;
    result.maxColor = maxColor;
    for (float i = 0; i < middleRow; i++)
    {
        for (float j = 0; j < result.columns; j++)
        {
            pixelRow = middleRow + (middleRow - i);
            originalPixel = get(pixelRow, j);
            result.pixels.push_back(originalPixel.r);
            result.pixels.push_back(originalPixel.g);
            result.pixels.push_back(originalPixel.b);
        }
    }
    for (int i = middleRow+1; i < result.rows; i++)
    {
        for (float j = 0; j < result.columns; j++)
        {
            pixelRow = middleRow - (i-middleRow);
            originalPixel = get(pixelRow, j);
            result.pixels.push_back(originalPixel.r);
            result.pixels.push_back(originalPixel.g);
            result.pixels.push_back(originalPixel.b);
        }
    }
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
    if (row == 0)
    {
        pixelNum = col;
    }
    else
    {
        pixelNum = row * columns + col;
    }
    index = pixelNum * 3;
    return ppm_pixel{ (unsigned char) pixels[index], (unsigned char) pixels[index+1], (unsigned char) pixels[index+2] };
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
    int pixelNum, index;
    if (row == 0)
    {
        pixelNum = col;
    }
    else
    {
        pixelNum = row * columns + col;
    }
    index = pixelNum * 3;
    pixels[index] = c.r;
    pixels[index + 1] = c.g;
    pixels[index + 2] = c.b;
}

int ppm_image::height() const
{
   return rows;
}

int ppm_image::width() const
{
    return columns;
}
