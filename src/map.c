/*
 * map.c
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent Reveillere, Vincent Filou
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>

#include <time.h>
#include "../include/constant.h"
#include "../include/map.h"
#include "../include/misc.h"
#include "../include/bomb.h"
#include "../include/monster.h"

typedef char t_cell_type_;

struct s_map {
	int width;
	int height;
	int map_number;
	list bombs;
	list monster;

	t_cell_type_* grid;

	SDL_Surface* img_box;
	SDL_Surface* img_goal;
	SDL_Surface* img_bonus_bomb_range_inc;
	SDL_Surface* img_bonus_bomb_range_dec;
	SDL_Surface* img_bonus_bomb_nb_inc;
	SDL_Surface* img_bonus_bomb_nb_dec;
	SDL_Surface* img_key;
	SDL_Surface* img_door;
	SDL_Surface* img_closed_door;
	SDL_Surface* img_stone;
	SDL_Surface* img_tree;
	SDL_Surface* img_bomb_ttl1;
	SDL_Surface* img_bomb_ttl2;
	SDL_Surface* img_bomb_ttl3;
	SDL_Surface* img_bomb_ttl4;
	SDL_Surface* img_bonus_life;
	SDL_Surface* img_monster_north;
	SDL_Surface* img_monster_south;
	SDL_Surface* img_monster_west;
	SDL_Surface* img_monster_east;
	SDL_Surface* img_map_1;
	SDL_Surface* img_flag;
	SDL_Surface* img_bomberwomen;

};

#define CELL(i,j) (i +  map->width * j)

t_map map_new(int width, int height) {
	assert(width > 0 && height > 0);

	t_map map = malloc(sizeof(struct s_map));
	if (map == NULL )
		exit(EXIT_FAILURE);

	map->width = width;
	map->height = height;
	map->bombs = init_bombs();
	map->monster = init_bombs();

	map->grid = (t_cell_type_ *) malloc(height * width * sizeof(t_cell_type_));
	if (map->grid == NULL )
		exit(EXIT_FAILURE);

	// Grid cleaning
	int i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			map->grid[CELL(i,j)] = CELL_EMPTY;
		}
	}

	// Sprite loading
	map->img_tree = load_image(IMG_MAP_TREE);
	map->img_box = load_image(IMG_MAP_CASE);
	map->img_goal = load_image(IMG_MAP_GOAL);
	map->img_key = load_image(IMG_MAP_KEY);
	map->img_stone = load_image(IMG_MAP_STONE);
	map->img_door = load_image(IMG_MAP_DOOR);
	map->img_closed_door = load_image(IMG_MAP_CLOSED_DOOR);
	map->img_bonus_bomb_range_inc = load_image(IMG_BONUS_BOMB_RANGE_INC);
	map->img_bonus_bomb_range_dec = load_image(IMG_BONUS_BOMB_RANGE_DEC);
	map->img_bonus_bomb_nb_inc = load_image(IMG_BONUS_BOMB_NB_INC);
	map->img_bonus_bomb_nb_dec = load_image(IMG_BONUS_BOMB_NB_DEC);
	map->img_bomb_ttl1 = load_image(IMG_BOMB_TTL1);
	map->img_bomb_ttl2 = load_image(IMG_BOMB_TTL2);
	map->img_bomb_ttl3 = load_image(IMG_BOMB_TTL3);
	map->img_bomb_ttl4 = load_image(IMG_BOMB_TTL4);
	map->img_bonus_life = load_image(IMG_BANNER_LIFE);
	map->img_monster_north = load_image(IMG_MONSTER_UP);
	map->img_monster_south = load_image(IMG_MONSTER_DOWN);
	map->img_monster_west = load_image(IMG_MONSTER_LEFT);
	map->img_monster_east = load_image(IMG_MONSTER_RIGHT);
	map->img_map_1 = load_image(IMG_MAP_1);
	map->img_flag = load_image(IMG_FLAG);
	map->img_bomberwomen = load_image(IMG_BOMBERWOMEN);

	return map;
}

int allow_move(int x1, int x2, int y1, int y2) {//Player is inside the grid ?
	if ((x1 == 12 && x2 == 13 && y1 >= 0 && y2 >= 0)
			|| (x1 >= 0 && x2 >= 0 && y1 == -1 && y2 == -2)
			|| (x1 == -1 && x2 == -2 && y1 >= 0 && y2 >= 0)
			|| (x1 >= 0 && x2 >= 0 && y1 == 12 && y2 == 13))
		return 1;
	else
		return 0;
}

int allow_case_move(int x1, int x2, int y1, int y2) { // Same function as the previous but for the case
	if ((x1 == 11 && x2 == 12 && y1 >= 0 && y2 >= 0)
			|| (x1 >= 0 && x2 >= 0 && y1 == 0 && y2 == -1)
			|| (x1 == 0 && x2 == -1 && y1 >= 0 && y2 >= 0)
			|| (x1 >= 0 && x2 >= 0 && y1 == 11 && y2 == 12))
		return 1;
	else
		return 0;
}

int map_is_inside(t_map map, int x, int y) {
	assert(map);
	return 1;
}

void map_free(t_map map) {
	if (map == NULL ) {
		return;
	}

	free(map->grid);
	list_free(map->bombs);
	list_free(map->monster);
	SDL_FreeSurface(map->img_bonus_bomb_nb_dec);
	SDL_FreeSurface(map->img_bonus_bomb_nb_inc);
	SDL_FreeSurface(map->img_bonus_bomb_range_dec);
	SDL_FreeSurface(map->img_bonus_bomb_range_inc);
	SDL_FreeSurface(map->img_closed_door);
	SDL_FreeSurface(map->img_door);
	SDL_FreeSurface(map->img_key);
	SDL_FreeSurface(map->img_stone);
	SDL_FreeSurface(map->img_box);
	SDL_FreeSurface(map->img_goal);
	SDL_FreeSurface(map->img_tree);
	SDL_FreeSurface(map->img_flag);
	SDL_FreeSurface(map->img_bomb_ttl1);
	SDL_FreeSurface(map->img_bomb_ttl2);
	SDL_FreeSurface(map->img_bomb_ttl3);
	SDL_FreeSurface(map->img_bomb_ttl4);
	SDL_FreeSurface(map->img_bonus_life);
	SDL_FreeSurface(map->img_monster_north);
	SDL_FreeSurface(map->img_monster_south);
	SDL_FreeSurface(map->img_monster_west);
	SDL_FreeSurface(map->img_monster_east);
	SDL_FreeSurface(map->img_map_1);

	free(map);
}

int map_get_width(t_map map) {
	assert(map != NULL);
	return map->width;
}

int map_get_height(t_map map) {
	assert(map != NULL);
	return map->height;
}

list map_get_bombs(t_map map) {
	assert(map != NULL);
	return map->bombs;
}
void map_set_bombs(t_map map, list bombs) {
	assert(bombs);
	map->bombs = bombs;
}
list map_get_monster(t_map map) {
	assert(map != NULL);
	return map->monster;
}
void map_set_monster(t_map map, list monster) {
	assert(monster);
	map->monster = monster;
}

/*void printgrid(t_map map) {
 int i, j;
 for (i = 0; i < map->width; i++) {
 for (j = 0; j < map->height; j++) {
 printf("%d -",map->grid[CELL(j,i)]);
 }
 printf("\n");
 }
 printf("\n \n");
 }*/

