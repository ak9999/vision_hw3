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

	fstream of(array);
	if (!of.is_open())
	{
		cout << "Could not open " << array << " for writing. Abort." << endl;
		return 0;
	}

	int diagonal, width;

	// Start reading file.
	{
		string str;
		getline(of, str);
		diagonal = stoi(str);
		getline(of, str);
		width = stoi(str);
	} // I have read the first two lines of the file.

	// Create accumulator array and re-create Hough space image.
	Image hough; hough.AllocateSpaceAndSetSize(diagonal, width);
	hough.SetNumberGrayLevels(255);

	int** accumulator = new int*[diagonal];
	for (int i = 0; i < diagonal; i++)
	{
		accumulator[i] = new int[width];
		for (int j = 0; j < width; j++)
		{
			string str;
			getline(of, str);
			int votes = stoi(str);
			accumulator[i][j] = votes;
			hough.SetPixel(i, j, votes);
		}
	} // Accumulator array obtained!

	// code

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
