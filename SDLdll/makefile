NAME=SDL.dll

$(NAME):
	echo heck

make: $(SDL)
	clang++ -v main.cpp -framework Cocoa -I$(SDL)/include -L$(SDL)/lib -lSDL2 -lSDL2main

