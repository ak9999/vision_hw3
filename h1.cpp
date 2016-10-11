/*
 * Author: Abdullah Khan
 * h1: Locate edges and generates an "edge" image.
 *     Intensity at each edge point is proportional to edge magnitude.
 *     Use squared gradient operator or the Laplacian.
 * Challenges: Laplacian requires finding zero-crossings in the image.
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include <cmath>
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	if (argc != 3) {
		cout <<
		"Usage: " << argv[0] << " {input gray-level image} {output gray-level edge image}"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const string output(argv[2]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}

	// Create output image with same dimensions as input.
	Image dst;
	dst.SetNumberGrayLevels(img.num_gray_levels());
	dst.AllocateSpaceAndSetSize(img.num_rows(), img.num_columns());
	for (unsigned int i = 0; i < dst.num_rows(); ++i) // Make dst black.
		for (unsigned int j = 0; j < dst.num_columns(); ++j)
			dst.SetPixel(i, j, 0);

	//Sobel(img, img.num_rows(), img.num_columns());

	if (!WriteImage(output, dst)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}