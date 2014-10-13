/*
 * game.c
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent R�veill�re
 */

#include <assert.h>
#include <time.h>

#include "../include/game.h"
#include "../include/map.h"
#include "../include/bomb.h"
#include "../include/player.h"
#include "../include/misc.h"
#include "../include/level.h"
#include "../include/monster.h"
#include "../include/level.h"

 struct s_game {
	t_level curr_level; // current level
	t_player player;
	int game_paused;
	int menu;
	int finished;
	int level;

	SDL_Surface * number[10];
	SDL_Surface * banner_life;
	SDL_Surface * banner_bomb;
	SDL_Surface * banner_range;
	SDL_Surface * banner_line;
	SDL_Surface * banner_key;
	SDL_Surface * banner_pause;
	SDL_Surface * banner_flag;
	SDL_Surface * menu_back_default;
	SDL_Surface * menu_back_0;
	SDL_Surface * menu_back_1;
	SDL_Surface * menu_back_2;
	SDL_Surface * menu_back_3;
	SDL_Surface * menu_end_default;
	SDL_Surface * menu_end_exit;
	SDL_Surface * menu_end_victory;
	SDL_Surface * menu_game_over;
};

static struct s_game the_game;

int etat_menu = 0; // This value is used to select the element in the menus.

t_game game_new(void) {
	srand(time(NULL ));
	the_game.level = 0;
	the_game.curr_level = level_get_level(0); // get maps of the first level
	// At the beginning, the game is not paused
	the_game.player = player_init(0, 0, 50, 50); // For defaut there is 50 bombs
	the_game.finished = 0;
	the_game.menu = 0;
	/* load banner's imgs in memory */
	the_game.number[0] = load_image(IMG_BANNER_0);
	the_game.number[1] = load_image(IMG_BANNER_1);
	the_game.number[2] = load_image(IMG_BANNER_2);
	the_game.number[3] = load_image(IMG_BANNER_3);
	the_game.number[4] = load_image(IMG_BANNER_4);
	the_game.number[5] = load_image(IMG_BANNER_5);
	the_game.number[6] = load_image(IMG_BANNER_6);
	the_game.number[7] = load_image(IMG_BANNER_7);
	the_game.number[8] = load_image(IMG_BANNER_8);
	the_game.number[9] = load_image(IMG_BANNER_9);
	the_game.banner_life = load_image(IMG_BANNER_LIFE);
	the_game.banner_bomb = load_image(IMG_BANNER_BOMB);
	the_game.banner_range = load_image(IMG_BANNER_RANGE);
	the_game.banner_line = load_image(IMG_BANNER_LINE);
	the_game.banner_key = load_image(IMG_BANNER_KEY);
	the_game.banner_pause = load_image(IMG_BANNER_PAUSE);
	the_game.banner_flag = load_image(IMG_FLAG);
	the_game.menu_back_default = load_image(IMG_MENU_BACK_DEFAULT);
	the_game.menu_back_0 = load_image(IMG_MENU_BACK_0);
	the_game.menu_back_1 = load_image(IMG_MENU_BACK_1);
	the_game.menu_back_2 = load_image(IMG_MENU_BACK_2);
	the_game.menu_back_3 = load_image(IMG_MENU_BACK_3);
	the_game.menu_end_default = load_image(IMG_END_DEFAULT);
	the_game.menu_end_exit = load_image(IMG_END_EXIT);
	the_game.menu_end_victory = load_image(IMG_END_VICTORY);
	the_game.menu_game_over = load_image(IMG_GAME_OVER);
	the_game.game_paused = 1;
	return &the_game;
}

void game_free(t_game game) {
	assert(game);
	player_free(game->player);
	level_free(game->curr_level);
}

