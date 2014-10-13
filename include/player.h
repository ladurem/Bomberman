/*
 * player.h
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent R�veill�re
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "../include/constant.h"
#include "../include/map.h"

typedef struct s_player * t_player;

// Creates a new player with a given number of available bombs
extern t_player player_init(int x, int y, int bomb_number, int nb_life);
extern void player_free(t_player player);

// Returns the current position of the player
extern int player_get_x(t_player player);
extern int player_get_y(t_player player);
// Set the posotion of the player (interesting to set the player at (0,0))
extern void player_set_x(t_player player, int x);
extern void player_set_y(t_player player, int y);

// Set the direction of the next move of the player
extern void player_set_current_way(t_player player, enum e_way way);

// Set, Increase, Decrease the number of bomb that player can put
extern int player_get_nb_bomb(t_player player);
extern void player_inc_nb_bomb(t_player player);
extern void player_dec_nb_bomb(t_player player);
extern int player_get_life(t_player player); // Permet d'obtenir de nombre de vie du joueur
extern void player_remove_life(t_player player);
extern void player_add_life(t_player player);

// Load the player position from the map (unused and has to be deleted)
//extern void player_from_map(t_player player, t_map map);

// Move the player according to the current direction
extern int player_move(t_player player, t_map map);

// Display the player on the screen
extern void player_display(t_player player, SDL_Surface *screen);
// Display if the payer has a key
extern int player_get_key(t_player player, int cell);
extern void player_set_key(t_player player, int cell, int bool);

extern void player_get_bonus(t_player player, t_map map, int x, int y);

//Move player when we change the map
extern void player_move_east(t_player player);

extern void player_set_time_death(t_player player, Uint32 time_of_death);

extern Uint32 player_get_time_death(t_player player);

#endif /* PLAYER_H_ */