t_cell_type map_get_cell_type(t_map map, int x, int y) {
	assert(map && map_is_inside(map, x, y));
	//printgrid(map);
	return map->grid[CELL(x,y)] & 15;
}

t_compose_type map_get_cell_type_detailled(t_map map, int x, int y) {
	//Same function as the previous one but let the 4 most significant bits
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)];
}

void map_set_cell_type(t_map map, int x, int y, t_cell_type type) {
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = type;
}

void display_doors(t_map map, SDL_Surface* screen, SDL_Rect* place,
		t_cell_type_ type) {
	switch (type >> 4 && 4) {
	case OPEN:
		SDL_BlitSurface(map->img_door, NULL, screen, place);
		break;
	case CLOSE:
		SDL_BlitSurface(map->img_closed_door, NULL, screen, place);
		break;
	}

}

void display_bonus(t_map map, SDL_Surface* screen, SDL_Rect* place,
		t_cell_type_ type) {
	// bonus is encoded with the 4 most significant bits
	//printf("type = %d \n", type);
	switch (type >> 4) {
	case BONUS_BOMB_RANGE_INC:
		SDL_BlitSurface(map->img_bonus_bomb_range_inc, NULL, screen, place);
		break;

	case BONUS_BOMB_RANGE_DEC:
		SDL_BlitSurface(map->img_bonus_bomb_range_dec, NULL, screen, place);
		break;

	case BONUS_BOMB_NB_INC:
		SDL_BlitSurface(map->img_bonus_bomb_nb_inc, NULL, screen, place);
		break;

	case BONUS_BOMB_NB_DEC:
		SDL_BlitSurface(map->img_bonus_bomb_nb_dec, NULL, screen, place);
		break;
	case BONUS_LIFE:
		SDL_BlitSurface(map->img_bonus_life, NULL, screen, place);
		break;

	}
}

