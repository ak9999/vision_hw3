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
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	// My chosen threshold is 125, though 120-125 produce similar results.
	if (argc != 4) {
		cout <<
		"Usage: " << argv[0] << " <input_image.pgm> <threshold> <output_image.pgm>"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const int threshold = atof(argv[2]);
	const string output(argv[3]);

	return 0;
}