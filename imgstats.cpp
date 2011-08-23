#include <iostream>
#include <cstdio>
#include <cstdlib>

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

	// Construct the image object. Seperating image construction from the
	// the read operation ensures that a failure to read the image file
	// doesn't render the image object useless.
	Magick::Image image;

	matrix::matrix<unsigned char> mat(2,2);
	unsigned char val = 0;
	for (size_t i = 0; i < mat.height(); ++i)
	{
		for (size_t j = 0; j < mat.width(); ++j)
		{
			mat(i,j) = ++val;
		}
	}

	printMat(mat);
	printf("det(mat) = %f\n", matrix::det(mat));
	printf("mean2d(mat) = %f\n", matrix::mean2d(mat));
	printf("vari2d(mat) = %f\n", matrix::vari2d(mat,true));

	return EXIT_SUCCESS;
}