t_player game_get_player(t_game game) {
	assert(game);
	return game->player;
}
void remove_game_pause(t_game game) {
	assert(game);
	game->game_paused = 1;
}
void put_game_pause(t_game game) {
	assert(game);
	game->game_paused = 0;
}
t_level game_get_curr_level(t_game game) {
	return game->curr_level;
}
void game_banner_display(t_game game, SDL_Surface* screen) {
	assert(game);
	assert(screen);
	t_map map = level_get_curr_map(game_get_curr_level(game));
	SDL_Rect place;

	int i;
	place.y = (map_get_height(map)) * SIZE_BLOC;
	for (i = 0; i < map_get_width(map); i++) {
		place.x = i * SIZE_BLOC;
		SDL_BlitSurface(game->banner_line, NULL, screen, &place);
	}

	place.y = (map_get_height(map) * SIZE_BLOC) + SIZE_LINE;

	int white_bloc = ((map_get_width(map) * SIZE_BLOC) - 6 * SIZE_BLOC) / 5;
	place.x = white_bloc;
	SDL_BlitSurface(game->banner_life, NULL, screen, &place);

	if (player_get_key(game_get_player(game),
			level_get_curr_map_number(game->curr_level))) { //player have a key ?
		place.x = 0;
	SDL_BlitSurface(game->banner_key, NULL, screen, &place);

}

place.x = white_bloc + SIZE_BLOC;

	if (player_get_life(game_get_player(game)) == 0) { //Put Game Over if player is dead
		put_game_pause(game);
		game->finished = 1;
	}
	//The next lines are used to print the number of lifes in the banner
	if (player_get_life(game_get_player(game)) >= 0 // less than 10 bombs
		&& player_get_life(game_get_player(game)) < 10)
		SDL_BlitSurface(game->number[player_get_life(game_get_player(game))],
			NULL, screen, &place);
	if (player_get_life(game_get_player(game)) >= 10) { //more than 10 bombs
		SDL_BlitSurface(
			game->number[player_get_life(game_get_player(game)) / 10], NULL,
			screen, &place);
		place.x = white_bloc + 2 * SIZE_BLOC;
		SDL_BlitSurface(
			game->number[player_get_life(game_get_player(game))
				- (player_get_life(game_get_player(game)) / 10) * 10],
			NULL, screen, &place);
	}

	place.x = 2 * white_bloc + 2 * SIZE_BLOC;
	SDL_BlitSurface(game->banner_bomb, NULL, screen, &place);
	place.x = 2 * white_bloc + 3 * SIZE_BLOC;

	if (player_get_nb_bomb(game_get_player(game)) >= 0
		&& player_get_nb_bomb(game_get_player(game)) < 10)
		SDL_BlitSurface(game->number[player_get_nb_bomb(game_get_player(game))],
			NULL, screen, &place);
	if (player_get_nb_bomb(game_get_player(game)) >= 0
		&& player_get_nb_bomb(game_get_player(game)) >= 10) {
		SDL_BlitSurface(
			game->number[player_get_nb_bomb(game_get_player(game)) / 10],
			NULL, screen, &place);
	place.x = 2 * white_bloc + 4 * SIZE_BLOC;
	SDL_BlitSurface(
		game->number[player_get_nb_bomb(game_get_player(game))
			- (player_get_nb_bomb(game_get_player(game)) / 10) * 10],
		NULL, screen, &place);
}
place.x = 3 * white_bloc + 4 * SIZE_BLOC;
SDL_BlitSurface(game->banner_range, NULL, screen, &place);
place.x = 3 * white_bloc + 5 * SIZE_BLOC;

	SDL_BlitSurface(game->number[bomb_range], NULL, screen, &place); //Default bombrange

	place.x = 4 * white_bloc + 5 * SIZE_BLOC;
	SDL_BlitSurface(game->banner_flag, NULL, screen, &place); //level
	place.x = 4 * white_bloc + 6 * SIZE_BLOC;
	SDL_BlitSurface(game->number[game->level], NULL, screen, &place); //level
}

void put_menu_game(t_game game) {
	assert(game);
	game->menu = 1;
}
void remove_menu_game(t_game game) {
	assert(game);
	game->menu = 0;
	game->game_paused = 1; // remove the pause
	etat_menu = 0; //put the selector at the top
}
int return_menu_game(t_game game) {
	assert(game);
	return game->menu;
}

void game_display(t_game game, SDL_Surface* screen) {
	assert(game);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
	game_banner_display(game, screen);
	level_display(game_get_curr_level(game), screen);
	player_display(game->player, screen);
	if (game->game_paused == 0) {
		SDL_Rect place;
		place.x = 0;
		place.y = 0;
		SDL_BlitSurface(game->banner_pause, NULL, screen, &place);
	}
	menu_display(game, screen);
	SDL_Flip(screen); // SDL_Flip -- swaps screen buffers -- update
}

