/*
	Format for importing bitmaps for BitmapTo3dArray

	units in pixels for length, width, height

 <----------------------------------------------width * height--------------------------------------------->
 ___________________________________ ___________________________________ ___________________________________
|		/\							|									|									|
|<------+-----------width---------->|									|									|
|		|							|									|									|
|		|							|									|									|
|	length							|									|									|
|		|							|									|									|
|		|							|									|									|
|		|							|									|									|
|_______\/__________________________|___________________________________|___________________________________|

*/

#include <stdlib.h>
#include "bitmap_image.hpp"

int*** BitmapTo3dArray(const char* bitmap, int height, int width, int length) { // NOTE: height corresponds with x, width with y, and length with z

	bitmap_image image(bitmap);

	int totalPixels = 0;

	for (int i = 0; i < image.width(); i++) {
		for (int j = 0; j < image.height(); j++) {
			totalPixels++;
		}
	}
	std::cout << "total pixels in bitmap = " << totalPixels << std::endl;

	int*** arr = new int** [length];
	rgb_t col;

	if (length*width*height > totalPixels) { throw " double check dimensions "; return arr; }

	for (int i = 0; i < height; i++) {
		arr[i] = new int* [width];
		for (int j = 0; j < width; j++) {
			arr[i][j] = new int[length];
			for (int k = 0; k < length; k++) {

				image.get_pixel(k+i*width, j, col);

				if (signbit(128.0 - col.red)) { // red pixels are obstacles, black pixels are open spaces
					arr[i][j][k] = 1;   
				}
				else {
					arr[i][j][k] = -1;
				}

				std::cout << arr[i][j][k];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	return arr;
}