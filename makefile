CC=g++
CFLAGS=-lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
IDIR=include

all:
	$(CC) $(CFLAGS) src/main.cpp -I$(IDIR) -o build/oballtus
