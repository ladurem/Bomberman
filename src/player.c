/*
 * player.c
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent Reveillere
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include "SDL.h"
#include "SDL_image.h"

#include "../include/game.h"
#include "../include/misc.h"
#include "../include/bomb.h"

struct s_player {
	int x, y;
	SDL_Surface * directed_img[4];
	enum e_way current_way;
	int nb_bomb;
	int life;
	int* get_key;
	Uint32 time_of_last_death;
};

t_player player_init(int x, int y, int bomb_number, int nb_life) {
	t_player player = malloc(sizeof(*player));
	player->get_key = malloc(4 * sizeof(int)); // 3 is the max of keys necessary for all the levels
	if (!player)
		error("Memory error");

	player->directed_img[WEST] = load_image(IMG_PLAYER_LEFT);
	player->directed_img[EAST] = load_image(IMG_PLAYER_RIGHT);
	player->directed_img[NORTH] = load_image(IMG_PLAYER_UP);
	player->directed_img[SOUTH] = load_image(IMG_PLAYER_DOWN);

	player->x = x;
	player->y = y;

	player->current_way = SOUTH;
	player->nb_bomb = bomb_number;
	player->life = nb_life; //Nomber of life
	for (int i = 0; i < 4; i++) {
		player->get_key[i] = 0; // at the begin player did'nt have key
	}
	return player;
}

void player_free(t_player player) {
	assert(player);
	int i;
	for (i = 0; i < 4; i++)
		SDL_FreeSurface(player->directed_img[i]);

	free(player);
}

int player_get_x(t_player player) {
	assert(player);
	return player->x;
}

int player_get_y(t_player player) {
	assert(player);
	return player->y;
}

void player_set_x(t_player player, int x) {
	assert(player);
	player->x = x;
}
void player_set_y(t_player player, int y) {
	assert(player);
	player->y = y;
}
void player_set_current_way(t_player player, enum e_way way) {
	assert(player);
	player->current_way = way;
}

int player_get_nb_bomb(t_player player) {
	assert(player);
	return player->nb_bomb;
}

void player_inc_nb_bomb(t_player player) {
	assert(player);
	player->nb_bomb += 1;
}

void player_dec_nb_bomb(t_player player) {
	assert(player);
	if (player->nb_bomb != 0)
		player->nb_bomb -= 1;
}
int player_get_life(t_player player) {
	assert(player);
	return player->life;
}

void player_remove_life(t_player player) {
	assert(player);
	player->life--;
}

void player_add_life(t_player player) {
	assert(player);
	player->life++;
}

int player_get_key(t_player player, int cell) {
	return player->get_key[cell];
}

void player_set_key(t_player player, int cell, int bool) {
	player->get_key[cell] = bool;
}

static int player_move_aux(t_player player, t_map map, int x1, int y1, int x2,
		int y2) {

	if (allow_move(x1, x2, y1, y2)) // Inside the screen ?
		return 0;
	switch (map_get_cell_type(map, x1, y1)) {
	case CELL_BOMBERWOMAN:
		break;
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_CASE:
		if (allow_case_move(x1, x2, y1, y2) == 0
				&& map_get_cell_type(map, x2, y2) == CELL_EMPTY) {
			map_set_cell_type(map, x1, y1, CELL_EMPTY);
			map_set_cell_type(map, x2, y2, CELL_CASE);
			return 1;
		} else
			return 0;
		break;

	case CELL_BONUS:
		player_get_bonus(player, map, x1, y1);
		return 1;
		break;

	case CELL_EMPTY:
		return 1;
		break;

	case CELL_BOMB:
		return 0;
		break;

	case CELL_KEY:
		player->get_key[get_map_number(map)] = 1;
		map_set_cell_type(map, x1, y1, CELL_EMPTY);
		break;

	case CELL_DOOR:
		return 1;
		break;

	case CELL_GOAL:
		return 0;
		break;

	case CELL_MONSTER:
		return 1;
		break;

	case CELL_PLAYER:
		break;

	case CELL_LEVEL:
		return 1;
		break;

	}
	return 1;
}

int player_move(t_player player, t_map map) {
	int x = player->x;
	int y = player->y;
	int move = 0;
	switch (player->current_way) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1, x, y - 2)) {
			player->y--;
			move = 1;
		}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1, x, y + 2)) {
			player->y++;
			move = 1;
		}
		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y, x - 2, y)) {
			player->x--;
			move = 1;
		}
		break;

	case EAST:
		if (player_move_aux(player, map, x + 1, y, x + 2, y)) {
			player->x++;
			move = 1;
		}
		break;
	}
	return move;
}

void player_display(t_player player, SDL_Surface *screen) {
	assert(player);
	assert(player->directed_img[player->current_way]);
	assert(screen);

	SDL_Rect place;
	place.x = player->x * SIZE_BLOC;
	place.y = player->y * SIZE_BLOC;

	SDL_BlitSurface(player->directed_img[player->current_way], NULL, screen,
			&place);
}

void player_get_bonus(t_player player, t_map map, int x, int y) {
	t_cell_type cell_type_detailled = map_get_cell_type_detailled(map, x, y);
	switch (cell_type_detailled >> 4) {
	case BONUS_BOMB_RANGE_INC:
		bomb_range++;
		break;
	case BONUS_BOMB_RANGE_DEC:
		if (bomb_range > 1)
			bomb_range--;
		break;
	case BONUS_BOMB_NB_INC:
		player_inc_nb_bomb(player);
		break;
	case BONUS_BOMB_NB_DEC:
		player_dec_nb_bomb(player);
		break;
	case BONUS_LIFE:
		player_add_life(player);
		break;
	}
	map_set_cell_type(map, x, y, CELL_EMPTY);
}

void player_move_east(t_player player) {
	assert(player);
	player->x++;
}

void player_set_time_death(t_player player, Uint32 time_of_death) {
	assert(player);
	player->time_of_last_death = time_of_death;
}

Uint32 player_get_time_death(t_player player) {
	assert(player);
	return player->time_of_last_death;
}

