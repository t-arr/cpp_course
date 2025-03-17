/**
 * @file rgbapixel.h
 * Definition of the RGBAPixel class for the EasyPNG library.
 *
 * @author Chase Geigle
 * @author Anna LaValle
 * @date Created: Spring 2012
 * @date Modified: Spring 2025
 */
#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <stdint.h>
#include <cstdint>
using std::uint8_t;

class RGBAPixel {
    public:
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
        RGBAPixel();
        RGBAPixel(uint8_t red, uint8_t green, uint8_t blue);
};
#endif // RGBAPIXEL_H

