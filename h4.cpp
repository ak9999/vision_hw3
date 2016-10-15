/*
 * Author: Abdullah Khan
 * h4: Find Lines
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include "image.h"
#include <vector>
#include <utility>
#include <cmath>

using namespace std;
using namespace ComputerVisionProjects;

// Leave me alone
#pragma GCC diagnostic ignored "-Wsign-compare"

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

	ifstream in(array);
	if (!in.is_open())
	{
		cout << "Could not open " << array << " for writing. Sorry." << endl;
		return 0;
	}

	int hough_height, hough_width;

	// Start reading file.
	{
		string str;
		getline(in, str);
		hough_height = stoi(str);
		getline(in, str);
		hough_width = stoi(str);
	} // I have read the first two lines of the file.

	// Init Hough accumulator array.
	vector<vector<int>> accumulator;
	accumulator.resize(hough_height, vector<int>(hough_width, 0));

	vector<pair<int,int>> rho_theta; // pixels that will be above threshold
	for (int i = 0; i < hough_height; i++)
	{
		for (int j = 0; j < hough_width; j++)
		{
			string str;
			getline(in, str);
			int votes = stoi(str);
			accumulator[i][j] = votes;
			if (votes > threshold) // Pixel is significantly bright
			{
				// Create std::pair<int,int> and push it into vector
				rho_theta.push_back(make_pair(i,j));
			}
		}
	}

	CalcLines(rho_theta, img);

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
