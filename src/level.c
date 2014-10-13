/*
 * level.c
 *
 *  Created on: 26 févr. 2013
 *      Author: charles-damien,Martin Ladure
 */
#include "../include/game.h"
#include "../include/level.h"
#include "../include/map.h"

struct s_level {
	t_map* maps; // array of the level's maps
	ushort nb_maps; // nb maps of the level
	ushort cur_map; // the current map
};

t_level level_get_level(int num) {
	t_level level = malloc(sizeof(struct s_level));
	switch (num) {
	case 0:
		level->nb_maps = 3;
		level->cur_map = 0;
		level->maps = malloc(level->nb_maps * sizeof(*level->maps));
		level->maps[0] = map_get_from_int(num, 0);
		level->maps[1] = map_get_from_int(num, 1);
		level->maps[2] = map_get_from_int(num, 2);
		return level;
		break;
	case 1:
		level->nb_maps = 4;
		level->cur_map = 0;
		level->maps = malloc(level->nb_maps * sizeof(*level->maps));
		level->maps[0] = map_get_from_int(num, 0);
		level->maps[1] = map_get_from_int(num, 1);
		level->maps[2] = map_get_from_int(num, 2);
		level->maps[3] = map_get_from_int(num, 3);
		return level;
		break;
	}
	return NULL;
}

void level_map_up(t_level level) {
	if (level->cur_map < level->nb_maps - 1)
		level->cur_map++;
}

void level_map_down(t_level level) {
	if (level->cur_map != 0)
		level->cur_map--;
}

t_map level_get_curr_map(t_level level) {
	return level->maps[level->cur_map];
}
int level_get_curr_map_number(t_level level) {
	return level->cur_map;
}

t_map level_get_map(t_level level, int num) {
	assert(num <= level->nb_maps);
	return level->maps[num];
}

void level_free(t_level level) {
	for (int i = 0; i < level->nb_maps; i++) {
		map_free(level->maps[i]);
	}
	free(level->maps);
}

void level_display(t_level level, SDL_Surface* screen) {
	map_display(level->maps[level->cur_map], screen);
}

void save_level(FILE* file, t_level level) {
	fprintf(file, "current_map:%d,\n", level->cur_map);
	for (ushort map_i = 0; map_i < level->nb_maps; map_i++) {
		fprintf(file, "map:%d,\n", map_i);
		save_map_from_int(file, level->maps[map_i]);
	}
}

t_level load_level(FILE* file, void* player, int nb_maps) {
	t_level level = malloc(sizeof(struct s_level));
	assert(level);
	level->maps = malloc(level->nb_maps * sizeof(*level->maps));
	int current_map;
	fscanf(file, "current_map:%d,\n", &current_map);
	level->cur_map = (ushort) current_map;
	int checkmap;
	level->nb_maps = nb_maps;
	for (ushort map_i = 0; map_i < level->nb_maps; map_i++) {
		fscanf(file, "map:%d,\n", &checkmap);
		if (checkmap != map_i)
			error("Fichier de sauvegarde corrompu");
		level->maps[map_i] = load_map_from_backup(file, player, map_i);
	}
	return level;

}

