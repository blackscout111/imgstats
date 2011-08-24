################################################################################
# README for imgstats
################################################################################
#===============================================================================
Install Xserver-Xorg
#===============================================================================
- You should have the following packages installed:
	
	xorg
	xorg-dev
	xfonts-100dpi	# These fonts should be installed to "/usr/share/fonts/X11"
	xfonts-75dpi

- You can get these by useing the following command:

	sudo aptitude install [PACKAGE_NAME]

- Make sure that the 100 and 75 dpi fonts are in your xserver fontpath.
- You can check the font path wiht the following command:

	xset -q

- You can add both of those fonts to the path with the following commands:

	xset +fp /usr/share/fonts/X11/100dpi
	xset +fp /usr/share/fonts/X11/75dpi


#===============================================================================
Install Graphics Magick
(on ubuntu 11.04)
#===============================================================================
- go to "http://sourceforge.net/projects/graphicsmagick/files/graphicsmagick/1.3.12/l"
- download "GraphicsMagick-1.3.12.tar.gz"
- extract it to "~/GraphicsMagick-1.3.12/"
- Perform the following:

	cd ~/GraphicsMagick-1.3.12/
	./configure --with-x --with-quantum-depth=8	# This will install it to "usr/local"
	make
	sudo make install
	make check (This one is optional)

# See "http://www.graphicsmagick.org/INSTALL-unix.html#optional-features" for
# instructions about the configure options
# 'with-quantum-depth=8' means that pixle sizes will be 8 bits

- DONE

#===============================================================================
Installing ROOT
#===============================================================================
- Prerequisit "optional" packages (not actually optional):

	libgsl0-dev
	libglew-dev
	libfftw3-dev

- You can get these by useing the following command:

	sudo aptitude install [PACKAGE_NAME]

- Once the prequisit packages are installed go to
	
	"http://root.cern.ch/drupal/content/production-version-530"

- Scroll down near the bottom and download "ROOT 5.30/01 complete source tree"
- Extract the file to "~/root"
- Perform the following actions:

    cd ~/root
    ./configure --help > configure_help # This outputs the configuration
										# help/settings/arguments to a file.
    ./configure --enable-gdml --enable-mathmore --enable-opengl --enable-python --enable-tmva --enable-minuit2 --enable-fftw3 
    make -j # This takes a long time (  >30 min)
    . bin/thisroot.sh

- Try running ROOT by performing the following action:

    root

- If all went well root should start.  Close it with the command ".q".

- Clean up make's intermediaries.  To do this perform the following action:
    make clean

- Add the following line to your ".bashrc" file:

	export ROOTSYS="$HOME/root"
	export PYTHONPATH="$ROOTSYS/lib"
	export PATH=$PATH:"$ROOTSYS/bin"
	export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$ROOTSYS/lib"

- Open a new terminal and perform the following actions:

	source ~/.bashrc
	root

- If all went well root should start.  Close it with the command ".q".

- DONE

#===============================================================================
Building the Project
#===============================================================================
- The above instlation instructions should be followed prior to building the
  project.
- Make sure that you have the following environment variables set in order
  to compile and run this project

	LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib"
	LIBRARY_PATH="$LIBRARY_PATH:/usr/lib:/usr/local/lib"

- Perform the following action:

	make

- DONE

#===============================================================================
Using the Project
#===============================================================================
- Peform the following action:

	./imgstats.exe [IMAGE_FILE_NAME]

- The statistics will be displayed in the terminal window.
