#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <vector>
#include <initializer_list>

using char_vector = std::vector< std::vector<char> >;

int getBrightness(sf::Color pixel)
{
    int r = pixel.r;
    int g = pixel.g;
    int b = pixel.b;
    int bright = (r + g + b) / 3;

    return bright;
}

char pixelsToASCII(std::initializer_list<sf::Color> pixels, std::string &gradient, char mode)
{
    int bright = 0;
    for(const auto& pixel : pixels)
        bright += getBrightness(pixel);
    bright /= pixels.size();

    int step = 256 / gradient.length();
    int index = bright / step;

    if(mode == 'd')
        index = gradient.length() - index;
    
    return gradient[index];
}

char_vector imgToAscii(sf::Image &img, std::string gradient, int grad_n, char mode, bool squared)
{
    const uint32_t WIDTH  = img.getSize().x;
    const uint32_t HEIGHT = img.getSize().y;
    uint32_t height = HEIGHT / (1 + squared);
    char_vector out(height, std::vector<char>(WIDTH));

    gradient = gradient.substr(0, grad_n);

    int step = 1 + squared;

    for(uint32_t i = 0; i <= HEIGHT - step; i += step)
    {
        for(uint32_t j = 0; j < WIDTH; j++)
        {
            char c = 0;
            int h = i;
            if(squared)
            {
                sf::Color pixel1 = img.getPixel({j, i});
                sf::Color pixel2 = img.getPixel({j, i + 1});
                c = pixelsToASCII({pixel1, pixel2}, gradient, mode);
                h /= 2;
            }
            else
            {
                sf::Color pixel = img.getPixel({j, i});
                c = pixelsToASCII({pixel}, gradient, mode);
            }

            out[h][j] = c;
        }
    }

    return out;
}