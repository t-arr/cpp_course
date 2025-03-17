/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author Chase Geigle
 * @author Anna LaValle
 * @date Created: Spring 2012
 * @date Modified: Spring 2025
*/
#include <algorithm>
#include <iostream>

#include "rgbapixel.h"
#include "png.h"

/**
 * This function accepts a PNG object, two integer coordinates and a color, and
 * proceeds to draw a horizontal line across the image at the y coordinate and
 * a vertical line down the image at the x coordinage using the given color,
 * thereby, updating the original image
 *
 * @param original A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 * @param color The color of the lines to be drawn.
 *
 */
void drawCrosshairs(PNG & original, size_t centerX, size_t centerY, const RGBAPixel & color)
{
    /// This function is already written for you so you can see how to
    /// interact with our PNG class.

    for (size_t x = 0; x < original.width(); x++)
        original(x, centerY) = color;

    for (size_t y = 0; y < original.height(); y++)
        original(centerX, y) = color;

}

/**
 * This function brightens a rectangle of a PNG, increasing the components
 * (red, green, blue) of each pixel by the given amount. You must account
 * for potential overflow issues (color components can only store numbers
 * between 0 and 255). If you attempt to store a value greater than 255
 * into a color component, the result will wrap around (and you won't be
 * able to check if it was greater than 255).
 *
 * @param original A PNG object which holds the image data to be modified.
 * @param amount The integer amount by which to increase each pixel's
 * components.
 *
  */
void brighten(PNG & original, int amount)
{
    /// You can assume amount is positive.
    for (size_t yi = 0; yi < original.height(); yi++)
    {
      for (size_t xi = 0; xi < original.width(); xi++){
        RGBAPixel & pixel = original(xi, yi);
        pixel.red = std::min(255, pixel.red + amount);
        pixel.green = std::min(255, pixel.green + amount);
        pixel.blue = std::min(255, pixel.blue + amount);

      }
    }
}



/**
 * This function blends, or averages, two PNGs together. That is, each pixel in
 * the returned image consists of the averaged components (red, green, blue) of
 * the two input images.
 *
 * @param firstImage  The first of the two PNGs to be averaged together with the second image. 
 * The firstImage is going to be modified and updated upong completion of the function.
 * @param secondImage The second of the two PNGs to be averaged together.
 *
 */
void blendImages(PNG & firstImage, const PNG & secondImage)
{
    for (size_t yi = 0; yi < std::min(firstImage.height(), secondImage.height()); yi++)
    {
      for (size_t xi = 0; xi < std::min(firstImage.width(), secondImage.width()); xi++){
        RGBAPixel & pixel1 = firstImage(xi, yi);
        const RGBAPixel & pixel2 = secondImage(xi, yi);
        pixel1.red = (pixel1.red + pixel2.red) / 2;
        pixel1.green = (pixel1.green + pixel2.green) / 2;
        pixel1.blue = (pixel1.blue + pixel2.blue) / 2;

      }
    }
}


/**
 * The main function in this program (the starting point of the execution of our
 * code).
 *
 * @return An integer indicating whether execution was successful.
 */
int main()
{
    // Open a new PNG image from the file sample.png.
    PNG image("sample.png");

    // Open a new PNG image from the file overlay.png.
    PNG overlay("overlay.png");

    // Brighten the image read from overlay.png.
    brighten(overlay, 128);

    // Blend sample.png and overlay.png together.
    blendImages(image, overlay);

    // Create a new RGBAPixel color for drawCrosshairs which is cyan.
    RGBAPixel cyanColor(0, 255, 255);

    // Draw two crosshairs on the image.
    drawCrosshairs(image, 460, 305, cyanColor);
    drawCrosshairs(image, 676, 410, cyanColor);

    image.resize(795,595);

    // Save the modified image to a file called output.png, overwriting the file
    // if it already exists.
    image.writeToFile("output.png");

    return 0;
}
