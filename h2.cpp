/*
 * Author: Abdullah Khan
 * h2: Threshold the edge image so that we are only left with strong edges.
 *    This is basically program p1 from the previous assignment.
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
		"Usage: " << argv[0] << " {input gray-level image} {input gray-level threshold} {output binary image}"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const int threshold = atof(argv[2]);
	const string output(argv[3]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}
	
	Threshold(img, threshold);

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
