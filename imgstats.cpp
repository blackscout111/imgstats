#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <Magick++.h>

#include "matrix/matrixmath.h"

using namespace std;

//_____________________________________________________________________________
void printMat(const matrix::matrix<unsigned char> &mat)
{
	for (size_t i = 0; i < mat.height(); ++i)
	{
		for (size_t j = 0; j < mat.width(); ++j)
		{
			printf("%3u  ", mat(i,j));
		}
		printf("\n");
	}
}


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

	// Image dimensions
	size_t	nrows = image->rows(), ncols = image->columns();

	matrix::matrix<unsigned char> rmat(nrows,ncols), gmat(nrows,ncols), bmat(nrows,ncols);
	for (size_t row = 0; row < nrows; ++row)
	{
		for (size_t col = 0; col < ncols; ++col)
		{
			rmat(row,col) = (unsigned char)image->pixelColor(row, col).redQuantum();
			gmat(row,col) = (unsigned char)image->pixelColor(row, col).greenQuantum();
			bmat(row,col) = (unsigned char)image->pixelColor(row, col).blueQuantum();
		}
	}
	delete image;

	printf("image dimensions (nrows, ncols): %u %u\n", nrows, ncols);
	printf("==== red layer ====\n");
	printf("min = %u\n", matrix::min2d(rmat));
	printf("max = %u\n", matrix::max2d(rmat));
	printf("mean = %f\n", matrix::mean2d(rmat));
	printf("stdev = %f\n", matrix::stdev2d(rmat,true));
	printf("==== green layer ====\n");
	printf("min = %u\n", matrix::min2d(gmat));
	printf("max = %u\n", matrix::max2d(gmat));
	printf("mean = %f\n", matrix::mean2d(gmat));
	printf("stdev = %f\n", matrix::stdev2d(gmat,true));
	printf("==== blue layer ====\n");
	printf("min = %u\n", matrix::min2d(bmat));
	printf("max = %u\n", matrix::max2d(bmat));
	printf("mean = %f\n", matrix::mean2d(bmat));
	printf("stdev = %f\n", matrix::stdev2d(bmat,true));

	return EXIT_SUCCESS;
}
