#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <Magick++.h>

#include "matrix/matrixmath.h"

using namespace std;

//_____________________________________________________________________________
int main(int argc, char **argv)
{
	Magick::InitializeMagick(*argv);

	// Construct the image object. Separating image construction from the
	// the read operation ensures that a failure to read the image file
	// doesn't render the image object useless.
	Magick::Image *image = new Magick::Image;
	
	// We're using 8 bit colors
	assert(MaxRGB == 255);

	printf("loading image... ");
	try 
	{
		// Read a file into image object
		image->read( argv[1] );
	}
	catch( Magick::Exception &error_ )
	{
		cout << "Caught exception: " << error_.what() << endl;
		return EXIT_FAILURE;
	}
	printf("done\n");

	// Image dimensions
	printf("getting image pixel data... ");
	size_t	nrows = image->rows(), ncols = image->columns();

	// Matrices for the image layers
	matrix<unsigned char> rmat(nrows,ncols), gmat(nrows,ncols), bmat(nrows,ncols);
	for (size_t row = 0; row < nrows; ++row)
	{
		for (size_t col = 0; col < ncols; ++col)
		{
			rmat(row,col) = (unsigned char)image->pixelColor(row, col).redQuantum();
			gmat(row,col) = (unsigned char)image->pixelColor(row, col).greenQuantum();
			bmat(row,col) = (unsigned char)image->pixelColor(row, col).blueQuantum();
		}
	}
	printf("done\n");
	
	// Free the image from memory
	printf("freeing image memory... ");
	delete image;
	printf("done\n");

	int  min, max, range;
	double mean, stdev;
	printf("dimensions (rows, columns): %u %u\n", nrows, ncols);
	printf("number of pixels: %u\n", nrows*ncols);
	printf("==== red layer ====\n");
	printf("min = %u\n", min = matrixmath::min2d(rmat));
	printf("max = %u\n", max = matrixmath::max2d(rmat));
	printf("range = %u\n",range = max - min);
	printf("mean = %f\n", mean = matrixmath::mean2d(rmat));
	printf("stdev = %f\n", stdev = matrixmath::stdev2d(rmat,true));
	printf("stdev/range = %f\n", stdev/range);
	printf("==== green layer ====\n");
	printf("min = %u\n", min = matrixmath::min2d(gmat));
	printf("max = %u\n", max = matrixmath::max2d(gmat));
	printf("range = %u\n",range = max - min);
	printf("mean = %f\n", mean = matrixmath::mean2d(gmat));
	printf("stdev = %f\n", stdev = matrixmath::stdev2d(gmat,true));
	printf("stdev/range = %f\n", stdev/range);
	printf("==== blue layer ====\n");
	printf("min = %u\n", min = matrixmath::min2d(bmat));
	printf("max = %u\n", max = matrixmath::max2d(bmat));
	printf("range = %u\n",range = max - min);
	printf("mean = %f\n", mean = matrixmath::mean2d(bmat));
	printf("stdev = %f\n", stdev = matrixmath::stdev2d(bmat,true));
	printf("stdev/range = %f\n", stdev/range);

	return EXIT_SUCCESS;
}
