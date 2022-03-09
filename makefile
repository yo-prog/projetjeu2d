game:func.o main.o
	gcc main.o func.o -o game -lSDL -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer -g
main.o:main.c
	gcc -c main.c -g
Image.o:Image.c
	gcc -c func.c -g
