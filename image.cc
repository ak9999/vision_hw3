
// Class for representing a 2D gray-scale image,
// with support for reading/writing pgm images.
// To be used in Computer Vision class.

#include "image.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

// Pragmas
#pragma GCC diagnostic ignored "-Wsign-compare"

namespace ComputerVisionProjects {

Image::Image(const Image &an_image){
  AllocateSpaceAndSetSize(an_image.num_rows(), an_image.num_columns());
  SetNumberGrayLevels(an_image.num_gray_levels());

  for (size_t i = 0; i < num_rows(); ++i)
    for (size_t j = 0; j < num_columns(); ++j){
      SetPixel(i,j, an_image.GetPixel(i,j));
    }
}

Image::~Image(){
  DeallocateSpace();
}

void
Image::AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns) {
  if (pixels_ != nullptr) DeallocateSpace();
  pixels_ = new int*[num_rows];
  for (size_t i = 0; i < num_rows; ++i)
    pixels_[i] = new int[num_columns];

  num_rows_ = num_rows;
  num_columns_ = num_columns;
}

void
Image::DeallocateSpace() {
  for (size_t i = 0; i < num_rows_; i++)
    delete pixels_[i];
  delete pixels_;
  pixels_ = nullptr;
  num_rows_ = 0;
  num_columns_ = 0;
}

bool ReadImage(const string &filename, Image *an_image) {  
  if (an_image == nullptr) abort();
  FILE *input = fopen(filename.c_str(),"rb");
  if (input == 0) {
    cout << "ReadImage: Cannot open file" << endl;
    return false;
  }
  
  // Check for the right "magic number".
  char line[1024];
  if (fread(line, 1, 3, input) != 3 || strncmp(line,"P5\n",3)) {
    fclose(input);
    cout << "ReadImage: Expected .pgm file" << endl;
    return false;
  }
  
  // Skip comments.
  do
    fgets(line, sizeof line, input);
  while(*line == '#');
  
  // Read the width and height.
  int num_columns,num_rows;
  sscanf(line,"%d %d\n", &num_columns, &num_rows);
  an_image->AllocateSpaceAndSetSize(num_rows, num_columns);
  

  // Read # of gray levels.
  fgets(line, sizeof line, input);
  int levels;
  sscanf(line,"%d\n", &levels);
  an_image->SetNumberGrayLevels(levels);

  // read pixel row by row.
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0;j < num_columns; ++j) {
      const int byte=fgetc(input);
      if (byte == EOF) {
        fclose(input);
        cout << "ReadImage: short file" << endl;
        return false;
      }
      an_image->SetPixel(i, j, byte);
    }
  }
  
  fclose(input);
  return true; 
}

bool WriteImage(const string &filename, const Image &an_image) {  
  FILE *output = fopen(filename.c_str(), "w");
  if (output == 0) {
    cout << "WriteImage: cannot open file" << endl;
    return false;
  }
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  const int colors = an_image.num_gray_levels();

  // Write the header.
  fprintf(output, "P5\n"); // Magic number.
  fprintf(output, "#\n");  // Empty comment.
  fprintf(output, "%d %d\n%03d\n", num_columns, num_rows, colors);

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_columns; ++j) {
      const int byte = an_image.GetPixel(i , j);
      if (fputc(byte,output) == EOF) {
	    fclose(output);
            cout << "WriteImage: could not write" << endl;
	    return false;
      }
    }
  }

  fclose(output);
  return true; 
}

