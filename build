#!/usr/bin/zsh

mkdir bin
gcc -c ./src/main.c `pkg-config sdl2 --cflags` 
gcc -o ./bin/timer main.o `pkg-config sdl2 --libs` -lSDL2_ttf

rm main.o 


echo "Look the bin folder and execute timer!"
