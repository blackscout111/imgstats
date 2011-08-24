/* Filename: imgstats.cpp
 * Description: This is a simple program that calculates image layer statistics.
 * Input Parameters: [Image File Name]
 * Author: Bryan A. Clifford
 * Last Updated: 08.24.2011
 */


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#include <Magick++.h>

#include <TROOT.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TMath.h>
#include <TRandom.h>
#include <TCanvas.h>
#include <TGraph.h>

using namespace std;

//_____________________________________________________________________________
// This function starts ROOT. The pointer returned should be used to stop the
// application and also be deleted before program completion. This is don via
// the "Terminate" method or by calling the "Run" method with a value of "kTRUE"
// as the input parameter.
void initROOT(const char* appClassName)
{
	// Initialize the root application
	Int_t argv = 0;
	char** argc = NULL;
	new TApplication(appClassName, &argv, argc, NULL, 0);

	//======= Set the style of plots ============
	// Set the canvas style used
	gROOT->SetStyle("Plain");		// Start using the plain style
	gStyle->SetPalette(1);			// Get access to a fancy color palette

	// Display Histogram Statistics Box
	// The type of information printed in the histogram statistics box
	//  can be selected via the parameter mode.
	//
	//	Example: gStyle->SetOptStat("ne");  Display name and number of entries
	//    k  kurtosis printed
	//    K  kurtosis and kurtosis error printed
	//    s  skewness printed
	//    S  skewness and skewness error printed
	//    i  integral of bins printed
	//    o  number of overflows printed
	//    u  number of underflows printed
	//    r  rms printed
	//    R  rms and rms error printed
	//    m  mean value printed
	//    M  mean and mean error values printed
	//    e  number of entries printed
	//    n  name of histogram is printed
	gStyle->SetOptStat("nemrks");

	// Set some title properties
	gStyle->SetTitleW(0.5);
	gStyle->SetTitleH(0.07);
	gStyle->SetTitleX(0.25);
	gStyle->SetTitleBorderSize(0);


	gROOT->ForceStyle();
    //============================================
}


//_____________________________________________________________________________
void dispImgStats(const Magick::Image* image)
{
	// No NULLs
	assert(image);

	// Initialize ROOT
	initROOT("imgstats");

    // Histogram criteria
    TH1F	*rhist = NULL,
			*ghist = NULL,
			*bhist = NULL;

	// Canvases
	TCanvas *rcan = new TCanvas("rcan", "imgstats - Red Layer Statistics");
	TCanvas *gcan = new TCanvas("gcan", "imgstats - Green Layer Statistics");
	TCanvas *bcan = new TCanvas("bcan", "imgstats - Blue Layer Statistics");

    // Make the histograms
    rhist = new TH1F("Red Layer", "Red Layer Statistics", 256, -0.5, 255.5);
    rhist->GetXaxis()->SetTitle("Pixel Intensity");
	rhist->GetYaxis()->SetTitle("# of Pixels");
    ghist = new TH1F("Green Layer", "Green Layer Statistics", 256, -0.5, 255.5);
    ghist->GetXaxis()->SetTitle("Pixel Intensity");
	ghist->GetYaxis()->SetTitle("# of Pixels");
    bhist = new TH1F("Blue Layer", "Blue Layer Statistics", 256, -0.5, 255.5);
    bhist->GetXaxis()->SetTitle("Pixel Intensity");
	bhist->GetYaxis()->SetTitle("# of Pixels");

    // Fill the histograms
	// Image dimensions
	printf("getting image pixel data... ");
	size_t	nrows = image->rows(), ncols = image->columns();
	Magick::Color tmpColor;

	for (size_t row = 0; row < nrows; ++row)
	{
		for (size_t col = 0; col < ncols; ++col)
		{
			tmpColor = image->pixelColor(row,col);
			rhist->Fill(tmpColor.redQuantum());
			ghist->Fill(tmpColor.greenQuantum());
			bhist->Fill(tmpColor.blueQuantum());
		}
	}
	printf("done\n");

    // Draw the histograms
	rhist->SetLineColor(kRed);
	rhist->SetFillColor(kRed);
	ghist->SetLineColor(kGreen);
	ghist->SetFillColor(kGreen);
	bhist->SetLineColor(kBlue);
	bhist->SetFillColor(kBlue);
	rcan->cd();
	rhist->Draw();
	gcan->cd();
	ghist->Draw();
	bcan->cd();
	bhist->Draw();

	// Program will pause at this next line until you go File->Exit from the X11 screen
	printf("In an X11 window go to File-->\"Close Canvas\" to close\n");
	gApplication->Run(kTRUE);

	// Delete the canvases
	delete rcan;
	delete gcan;
	delete bcan;

    // Delete the histograms
    delete rhist;
    delete ghist;
    delete bhist;
}

//_____________________________________________________________________________
int main(int argc, char **argv)
{
	Magick::InitializeMagick(*argv);

	// Construct the image object. Separating image construction from the
	// the read operation ensures that a failure to read the image file
	// doesn't render the image object useless.
	Magick::Image *image = NULL;
	
	// We're using 8 bit colors
	assert(MaxRGB == 255);

	printf("loading image... ");
	try 
	{
		// Read a file into image object
		if (argc == 2)
		{
			image = new Magick::Image;
			image->read(argv[1]);
		}
		else
		{
			printf("Incorrect number of input parameters.\n");
			printf("Usage:\n\n\t./imgstats [FILE NAME]\n");
		}
	}
	catch(Magick::Exception &error_)
	{
		cout << "Caught exception: " << error_.what() << endl;
		return EXIT_FAILURE;
	}
	printf("done\n");
	
	// Display the histograms
	if (image)
	{
		dispImgStats(image);

		// Free the image from memory
		printf("freeing image memory... ");
		delete image;
		printf("done\n");
	}

	return EXIT_SUCCESS;
}