// Implements the Bresenham's incremental midpoint algorithm;
// (adapted from J.D.Foley, A. van Dam, S.K.Feiner, J.F.Hughes
// "Computer Graphics. Principles and practice", 
// 2nd ed., 1990, section 3.2.2);  
void
DrawLine(int x0, int y0, int x1, int y1, int color,
	 Image *an_image) {  
  if (an_image == nullptr) abort();

#ifdef SWAP
#undef SWAP
#endif
#define SWAP(a,b) {a^=b; b^=a; a^=b;}

  const int DIR_X = 0;
  const int DIR_Y = 1;
  
  // Increments: East, North-East, South, South-East, North.
  int incrE,
    incrNE,
    incrS,
    incrSE,
    incrN;     
  int d;         /* the D */
  int x,y;       /* running coordinates */
  int mpCase;    /* midpoint algorithm's case */
  int done;      /* set to 1 when done */
  
  int xmin = x0;
  int xmax = x1;
  int ymin = y0;
  int ymax = y1;
  
  int dx = xmax - xmin;
  int dy = ymax - ymin;
  int dir;

  if (dx * dx > dy * dy) {  // Horizontal scan.
    dir=DIR_X;
    if (xmax < xmin) {
      SWAP(xmin, xmax);
      SWAP(ymin , ymax);
    } 
    dx = xmax - xmin;
    dy = ymax - ymin;

    if (dy >= 0) {
      mpCase = 1;
      d = 2 * dy - dx;      
    } else {
      mpCase = 2;
      d = 2 * dy + dx;      
    }

    incrNE = 2 * (dy - dx);
    incrE = 2 * dy;
    incrSE = 2 * (dy + dx);
  } else {// vertical scan.
    dir = DIR_Y;
    if (ymax < ymin) {
      SWAP(xmin, xmax);
      SWAP(ymin, ymax);
    }
    dx = xmax - xmin;
    dy = ymax-ymin;    

    if (dx >=0 ) {
      mpCase = 1;
      d = 2 * dx - dy;      
    } else {
      mpCase = 2;
      d = 2 * dx + dy;      
    }

    incrNE = 2 * (dx - dy);
    incrE = 2 * dx;
    incrSE = 2 * (dx + dy);
  }
  
  /// Start the scan.
  x = xmin;
  y = ymin;
  done = 0;

  while (!done) {
    an_image->SetPixel(x,y,color);
  
    // Move to the next point.
    switch(dir) {
    case DIR_X: 
      if (x < xmax) {
	      switch(mpCase) {
	      case 1:
		if (d <= 0) {
		  d += incrE;  
		  x++;
		} else {
		  d += incrNE; 
		  x++; 
		  y++;
		}
		break;
  
            case 2:
              if (d <= 0) {
                d += incrSE; 
		x++; 
		y--;
              } else {
                d += incrE;  
		x++;
              }
	      break;
	      } 
      } else {
	done=1;
      }     
      break;

    case DIR_Y: 
        if (y < ymax) {
          switch(mpCase) {
	  case 1:
	    if (d <= 0) {
	      d += incrE;  
	      y++;
	    } else {
	      d += incrNE; 
	      y++; 
	      x++;
	    }
            break;
  
	  case 2:
	    if (d <= 0) {
                d += incrSE; 
		y++; 
		x--;
              } else {
                d += incrE;  
		y++;
	    }
            break;
	  } // mpCase
        } // y < ymin 
        else {
	  done=1;
	}
	break;    
    }
  }
}

// Functions added by me

// --------------MATH FUNCTIONS----------------------

// Convert degrees to radians
double deg2rad(double degrees) { return degrees * 4.0 * std::atan(1.0) / 180.0; }

// Apply std::cos to all in vector.
template <typename T> struct Cos : public std::unary_function<T,T>
{
  const T operator() (const T& x) const { return std::cos(x); }
};
void cosine_vector(std::vector<double>& v)
{
  std::transform(v.begin(), v.end(), v.begin(), Cos<double>());
}

// Apply std::sin to all in vector.
template <typename T> struct Sin : public std::unary_function<T,T>
{
  const T operator() (const T& x) const { return std::sin(x); }
};
void sine_vector(std::vector<double>& v)
{
  std::transform(v.begin(), v.end(), v.begin(), Sin<double>());
}
// --------------------------------------------------

void Threshold(Image &an_image, int threshold)
{
  /*
   * To make this truly binary, I will only use 2 gray levels (0 and 1).
   * 0 = black, 1 = white
   */
  an_image.SetNumberGrayLevels(1);

  int rows = an_image.num_rows();
  int cols = an_image.num_columns();

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (an_image.GetPixel(i, j) < threshold)
        an_image.SetPixel(i, j, 0);
      else
        an_image.SetPixel(i, j, 1);
    }
  }
} // end Threshold

