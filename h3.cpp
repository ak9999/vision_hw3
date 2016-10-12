/*
 * Author: Abdullah Khan
 * h3: Hough Transform
 * Brightness of each pixel (voting bin) in the output gray-level Hough image should be proportional
 * to the number of votes it receives.
 * The last output filename will store the votes of the voting array
 * in a representation of my choice. Note that the gray-level output will be used just for visualization.
 */

#include <iostream>
#include <string>
#include <cstdlib> // for std::atof
#include <algorithm> // for std::max_element
#include <fstream>
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
	const string output(argv[2]);
	const string votingarray(argv[3]);

	Image img;
	if (!ReadImage(input, &img)) {
		cout << "Can\'t read file " << input << endl;
		return 0;
	}

	// Get rhos and thetas.
	vector<int> rho_values = get_rhos(img);
	vector<double> theta_v = theta_range();

	// Get diagonal
	int diagonal = ceil( hypot(img.num_columns(), img.num_rows()) );

	// Get accumulator array
	int** accumulator = hough_accumulator(img, theta_v);

	{
		fstream of(votingarray, std::ios::out);
		if (!of.is_open()) abort();
		of << 2*diagonal << " " << theta_v.size() << endl;
		for (int i = 0; i < 2*diagonal; i++)
			for (size_t j = 0; j < theta_v.size(); j++)
				of << accumulator[i][j] << endl;
		of.close();
	} // Write accumulator array to file.
	
	Image hough; // Create hough image.
	InitBlankImage(hough, img.num_rows(), img.num_columns(), img.num_gray_levels());

	hough_space(accumulator, hough);

	if (!WriteImage(output, hough)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
