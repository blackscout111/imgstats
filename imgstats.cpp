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
	gStyle->SetOptStat(1);			// Show/Remove the stats box

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

	// Initialize ROOT
	initROOT("imgstats");

    // Histogram criteria
    TH1F	*rhist = NULL,
			*ghist = NULL,
			*bhist = NULL;

	// Canvases
	TCanvas *rcan = new TCanvas("rcan");
	TCanvas *gcan = new TCanvas("gcan");
	TCanvas *bcan = new TCanvas("bcan");

    // Make the histograms
    rhist = new TH1F("rhist", "Red Layer", 256, 0, 255);
    rhist->GetXaxis()->SetTitle("Pixel Intensity");
	rhist->GetYaxis()->SetTitle("# of Pixels");
    ghist = new TH1F("ghist", "Green Layer", 256, 0, 255);
    ghist->GetXaxis()->SetTitle("Pixel Intensity");
	ghist->GetYaxis()->SetTitle("# of Pixels");
    bhist = new TH1F("bhist", "Blue Layer", 256, 0, 255);
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
	ghist->SetLineColor(kGreen);
	bhist->SetLineColor(kBlue);
	rcan->cd();
    rhist->Draw("");
	gcan->cd();
    ghist->Draw("");
	bcan->cd();
    bhist->Draw("");

	// Program will pause at this next line until you go File->Exit from the X11 screen
	printf("In the X11 window...\n go to File-->\"Close Canvas\" to close\n");
	gApplication->Run(kTRUE);

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
	
	// Display the histograms
	dispImgStats(image);

	// Free the image from memory
	printf("freeing image memory... ");
	delete image;
	printf("done\n");

	return EXIT_SUCCESS;
}
