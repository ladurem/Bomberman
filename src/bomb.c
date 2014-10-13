/*
 * bomb.c
 *
 *  Created on: 26 févr. 2013
 *      Author: charles-damien,Martin Ladure
 */

#include "../include/bomb.h"
#include "../include/map.h"
#include "../include/player.h"
#include "../include/monster.h"
#include <math.h>
#include <time.h> 
struct s_bomb {
	int x;
	int y;
	Uint32 update_time;
	int time_remaining;
	t_player player;
	int power;
};

int bomb_range = BOMB_RANGE_DEFAULT;

list init_bombs() {
	list l;
	l = list_new();
	return l;
}

t_bomb create_new_bomb(t_map map, t_player player) {

	t_bomb bomb;
	if (player_get_nb_bomb(player) > 0) { //a bomb is available ?
		bomb = malloc(sizeof(*bomb));
		assert(bomb);
		bomb->x = player_get_x(player);
		bomb->y = player_get_y(player);
		bomb->update_time = SDL_GetTicks();
		bomb->power = bomb_range;
		bomb->time_remaining = BOMB_LIFETIME;
		bomb->player = player;
		map_set_cell_type(map, player_get_x(player), player_get_y(player),
				CELL_BOMB_4); //put one bomb
		player_dec_nb_bomb(player); // remove one bomb to the stock
		return bomb;
	} else
		return 0;
}

void explosion(t_bomb bomb, t_map map) {
	int i, j, type_bonus, bonus;
	j = bomb->y;
	for (i = bomb->x - bomb->power; i <= bomb->x + bomb->power; i++) {
		if (i >= 0 && i < map_get_height(map)) {
			switch (map_get_cell_type(map, i, j)) {
			case CELL_CASE:
				type_bonus = random_bonus();
				if (type_bonus != CELL_EMPTY) {
					bonus = type_bonus << 4;
					bonus += CELL_BONUS;

				} else
					bonus = CELL_EMPTY;
				if (type_bonus == BONUS_MONSTER) {
					map_set_cell_type(map, i, j, CELL_EMPTY);
					add_new_monster(map, i, j);
				} else {
					map_set_cell_type(map, i, j, CELL_EMPTY);
					map_set_cell_type(map, i, j, bonus);
				}
				break;
			case CELL_MONSTER:
				monster_dec_nb_life(get_monster_from_map(map, i, j));
				break;
			default:
				break;

			}
		}
	}

	i = bomb->x;
	for (j = bomb->y - bomb->power; j <= bomb->y + bomb->power; j++) {
		if (j >= 0 && j < map_get_width(map)) {
			switch (map_get_cell_type(map, i, j)) {
			case CELL_CASE:
				type_bonus = random_bonus();
				if (type_bonus != CELL_EMPTY) {
					bonus = type_bonus << 4;
					bonus += CELL_BONUS;

				} else
					bonus = CELL_EMPTY;
				if (type_bonus == BONUS_MONSTER) {
					map_set_cell_type(map, i, j, CELL_EMPTY);
					add_new_monster(map, i, j);
				} else {
					map_set_cell_type(map, i, j, CELL_EMPTY);
					map_set_cell_type(map, i, j, bonus);
				}
				break;
			case CELL_MONSTER:
				monster_dec_nb_life(get_monster_from_map(map, i, j));
				break;
			default:
				break;

			}
		}
	}

//Remove the bomb
	map_set_cell_type(map, bomb->x, bomb->y, CELL_EMPTY);

//if the player is near the bomb, remove one life
	if ((player_get_x(bomb->player) == bomb->x
			&& abs(bomb->y - player_get_y(bomb->player)) <= bomb_range)
			|| (player_get_y(bomb->player) == bomb->y
					&& abs(player_get_x(bomb->player) - bomb->x) <= bomb_range)
			|| (player_get_x(bomb->player) == bomb->x
					&& player_get_y(bomb->player) == bomb->y)) {
		player_remove_life(bomb->player);
	}

}

int random_bonus() {
// Chose a random bonus
	int random = rand() % 100;
	if (random < PROBA_BONUS) {
		random = rand() % 100;
		if (random < PROBA_BONUS_BOMB_RANGE) {
			random = rand() % 100;
			if (random < PROBA_BONUS_BOMB_RANGE_INC) {
				return BONUS_BOMB_RANGE_INC;
			} else
				return BONUS_BOMB_RANGE_DEC;
		} else if (random < PROBA_BONUS_BOMB_RANGE + PROBA_BONUS_BOMB_NB) {
			if (random < PROBA_BONUS_BOMB_NB_INC) {
				return BONUS_BOMB_NB_INC;
			} else
				return BONUS_BOMB_NB_DEC;
		} else if (random
				< PROBA_BONUS_BOMB_RANGE + PROBA_BONUS_BOMB_NB
						+ PROBA_BONUS_LIFE) {
			return BONUS_LIFE;
		} else

			return BONUS_MONSTER;
		return BONUS_LIFE;

	} else
		return CELL_EMPTY;
}

int bomber_update(t_bomb bomb, t_map map) {

	if (bomb == NULL )
		return 1;
	if ((SDL_GetTicks() - bomb->update_time) > BASE_TIME) {

		bomb->time_remaining--;
		switch (bomb->time_remaining) {
		case 0:
			explosion(bomb, map);
			return '0'; //remove the element from the list
			break;
		case 1:
			map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB_1);
			break;
		case 2:
			map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB_2);
			break;
		case 3:
			map_set_cell_type(map, bomb->x, bomb->y, CELL_BOMB_3);
			break;
		}
		bomb->update_time = SDL_GetTicks();
	}
	return 1;
}

int bomberupdate(void * elt, void * elm) {
	int result = bomber_update((t_bomb) elt, (t_map) elm);
	return result;
}

void update_all_bombs(t_map map) {
	map_set_bombs(map, list_execute(map_get_bombs(map), map, bomberupdate));
}

void add_new_bomb(t_map map, t_player player) {
	list list = map_get_bombs(map);
	assert(list);
	list = list_add(list, create_new_bomb(map, player)); // add the bomb to the list
	map_set_bombs(map, list);
}

t_bomb create_bomb_from_save(int x, int y, int ttl, t_player player) {
	t_bomb bomb = malloc(sizeof(*bomb));
	bomb->x = x;
	bomb->y = y;
	bomb->update_time = SDL_GetTicks();
	bomb->power = bomb_range;
	bomb->time_remaining = ttl;
	bomb->player = player;
	return bomb;
}

void add_bomb_from_save(t_map map, int x, int y, int ttl, t_player player) {
	list list = map_get_bombs(map);
	assert(list);
	list = list_add(list, create_bomb_from_save(x, y, ttl, player));
	map_set_bombs(map, list);
}

