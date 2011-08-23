################################################################################
# Makefile for imgstats test
################################################################################

#-------------------------------------------------------------------------------
# NOTE: Make sure that you have the following environment variables set in order
# to compile and run this project
#
# LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib"
# LIBRARY_PATH="$LIBRARY_PATH:/usr/lib:/usr/local/lib"
#
#-------------------------------------------------------------------------------

#===============================================================================
# Graphics Magick macros
#===============================================================================
GM_CFLAGS = $(shell GraphicsMagick++-config --cppflags --cxxflags)
GM_LIBS = $(shell GraphicsMagick++-config --ldflags)
GM_LINK_LIBS = $(shell GraphicsMagick++-config --libs)

#===============================================================================
# Standard macros
#===============================================================================

# The directory containing the source files
SRC_DIR = src

# The directory containin the include files
INC_DIR = include

# Include directories
INCLUDE_DIRS =	-I/usr/include \
		-I/usr/local/include \
		-I$(INC_DIR)

# Library directories
LIB_DIRS =	-L/usr/lib \
		-L/usr/local/lib \
		$(GM_LIBS)

# Libraries to link to
LINK_LIBS = $(GM_LINK_LIBS)

# The compiler
COMPILER = g++

# Compiler flags
CFLAGS = -Wall \
	 $(GM_CFLAGS)

# The source object files needed
#   - These objects should correspond to .cpp files in the source directory that
#     need to be included in the project.  Each of these files should have a
#     corresponding header file in the include directory
SRC_FILES =

# These are the objects to be made corresponding to the needed source files
SRC_OBJS = $(patsubst %.cpp, %.o, $(SRC_FILES))

# The name of the executable
EXECNAME = imgstats

# The executable
EXEC = $(EXECNAME).exe

# The object files needed by the executable
OBJS = $(EXECNAME).o $(SRC_OBJS)



#===============================================================================
# Build the executable from the object files
#===============================================================================

# Build the executable
$(EXEC) : $(OBJS)
	@echo Building the executable
	@$(COMPILER) $(CFLAGS) \
	$(OBJS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_LIBS) \
	-o $(EXEC)

# Build the main object file
#   - The source corresponding to this object should be in the same directory
#     as this makefile and should have the same name as the  executable
$(EXECNAME).o : $(EXECNAME).cpp
	@echo Building $@
	@$(COMPILER) $(CFLAGS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_LIBS) \
	-c $<

#===============================================================================
# Build all of the source object files (These should be in the source folder)
#===============================================================================

# Build the object files corresponding to the source files
$(SRC_OBJS) : %.o : $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
	@echo Building $@
	@$(COMPILER) $(CFLAGS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_LIBS) \
	-c $<

################################################################################
# Clean up the build dependencies
################################################################################
clean:
	@echo Removing the object files
	@rm -f $(OBJS)

