/*
 * Author: Abdullah Khan
 * h4: Find Lines
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include "image.h"

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char ** argv)
{
	if (argc != 5) {
		cout <<
		"Usage: " << argv[0] << " {input original gray-level image} {input Hough-voting-array}"
		<< " {input Hough threshold value} {output gray-level line image}"
		<< endl;
		return 0;
	}

	const string input(argv[1]);
	const string array(argv[2]);
	const int threshold = atof(argv[3]);
	const string output(argv[4]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
