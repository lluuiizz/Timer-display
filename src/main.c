#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#define WIDTH 800
#define HEIGHT 600

int main (void) {
 	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
    SDL_Window* win = 
        SDL_CreateWindow("Timer - Created by Luiz Guilherme C. Da Silva", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (win == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError()); 
        return EXIT_FAILURE;
    }

    SDL_Renderer* render = 
        SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (render == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Event event;
    bool quit = false;

    //  Font
    if (TTF_Init() == -1) {
        printf("TTF_Init(): %s\n", TTF_GetError());
        return EXIT_FAILURE;
    
    }

    TTF_Font* Cascadia = TTF_OpenFont("../font/DIGITALDREAMFATSKEW.ttf", 120);
    SDL_Color yellow = {255, 255, 0}; // 253 253 150
    SDL_Rect timer_box;
    timer_box.x = WIDTH / 2 - WIDTH / 4 - 80; 
    timer_box.y = HEIGHT / 2 - HEIGHT / 8; 
    timer_box.w = 600;
    timer_box.h = 50;

    while(!quit) {
         while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                   quit = true;
                   break;
                default: {} 
            }
        }
        time_t rawtime;
        struct tm * timeinfo;

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        char *time_str = asctime(timeinfo);
        time_str[strlen(time_str) - 1] = '\0';
        SDL_Surface* surface_timer = TTF_RenderText_Solid(Cascadia, time_str, yellow);
        SDL_Texture* timer = SDL_CreateTextureFromSurface(render, surface_timer);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
        SDL_RenderClear(render);
        SDL_RenderCopy(render, timer, NULL, &timer_box); 
        SDL_RenderPresent(render);
        SDL_RenderClear(render);
        SDL_FreeSurface(surface_timer);
        SDL_DestroyTexture(timer);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}


