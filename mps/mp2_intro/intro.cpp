#include "RGBA/png.h"
#include "RGBA/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(const std::string & inputFile, const std::string & outputFile) {
	PNG pic(inputFile);
	PNG rotatedPic(pic.height(), pic.width());
	for (size_t i = 0; i < pic.width(); i++) {
		for (size_t j = 0; j < pic.height(); j++) {
			rotatedPic(j, pic.width() - i - 1) = pic(i, j);
		}
	}
	rotatedPic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
	PNG png(width, height);
	if (width < 2) {
		return png;
	}
	RGBAPixel colors[] = {
		RGBAPixel(255, 20, 147),
		RGBAPixel(0, 127, 255),
		RGBAPixel(255, 215, 0),
		RGBAPixel(50, 205, 50)
	};

    RGBAPixel lineColors[] = {
        RGBAPixel(0, 255, 255),
        RGBAPixel(255, 140, 0),
        RGBAPixel(255, 0, 255),
		RGBAPixel(250, 69, 0)
    };
	unsigned int squareSize = width / 2;
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            unsigned int colorIndex = (i / squareSize) + (j / squareSize) * 2;
            png(i, j) = colors[colorIndex];
            unsigned int centerX = (i / squareSize) * squareSize + squareSize / 2;
            unsigned int centerY = (j / squareSize) * squareSize + squareSize / 2;
            int dx = i - centerX;
            int dy = j - centerY;
            double distance = sqrt(dx * dx + dy * dy);
            double maxDistance = sqrt(2 * (squareSize / 2) * (squareSize / 2));
            double thickness = (distance / maxDistance) * (squareSize / 8) + 1;
            if (abs(dx) <= thickness || abs(dy) <= thickness || abs(dx - dy) <= thickness || abs(dx + dy) <= thickness) {
                png(i, j) = lineColors[colorIndex];
            }
        }
    }
	return png;
}