void menu_display(t_game game, SDL_Surface* screen) {
		assert(game);
	if (game->finished == 1) {
		SDL_Rect place;
		place.x = 0;
		place.y = 0;
		if (player_get_life(game->player) == 0)
			SDL_BlitSurface(game->menu_game_over, NULL, screen, &place);
		else
			SDL_BlitSurface(game->menu_end_victory, NULL, screen, &place);

		t_map map = level_get_curr_map(game_get_curr_level(game));
		place.y = SIZE_BLOC * map_get_height(map) / 2;
		SDL_BlitSurface(game->menu_end_default, NULL, screen, &place);

		if (etat_menu == 0) {
			SDL_BlitSurface(game->menu_end_default, NULL, screen, &place);
		} else if (etat_menu == 1) {
			SDL_BlitSurface(game->menu_end_exit, NULL, screen, &place);

		}
	} else {
		if (game->menu == 1) {
			game->game_paused = 0;
			SDL_Rect place;
			place.x = 0;
			place.y = 0;
			SDL_BlitSurface(game->menu_back_default, NULL, screen, &place); //Background

			if (etat_menu == 0) {
				SDL_BlitSurface(game->menu_back_default, NULL, screen, &place); //Background
			} else if (etat_menu == 1){
		SDL_BlitSurface(game->menu_back_0, NULL, screen, &place); //Background

	} 

	else if (etat_menu == 2) {
				SDL_BlitSurface(game->menu_back_1, NULL, screen, &place); //Background

			} else if (etat_menu == 3) {
				SDL_BlitSurface(game->menu_back_2, NULL, screen, &place); //Background

			} else if (etat_menu == 4) {
				SDL_BlitSurface(game->menu_back_3, NULL, screen, &place); //Background

			}

		}
	}
}
int menu_action(t_game game) { // make action of the menu
	switch (etat_menu) {
	case 0: //switch off the menu and stop the pause
	remove_menu_game(game);
	break;
	case 1:// Start a new game
	game_free(game);
	game_new();
	break;
	case 2:
	save_game(game);
	break;
	case 3:
	game_free(game);
	load_game(game);
	break;
	case 4: // Quit the game
	return 1;
	break;
}
	etat_menu = 0; //reset the value of the menu
	return 0;
}

int end_action(t_game game) { //make action of the end menu
	switch (etat_menu) {
		case 0:
		game_free(game);
		game_new();
		break;
	case 1: //quit the game
	default:
	return 1;
	break;
}
	etat_menu = 0; //reset the value of the menu
	return 0;
}

uint input_update(t_game game) {
	SDL_Event event;
	t_player player = game_get_player(game);
	t_map map = level_get_curr_map(game_get_curr_level(game));
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
			return 1;
			case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
				if (game->menu == 0) { // Put the menu on the screen and pause the game
					put_menu_game(game);
				} else
					remove_menu_game(game); // remove the menu on the screen and stop the pause	
					break;
					case SDLK_UP:
					if (game->game_paused == 1) {
						player_set_current_way(player, NORTH);
						player_move(player, map);
					} else if (game->menu == 1) {
						if (etat_menu >= 0)
							etat_menu--;
						if (etat_menu == -1)
							etat_menu = 4;
					} else if (game->finished == 1) {
						if (etat_menu >= 0)
							etat_menu--;
						if (etat_menu == -1)
							etat_menu = 1;
					}
					break;
					case SDLK_DOWN:
					if (game->game_paused == 1) {
						player_set_current_way(player, SOUTH);
						player_move(player, map);
					} else if (game->menu == 1) {
						if (etat_menu <= 4)
							etat_menu++;
						if (etat_menu == 5)
							etat_menu = 0;
					} else if (game->finished == 1) {
						if (etat_menu <= 1)
							etat_menu++;
						if (etat_menu == 2)
							etat_menu = 0;
					}
					break;
					case SDLK_RIGHT:
					if (game->game_paused == 1) {
						player_set_current_way(player, EAST);
						player_move(player, map);
					}
					break;
					case SDLK_LEFT:
					if (game->game_paused == 1) {
						player_set_current_way(player, WEST);
						player_move(player, map);
					}
					break;
					case SDLK_SPACE:
					if (game->game_paused == 1) {
						if (map_get_cell_type(
							level_get_curr_map(game_get_curr_level(game)),
							player_get_x(game_get_player(game)),
							player_get_y(game_get_player(game))) != CELL_DOOR) {
							add_new_bomb(
								level_get_curr_map(game_get_curr_level(game)),
								game_get_player(game));
					}
				}
				break;
				case SDLK_RETURN:
				if (game->menu == 1) { // menu actived
					return menu_action(game);
				} else if (game->finished == 1) { //end menu shown
					return end_action(game);
				}
				break;
				case SDLK_p:
				if (game->game_paused == 0) // Pause actived
					remove_game_pause(game);
				else
					put_game_pause(game);
				break;
			case SDLK_q: // if q is pressed, put the menu on "quit the game"
			put_menu_game(game);
			etat_menu = 3;
			break;
			case SDLK_s:
			put_menu_game(game);
			etat_menu = 1;
			break;
			default:
			break;
		}

		break;
	}
}
return 0;
}

