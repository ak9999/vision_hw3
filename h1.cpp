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
	if (argc != 3) {
		cout <<
		"Usage: " << argv[0] << " {input gray-level image} {output gray-level edge image}"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const string output(argv[2]);

	return 0;
}