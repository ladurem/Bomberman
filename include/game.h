/*
 * game.h
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent Reveillere
 */

#ifndef GAME_H_
#define GAME_H_

#include "../include/constant.h"
#include "../include/misc.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/level.h"

typedef struct s_game * t_game;

// Create a new game
extern t_game game_new();

//
extern void game_free(t_game game);

// Return the player of the current game
extern t_player game_get_player(t_game game);

// Return the current level
extern t_level game_get_curr_level(t_game game);

// Display the game of the screen
extern void game_display(t_game game, SDL_Surface *screen);

// update
extern int game_update(t_game game);

// Remove lifes when the player is on a monster
extern void monster_player_life(t_game game);

//Save Game
extern void save_game(t_game game);

//Load Game
extern void load_game(t_game game);

extern void game_change_map(t_game game);
extern void put_menu_game(t_game game);
extern void remove_menu_game(t_game game);
extern int return_menu_game(t_game game);
extern void menu_display(t_game game, SDL_Surface* screen);
#endif /* GAME_H_ */
