/*
 * main.c
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent R�veill�re
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#include <SDL.h>
#include <SDL_image.h>

#include "../include/game.h"
#include "../include/list.h"

int main(int argc, char *argv[]) {

	SDL_Surface *screen;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		error("Can't init SDL:  %s\n", SDL_GetError());
	}

	t_game game = game_new();

	t_map map = level_get_curr_map(game_get_curr_level(game));

	SDL_WM_SetCaption(WINDOW_NAME, NULL );
	screen = SDL_SetVideoMode(SIZE_BLOC * map_get_width(map),
			SIZE_BLOC * map_get_height(map) + SIZE_BANNER + SIZE_LINE,
			WINDOW_BPP, SDL_HWSURFACE);

	if (screen == NULL ) {
		error("Can't set video mode: %s\n", SDL_GetError());
	}

	game_display(game, screen);

	int done = 0;

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	// to obtain the DEFAULT_GAME_FPS, we have to reach a loop duration of (1000 / DEFAULT_GAME_FPS) ms
	uint ideal_speed = 1000 / DEFAULT_GAME_FPS;
	Uint32 timer, execution_speed;

	// game loop
	// fixed time rate implementation
	while (!done) {

		timer = SDL_GetTicks();

		done = game_update(game);
		game_display(game, screen);

		execution_speed = SDL_GetTicks() - timer;
		if (execution_speed < ideal_speed) {
			SDL_Delay(ideal_speed - execution_speed); // we are ahead of ideal time. let's wait.
		}
	}

	game_free(game);
	SDL_FreeSurface(screen);
	SDL_Quit();

	return EXIT_SUCCESS;
}
