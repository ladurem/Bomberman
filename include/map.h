/*
 * map.h
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent Reveillere
 */

#ifndef MAP_H_
#define MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "../include/constant.h"
#include "../include/list.h"

typedef enum {
	CELL_EMPTY = 0, CELL_GOAL,  // 1
	CELL_SCENERY, // 2
	CELL_PLAYER, // 3
	CELL_CASE,   // 4
	CELL_BONUS, // 5
	CELL_MONSTER, // 6
	CELL_BOMB, // 7
	CELL_KEY, //8
	CELL_DOOR, //9
	CELL_LEVEL, //10
	CELL_BOMBERWOMAN,//11

} t_cell_type;

typedef enum {
	BONUS_BOMB_RANGE_INC = 1,
	BONUS_BOMB_RANGE_DEC,
	BONUS_BOMB_NB_INC,
	BONUS_BOMB_NB_DEC,
	BONUS_LIFE,
	BONUS_MONSTER
} t_bonus_type;

typedef enum {
	SCENERY_STONE = 1, SCENERY_TREE, BOMB_1, BOMB_2, BOMB_3, BOMB_4,
} t_scenery_type;

typedef enum {
	CLOSE = 0, OPEN,
} t_door_status;

typedef enum {
	UP = 0, DOWN,
} t_door_level;

typedef enum {
	CELL_STONE = CELL_SCENERY | (SCENERY_STONE << 4),
	CELL_TREE = CELL_SCENERY | (SCENERY_TREE << 4),
	CELL_CASE_BOMBINC = CELL_CASE | (BONUS_BOMB_NB_INC << 4),
	CELL_CASE_BOMBDEC = CELL_CASE | (BONUS_BOMB_NB_DEC << 4),
	CELL_CASE_RANGEINC = CELL_CASE | (BONUS_BOMB_RANGE_INC << 4),
	CELL_CASE_RANGEDEC = CELL_CASE | (BONUS_BOMB_RANGE_DEC << 4),
	CELL_CASE_LIFE = CELL_CASE | (BONUS_LIFE << 4),
	CELL_CASE_MONSTER = CELL_CASE | (BONUS_MONSTER << 4),
	CELL_BOMB_1 = CELL_BOMB | (BOMB_1 << 4),
	CELL_BOMB_2 = CELL_BOMB | (BOMB_2 << 4),
	CELL_BOMB_3 = CELL_BOMB | (BOMB_3 << 4),
	CELL_BOMB_4 = CELL_BOMB | (BOMB_4 << 4),
	CELL_MONSTER_NORTH = CELL_MONSTER | (NORTH << 4),
	CELL_MONSTER_SOUTH = CELL_MONSTER | (SOUTH << 4),
	CELL_MONSTER_EAST = CELL_MONSTER | (EAST << 4),
	CELL_MONSTER_WEST = CELL_MONSTER | (WEST << 4),
	CELL_DOOR_OPEN_UP = CELL_DOOR | (OPEN << 4) | (UP << 6),
	CELL_DOOR_OPEN_DOWN = CELL_DOOR | (OPEN << 4) | (DOWN << 6),
	CELL_DOOR_CLOSE_UP = CELL_DOOR | (OPEN << 4),

} t_compose_type;

typedef struct s_map* t_map;

// Create a new empty map
extern t_map map_new(int width, int height);
extern void map_free(t_map map);

// Return the height and width of a map
extern int map_get_width(t_map map);
extern int map_get_height(t_map map);

// Return the list of all bombs on the map
extern list map_get_bombs(t_map map);

//Modify the list
extern void map_set_bombs(t_map map, list bombs);
extern list map_get_monster(t_map map);

//Modify the list
extern void map_set_monster(t_map map, list bombs);

// Return the type of a cell
extern t_cell_type map_get_cell_type(t_map map, int x, int y);
extern t_compose_type map_get_cell_type_detailled(t_map map, int x, int y);

// Set the type of a cell
extern void map_set_cell_type(t_map map, int x, int y, t_cell_type type);

// Test if (x,y) is within the map
extern int map_is_inside(t_map map, int x, int y);

// Load a static pre-calculated map
//extern t_map map_get_default(void);
extern t_map map_get_from_int(int level_number, int map_number);

// Display the map on the screen
extern void map_display(t_map map, SDL_Surface *screen);

// Fonction allow_to_move, eviter de sortir de l'ecran
extern int allow_move(int x1, int x2, int y1, int y2);

//function which prevent case to go outside the screen
extern int allow_case_move(int x1, int x2, int y1, int y2);

void save_map_from_int(FILE* file, t_map map);

extern t_map load_map_from_backup(FILE* file, void* player, ushort map_i);

//determine the number of the map in its level
extern int get_map_number(t_map map);

#endif /* MAP_H_ */
