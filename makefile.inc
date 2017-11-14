GCC = gcc
WORKDIR = `git rev-parse --show-toplevel`
CFLAGS = -g `sdl2-config --cflags --libs`
OBJ_DIR = $(WORKDIR)/build

%.o: %.cpp
	@ $(GCC) $(CFLAGS) -c $^ -o $(OBJ_DIR)/$@

$(SUBDIRS):
	@ $(MAKE) -C $@ all

.PHONY: $(SUBDIRS) all

all: $(OBS) $(SUBDIRS)