void Sobel(Image &in, Image &out)
{
  int rows = in.num_rows();
  int cols = in.num_columns();

  float sobel_x[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };

  float sobel_y[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

  for (int i = 2; i < rows-2; ++i)
  {
    for (int j = 2; j < cols-2; ++j)
    {
      int x = (sobel_x[0][0] * in.GetPixel(i-1,j-1)) + (sobel_x[0][1] * in.GetPixel(i,j-1)) + (sobel_x[0][2] * in.GetPixel(i+1,j-1)) +
              (sobel_x[1][0] * in.GetPixel(i-1,j))   + (sobel_x[1][1] * in.GetPixel(i,j))   + (sobel_x[1][2] * in.GetPixel(i+1,j)) +
              (sobel_x[2][0] * in.GetPixel(i-1,j+1)) + (sobel_x[2][1] * in.GetPixel(i,j+1)) + (sobel_x[2][2] * in.GetPixel(i+1,j+1));

      int y = (sobel_y[0][0] * in.GetPixel(i-1,j-1)) + (sobel_y[0][1] * in.GetPixel(i,j-1)) + (sobel_y[0][2] * in.GetPixel(i+1,j-1)) +
              (sobel_y[1][0] * in.GetPixel(i-1,j))   + (sobel_y[1][1] * in.GetPixel(i,j))   + (sobel_y[1][2] * in.GetPixel(i+1,j)) +
              (sobel_y[2][0] * in.GetPixel(i-1,j+1)) + (sobel_y[2][1] * in.GetPixel(i,j+1)) + (sobel_y[2][2] * in.GetPixel(i+1,j+1));

      int magnitude = ceil( hypot(x, y) );
      out.SetPixel(i, j, magnitude);
    }
  }
}

void InitBlankImage(Image &an_image, int height, int width, int num_gray_levels)
{
  an_image.SetNumberGrayLevels(num_gray_levels);
  an_image.AllocateSpaceAndSetSize(height, width);
  for (unsigned int i = 0; i < height; ++i) // Make an_image black.
    for (unsigned int j = 0; j < width; ++j)
      an_image.SetPixel(i, j, 0);
}

// int** HoughTransform(Image &an_image, int height, int width)
// {
//   // Get center of image.
//   double center_x = width / 2.0;
//   double center_y = height / 2.0;
//   // Determine height of hough accumulator.
//   int diagonal = hypot(height, width);
//   // Create 2D accumulator array.
//   //int accum[diagonal][180] = {}; // Fill with zeroes.
//   int** accum = new int*[diagonal];

//   for (int d = 0; d < diagonal; ++d) // Fill with zeroes.
//   {
//     accum[d] = new int[180];
//     for (int w = 0; w < 180; ++w)
//       accum[d][w] = 0;
//   }

//   for (int i = 0; i < height; ++i)
//   {
//     for (int j = 0; j < width; ++j)
//     {
//       if (an_image.GetPixel(i, j) > 0)
//       {
//         for (int k = 0; k < 180; k++)
//         {
//           // Calculate r for every theta.
//           double r = ( (double)x - center_x ) * cos(deg2rad(k)) + ( (double)y - center_y ) * sin(deg2rad(k));
//           accum[i][j]++;
//         }
//       }
//     }

//     return new int[1][1];
//   }

// }

vector<double> theta_range()
{
  // Theta ranges
  vector<double> thetas;
  for (int i = -90; i <= 90; i++)
    thetas.push_back(deg2rad(i));
  return thetas;
}

vector<int> get_rhos(Image &an_image)
{
  int width = an_image.num_columns(); int height = an_image.num_rows();
  int diagonal = hypot(height, width);
  // Rho ranges
  vector<int> rhos;
  for (int i = -diagonal; i < diagonal; i++)
    rhos.push_back(i);
  return rhos;
}

vector<int> nonzero_y(Image &an_image)
{
  vector<int> y_indices;
  for(int i = 0; i < an_image.num_rows(); i++)
    for(int j = 0; j < an_image.num_columns(); j++)
      if (an_image.GetPixel(i,j) == 1)
        y_indices.push_back(i);
  return y_indices;
}

vector<int> nonzero_x(Image &an_image)
{
  vector<int> x_indices;
  for(int i = 0; i < an_image.num_rows(); i++)
    for(int j = 0; j < an_image.num_columns(); j++)
      if (an_image.GetPixel(i,j) == 1)
        x_indices.push_back(j);
  return x_indices;
}

int** hough_accumulator(Image &an_image, vector<double>& thetas)
{
  // sine and cosine of thetas are reusable, keep them.
  vector<double> cos_v = thetas;
  vector<double> sin_v = thetas;
  cosine_vector(cos_v);
  sine_vector(sin_v);
  int num_thetas = thetas.size();

  // Create the Hough accumulator array of theta and rho.
  // Hough accumulator is 2D with height 2*diagonal and width num_thetas
  int diagonal = ceil( hypot(an_image.num_columns(), an_image.num_rows()) );
  int** accumulator = new int*[2*diagonal];
  for (int i = 0; i < 2*diagonal; i++)
  {
    accumulator[i] = new int[num_thetas];
    for (int j = 0; j < num_thetas; j++)
      accumulator[i][j] = 0;
  } // Fill it with zeroes.

  // Get non-zero indices.
  vector<int> y_indices = nonzero_y(an_image);
  vector<int> x_indices = nonzero_x(an_image);
  if (y_indices.size() != x_indices.size()) abort();

  for (int i = 0; i < x_indices.size(); i++)
  {
    int x = x_indices[i];
    int y = y_indices[i];

    for (int theta = 0; theta <= num_thetas; theta++)
    {
      // Calculate rho. Add diagonal to ensure positive index.
      int rho = round( x * cos_v[theta] + y * sin_v[theta] ) + diagonal;
      accumulator[rho][theta] += 1;
    }
  }
  return accumulator;
}

Image hough_lines(int** accumulator, Image &out)
{

}

}  // namespace ComputerVisionProjects







