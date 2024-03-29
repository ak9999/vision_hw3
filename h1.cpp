/*
 * Author: Abdullah Khan
 * h1: Locate edges and generates an "edge" image.
 *     Intensity at each edge point is proportional to edge magnitude.
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
	Image edge_image;
	InitBlankImage(edge_image, img.num_rows(), img.num_columns(), img.num_gray_levels());

	Sobel(img, edge_image);

	if (!WriteImage(output, edge_image)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}