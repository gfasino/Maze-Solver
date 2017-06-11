CC = g++

SRCS = cvgui.cc graph.cc matrix.cc node.cc visiblematrix.cc dataman.cc main.cc point.cc

CFLAGS= $(shell root-config --cflags)

PROG = mazesolver

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV) -lpthread

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
