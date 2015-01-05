CC=g++
ifeq ($(OS),Windows_NT)
	FLAGS=-lfreeglut -lopengl32 -lglu32 -m32
else
	FLAGS=-lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
endif
IDIR=include

all:
	$(CC) $(FLAGS) src/main.cpp -I$(IDIR) -o build/oballtus