void display_scenery(t_map map, SDL_Surface* screen, SDL_Rect* place,t_cell_type_ type) {

	switch (type >> 4) {
	case SCENERY_STONE:
		SDL_BlitSurface(map->img_stone, NULL, screen, place);
		break;

	case SCENERY_TREE:
		SDL_BlitSurface(map->img_tree, NULL, screen, place);
		break;

	case BOMB_4:
		SDL_BlitSurface(map->img_bomb_ttl4, NULL, screen, place);
		break;

	case BOMB_3:
		SDL_BlitSurface(map->img_bomb_ttl3, NULL, screen, place);
		break;

	case BOMB_2:
		SDL_BlitSurface(map->img_bomb_ttl2, NULL, screen, place);
		break;

	case BOMB_1:
		SDL_BlitSurface(map->img_bomb_ttl1, NULL, screen, place);
		break;
	}
}

void display_bomb(t_map map, SDL_Surface* screen, SDL_Rect* place,
		t_cell_type_ type) {

	switch (type >> 4) {
	case BOMB_4:
		SDL_BlitSurface(map->img_bomb_ttl4, NULL, screen, place);
		break;

	case BOMB_3:
		SDL_BlitSurface(map->img_bomb_ttl3, NULL, screen, place);
		break;

	case BOMB_2:
		SDL_BlitSurface(map->img_bomb_ttl2, NULL, screen, place);
		break;

	case BOMB_1:
		SDL_BlitSurface(map->img_bomb_ttl1, NULL, screen, place);
		break;
	}
}

void display_monster(t_map map, SDL_Surface* screen, SDL_Rect* place,
		t_cell_type_ type) {

	switch (type >> 4) {
	case NORTH:
		SDL_BlitSurface(map->img_monster_north, NULL, screen, place);
		break;

	case SOUTH:
		SDL_BlitSurface(map->img_monster_south, NULL, screen, place);
		break;

	case EAST:
		SDL_BlitSurface(map->img_monster_east, NULL, screen, place);
		break;

	case WEST:
		SDL_BlitSurface(map->img_monster_west, NULL, screen, place);
		break;
	}
}

