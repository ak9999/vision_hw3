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
		"Usage: " << argv[0] << " <input_gray-level_image.pgm> <threshold> <output_binary_image.pgm>"
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
	
	/*
	 * To make this truly binary, I will only use 2 gray levels (0 and 1).
	 * 0 = black, 1 = white
	 */
	img.SetNumberGrayLevels(1);

	int rows = img.num_rows();
	int cols = img.num_columns();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (img.GetPixel(i, j) < threshold)
				img.SetPixel(i, j, 0);
			else
				img.SetPixel(i, j, 1);
		}
	}

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
