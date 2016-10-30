*************************************************
Title:          README.txt
Author:         Abdullah Khan
Date Created:   2016-10-09
Class:          [CSCI 493.69] Computer Vision
Professor:      Stamos
Purpose:        Homework #3
*************************************************

# "Line Finder"

## Series of programs to recognize lines in an image using the Hough Transform.

I. Parts Completed
- h1
- h2
- h3
- h4 does not draw lines appropriately.


II. Bugs Encountered
h4 is broken.

DrawLines would abort in h4, so I went into image.cc and added a check to make sure
	DrawLines would only attempt to color a pixel if and only if it is within the image boundaries.

III. Run Instructions
- Run `make` to build
- ./h1 {input gray-level image} {output gray-level edge image}
- ./h2 {input gray-level image} {input gray-level threshold} {output binary image}
- ./h3 {input binary edge image} {output gray-level Hough image} {output Hough-voting-array}
- ./h4 {input original gray-level image} {input Hough-voting-array} {input Hough threshold value} {output gray-level line image}

If you want to quickly run all the programs and look at results, take a look at the following recipes:
	output_simple_1
	output_simple_2
	output_complex_1
If you use these recipes you don't get to pick what your thresholds or output file names are.

Run `make {recipe}` to run the tests.

IV. Input and Output Files
	User's PGM images.