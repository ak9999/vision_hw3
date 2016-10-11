/*
 * Author: Abdullah Khan
 * h3: Hough Transform
 * Brightness of each pixel (voting bin) in the output gray-level Hough image should be proportional
 * to the number of votes it receives. The last output filename will store the votes of the voting array
 * in a representation of my choice. Note that the gray-level output will be used just for visualization.
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;



int main(int argc, char ** argv)
{
	if (argc != 4) {
		cout <<
		"Usage: " << argv[0] << " {input binary edge image} {output gray-level Hough image}"
		<< " {output Hough-voting-array}"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const string hough(argv[2]);
	const string votingarray(argv[3]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}
	
	Image hough; // Create hough image.
	InitBlankImage(hough, img.num_rows(), img.num_columns(), img.num_gray_levels());

	if (!WriteImage(output, hough)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