void map_display(t_map map, SDL_Surface *screen) {
	int i, j;
	assert(map != NULL);
	assert(screen != NULL);
	assert(map->height > 0 && map->width > 0);
	assert(map->img_bonus_bomb_nb_dec != NULL);
	assert(map->img_bonus_bomb_nb_inc != NULL);
	assert(map->img_bonus_bomb_range_dec != NULL);
	assert(map->img_bonus_bomb_range_inc != NULL);
	assert(map->img_closed_door != NULL);
	assert(map->img_door != NULL);
	assert(map->img_key != NULL);
	assert(map->img_stone != NULL);
	assert(map->img_box != NULL);
	assert(map->img_goal != NULL);
	for (i = 0; i < map->width; i++) {
		for (j = 0; j < map->height; j++) {

			SDL_Rect place;
			place.x = i * SIZE_BLOC;
			place.y = j * SIZE_BLOC;
			t_cell_type_ type = map->grid[CELL(i,j)];

			switch (type & 15) { // type is encoded with 4 bits (the & 15 (1111)) is a mask to keep the four less significant bits)
			case CELL_GOAL:
				SDL_BlitSurface(map->img_goal, NULL, screen, &place);
				break;
			case CELL_SCENERY:
				display_scenery(map, screen, &place, type);
				break;
			case CELL_BOMB:
				display_bomb(map, screen, &place, type);
				break;
			case CELL_MONSTER:
				display_monster(map, screen, &place, type);
				break;
			case CELL_CASE:
				SDL_BlitSurface(map->img_box, NULL, screen, &place);
				break;
			case CELL_BONUS:
				display_bonus(map, screen, &place, type);
				break;
			case CELL_KEY:
				SDL_BlitSurface(map->img_key, NULL, screen, &place);
				break;
			case CELL_DOOR:
				display_doors(map, screen, &place, type);
				break;
			case CELL_LEVEL:
				SDL_BlitSurface(map->img_flag, NULL, screen, &place);
				break;
			case CELL_BOMBERWOMAN:
				SDL_BlitSurface(map->img_bomberwomen, NULL, screen, &place);
				break;
			case CELL_EMPTY:
				break;

			}
		}

	}
}

t_map map_get_from_int(int level_number, int map_number) {

	FILE * file;
	char path[] = "./map/map_n_n";
	path[10] = '0' + map_number;
	path[12] = '0' + level_number;
	if ((file = fopen(path, "r")) == NULL ) {
		printf("Impossible d'ouvrir le fichier de configuration\n");
		return NULL ;
	}
	int width = 0;
	int height = 0;

	fscanf(file, "%d:", &width);
	fscanf(file, "%d,\n", &height);
	int total = width * height;

	t_map map = map_new(width, height);
	map->map_number = map_number;
	int tmp;
	for (int i = 0; i < total; i++) {
		fscanf(file, "%d,", &tmp);
		map->grid[i] = tmp;
	}

	fclose(file);
	for (int i = 0; i < map->width; i++) {
		for (int j = 0; j < map->height; j++) {
			if (map->grid[CELL(i,j)] == CELL_MONSTER) {
				add_new_monster(map, i, j);
			}
		}
	}

	return map;
}

void save_map_from_int(FILE* file, t_map map) {
	assert(map);
	assert(file);
	int width = map->width;
	int height = map->height;
	fprintf(file, "%d:", width);
	fprintf(file, "%d,\n", height);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			fprintf(file, "%d,", map->grid[CELL(j,i)]);
		}
		fprintf(file, "\n");
	}
}

t_map load_map_from_backup(FILE* file, void* player, ushort map_i) {

	int width = 0;
	int height = 0;
	fscanf(file, "%d:", &width);
	fscanf(file, "%d,\n", &height);
	int total = width * height;

	t_map map = map_new(width, height);
	map->map_number = (int) map_i;
	int tmp;
	for (int i = 0; i < total; i++) {
		fscanf(file, "%d,", &tmp);
		map->grid[i] = tmp;
	}
	fscanf(file, "\n");

	for (int i = 0; i < map->width; i++) {
		for (int j = 0; j < map->height; j++) {
			if ((map->grid[CELL(i,j)] & 15) == CELL_MONSTER) {
				add_new_monster(map, i, j);
			}
			if ((map->grid[CELL(i,j)] & 15) == CELL_BOMB) {
				int ttl = map->grid[CELL(i,j)] >> 4;
				switch (ttl) {
				case BOMB_1:
					ttl = 1;
					break;
				case BOMB_2:
					ttl = 2;
					break;
				case BOMB_3:
					ttl = 3;
					break;
				case BOMB_4:
				default:
					ttl = 4;
					break;
				}
				add_bomb_from_save(map, i, j, ttl, player);
			}
		}
	}

	return map;

}

int get_map_number(t_map map) {
	assert(map);
	return map->map_number;
}
