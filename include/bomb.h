/*
 e * bomb.h
 *
 *  Created on: 26 févr. 2013
 *      Author: charles-damien
 */

#ifndef BOMB_H_
#define BOMB_H_

#include "../include/constant.h"
#include "../include/list.h"
#include "../include/player.h"
#include "../include/monster.h"
#include <assert.h>

typedef struct s_bomb* t_bomb;

extern int bomb_range;

extern list init_bombs();

extern t_bomb create_new_bomb(t_map map, t_player player);

extern void explosion(t_bomb bomb, t_map map);

extern int bomber_update(t_bomb bomb, t_map map);

extern int bomberupdate(void * elt, void * elm);

extern void update_all_bombs();

extern void add_new_bomb(t_map map, t_player player);

extern void add_bomb_from_save(t_map map, int x, int y, int ttl,t_player player); // This function is only used to load a game

extern int random_bonus();

#endif /* BOMB_H_ */
