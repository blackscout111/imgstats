////////////////////////////////////////////////////////////////////////////////
// README for imgstats
////////////////////////////////////////////////////////////////////////////////

====
Install Graphics Magick
(on ubuntu 11.04)
====

- go to "http://sourceforge.net/projects/graphicsmagick/files/graphicsmagick/1.3.12/l"
- download "GraphicsMagick-1.3.12.tar.gz"
- extract it to "~/GraphicsMagick-1.3.12/"
- Perform the following:

	cd ~/GraphicsMagick-1.3.12/
	./configure --with-quantum-depth=8	# This will install it to "usr/local"
	make
	sudo make install
	make check (This one is optional)

# See "http://www.graphicsmagick.org/INSTALL-unix.html#optional-features" for
# instructions about the configure options
# 'with-quantum-depth=8' means that pixle sizes will be 8 bits

- DONE

====
Building the Project
====

- Make sure that you have the following environment variables set in order
  to compile and run this project

	LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib"
	LIBRARY_PATH="$LIBRARY_PATH:/usr/lib:/usr/local/lib"

- Perform the following actions:

	make

- DONE