int game_update(t_game game) {
	if (input_update(game) == 1) {
		return 1; // exit game

	}
	if (game->game_paused == 1) {
		update_all_bombs(level_get_curr_map(game_get_curr_level(game))); // Update list of bomb
		update_all_monster(level_get_curr_map(game_get_curr_level(game))); // Update list of monster
		monster_player_life(game);
		game_change_map(game);
	}
	return 0;
}

void monster_player_life(t_game game) {
	Uint32 time = player_get_time_death(game->player);
	int player_x = player_get_x(game->player);
	int player_y = player_get_y(game->player);
	t_cell_type cell = map_get_cell_type(
		level_get_curr_map(game_get_curr_level(game)), player_x, player_y);
	if ((SDL_GetTicks() - time) > 1000 && cell == CELL_MONSTER) {
		player_remove_life(game->player);
		player_set_time_death(game->player, SDL_GetTicks());
	}

}

void game_change_map(t_game game) {
	int player_x = player_get_x(game->player);
	int player_y = player_get_y(game->player);
	t_cell_type cell = map_get_cell_type(
		level_get_curr_map(game_get_curr_level(game)), player_x, player_y);
	if (cell == CELL_DOOR) {
		t_compose_type cell_detailled = map_get_cell_type_detailled(
			level_get_curr_map(game_get_curr_level(game)), player_x,
			player_y);
		if (cell_detailled >> 6 == UP) {
			if (((cell_detailled >> 4 & 4) == CLOSE
				&& player_get_key(game->player,
					level_get_curr_map_number(game->curr_level)) == 1)
				|| (cell_detailled >> 4 & 4) == OPEN) {
				level_map_up(game->curr_level);
			player_move_east(game->player);
		}
	} else {
		level_map_down(game->curr_level);
		player_move_east(game->player);
	}
}
if (cell == CELL_LEVEL) {
	if (player_get_key(game->player, level_get_curr_map_number(game->curr_level))
		== 1) {
			//Player(0,0)
		player_set_x(game->player, 0);
	player_set_y(game->player, 0);
	for (int i = 0; i < 3; i++) {
		player_set_key(game->player, i, 0);
	}
	level_free(game->curr_level);
	game->level++;
			game->curr_level = level_get_level(game->level); // Set the level up
		}

	}
	if (cell == CELL_BOMBERWOMAN) { // same action as previously
		put_game_pause(game);
		game->finished = 1;

	}
}

void save_game(t_game game) {
	char path[] = "./save/save";
	FILE* file;
	if ((file = fopen(path, "w")) == NULL ) {
		printf("Impossible d'écrire sur le fichier de sauvegarde");
	}
	fprintf(file, "%d:%d:%d:%d:%d \n", player_get_x(game->player),
		player_get_y(game->player), player_get_life(game->player),
		player_get_nb_bomb(game->player), bomb_range);
	fprintf(file, "key:%d:%d:%d \n", player_get_key(game->player, 0),
		player_get_key(game->player, 1), player_get_key(game->player, 2));
	fprintf(file, "level:%d,\n", game->level);
	save_level(file, game->curr_level);
	fclose(file);
}

void load_game(t_game game) {
	srand(time(NULL ));

	char path[] = "./save/save";
	FILE* file;
	if ((file = fopen(path, "r")) == NULL ) {
		printf("Impossible d'ouvrir sur le fichier de sauvegarde");
	}
	int player_x, player_y, player_nb_lifes, player_nb_bombs, range,
	current_level;
	int player_key[3];
	fscanf(file, "%d:%d:%d:%d:%d \n", &player_x, &player_y, &player_nb_lifes,
		&player_nb_bombs, &range);
	fscanf(file, "key:%d:%d:%d \n", &player_key[0], &player_key[1],
		&player_key[2]);

	fscanf(file, "level:%d,\n", &current_level);
	the_game.level = current_level;

	the_game.menu = 0;
	bomb_range = range;
	the_game.player = player_init(player_x, player_y, player_nb_bombs,
		player_nb_lifes);
	for (int i = 0; i < 3; i++) {
		player_set_key(game->player, i, player_key[i]);
	}
	the_game.curr_level = load_level(file, the_game.player, NB_MAPS(the_game.level));

	fclose(file);

}
