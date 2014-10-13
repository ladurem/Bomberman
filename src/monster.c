/*
 * monster.c
 *
 *  Created on: 23 Mars 2013
 *      Author: mladure
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
#include "../include/monster.h"
#include <time.h> //For rand() 

 struct s_monster {
 	int x, y;
 	enum e_way current_way;
 	Uint32 last_mouvement;
 	int nb_life;

 };

 t_monster create_new_monster(t_map map, int x, int y) {

 	t_monster monster = malloc(sizeof(*monster));
 	if (!monster)
 		error("Memory error");
 	monster->current_way = SOUTH;
 	monster->last_mouvement = SDL_GetTicks();
// 	int x=rand()%map_get_width(map); Generate a monster where the place is free
// 	int y=rand()%map_get_height(map);
// 	while(map_get_cell_type(map, x, y)==CELL_SCENERY || map_get_cell_type(map, x, y)==CELL_DOOR || map_get_cell_type(map, x, y)==CELL_KEY){//Tant que le monstre est un cell_scenary on le deplace
// 		x=rand()%map_get_width(map);
// 		y=rand()%map_get_height(map);
// 	}
 	monster->x = x;
 	monster->y = y;
 	monster->nb_life = 1; 
	map_set_cell_type(map, monster->x, monster->y, CELL_MONSTER_SOUTH); //put the monster inside the grid
	return monster;
}
int monster_update(t_monster monster, t_map map) {
	int random;
	assert(map);
	if (monster == NULL )
		return 1;

	if (monster->nb_life == 0) {
		map_set_cell_type(map, monster->x, monster->y, CELL_EMPTY);
		return 0;
	}

	if ((SDL_GetTicks() - monster->last_mouvement) > BASE_TIME) {
		monster->last_mouvement = SDL_GetTicks();
		random = rand() % 4;
		int x = monster->x;
		int y = monster->y;
		switch (random) {
			case 0:
			if (monster_move_aux(monster, map, x, y - 1, x, y - 2)) {
				map_set_cell_type(map, monster->x, monster->y, CELL_EMPTY);
				monster->y--;

				map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_NORTH); 
			} else
			map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_NORTH);
			break;

			case 1:
			if (monster_move_aux(monster, map, x, y + 1, x, y + 2)) {
				map_set_cell_type(map, monster->x, monster->y, CELL_EMPTY);
				monster->y++;
				map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_SOUTH); 

			} else
			map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_SOUTH);
			break;

			case 2:
			if (monster_move_aux(monster, map, x - 1, y, x - 2, y)) {
				map_set_cell_type(map, monster->x, monster->y, CELL_EMPTY);
				monster->x--;
				map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_WEST);
			} else
			map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_WEST);
			break;

			case 3:
			if (monster_move_aux(monster, map, x + 1, y, x + 2, y)) {
				map_set_cell_type(map, monster->x, monster->y, CELL_EMPTY);
				monster->x++;
				map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_EAST);
			} else
			map_set_cell_type(map, monster->x, monster->y,CELL_MONSTER_EAST);
			break;
		}
	}
	return 1; //if the return is 0, delete the monster
}

int monsterupdate(void * elt, void * elm) {
	int result = monster_update((t_monster) elt, (t_map) elm);
	return result;
}

void update_all_monster(t_map map) {
	map_set_monster(map,
		list_execute(map_get_monster(map), map, monsterupdate));
}

void add_new_monster(t_map map, int x, int y) {
	list list = map_get_monster(map);
	assert(list);
	list = list_add(list, create_new_monster(map, x, y)); // add the monster
	map_set_monster(map, list);
}

int monster_move_aux(t_monster monster, t_map map, int x1, int y1, int x2,
	int y2) {

	if (allow_move(x1, x2, y1, y2)) // inside the screen?
		return 0;
	switch (map_get_cell_type(map, x1, y1)) {
		case CELL_SCENERY:
		return 0;
		break;
		case CELL_BOMBERWOMAN:
		return 0;
		break;
		case CELL_CASE:
		return 0;
		break;
		case CELL_EMPTY:
		return 1;
		break;
		case CELL_BOMB:
		return 0;
		break;
		case CELL_KEY:
		return 0;
		break;
		case CELL_DOOR:
		return 0;
		break;
		case CELL_GOAL:
		return 0;
		break;
		case CELL_MONSTER:
		return 0;
		break;
		case CELL_BONUS:
		return 0;
		break;
		case CELL_PLAYER:
		return 1;
		break;
		case CELL_LEVEL:
		return 0;
		break;

	}
	return 1;
}

void monster_dec_nb_life(t_monster monster) {
	assert(monster);
	monster->nb_life--;
}

t_monster get_monster_from_map(t_map map, int x, int y) {
	assert(map);
	list list_monsters = map_get_monster(map);
	assert(list_monsters);
	t_monster monster = list_get_element(list_monsters);
	assert(monster);
	while (list_monsters != NULL && !(monster->x == x && monster->y == y)) {
		list_monsters = list_get_next(list_monsters);
		if (list_monsters == NULL )
			break;
		monster = list_get_element(list_monsters);
		assert(monster);
	}
	return monster;

}

