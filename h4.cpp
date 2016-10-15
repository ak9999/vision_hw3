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
#include <typeinfo>

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

	vector<pair<int,int>> rho_theta; // rho_theta pairs

	vector<vector<int>> accumulator;
	accumulator.resize(diagonal, vector<int>(width, 0));
	for (int i = 0; i < diagonal; i++)
	{
		for (int j = 0; j < width; j++)
		{
			string str;
			getline(of, str);
			int votes = stoi(str);
			accumulator[i][j] = votes;
			cout << votes << endl;
			if (votes > threshold)
			{
				rho_theta.push_back(make_pair(i,j));
			}
		}
	}
	of.close(); // Don't need the file open anymore.

	// Get a vector of lines.
	auto vector_of_lines = GetLines(rho_theta, img.num_rows(), img.num_columns(), threshold);

	for (size_t i = 0; i < vector_of_lines.size(); i++)
	{
		auto p0 = vector_of_lines[i].first;
		int x0 = p0.first;
		int y0 = p0.second;
		
		auto p1 = vector_of_lines[i].second;
		int x1 = p1.first;
		int y1 = p1.second;
	}

	if (!WriteImage(output, img)) {
		cout << "Can\'t write to file." << endl;
		return 0;
	}

	return 0;
}
