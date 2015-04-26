CC=g++

linux:
	g++ -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm  src/main.cpp -Iinclude -o build/oballtus -std=c++0x -lfreetype

windows:
	i686-w64-mingw32-g++ src/main.cpp -lopengl32 -lglu32 -lfreeglut -m32 -Iinclude -o build/oballtus.exe -std=c++0x -static

