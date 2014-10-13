/*
 * monster.h
 *
 *  Created on: 23 Mars 2013
 *      Author: mladure
 */

#ifndef MONSTER_H_
#define MONSTER_H_

#include "../include/constant.h"
#include "../include/list.h"
#include "../include/monster.h"
#include "../include/player.h"
#include <assert.h>

typedef struct s_monster* t_monster;

extern t_monster create_new_monster(t_map map, int x, int y);
extern int monster_update(t_monster monster, t_map map);
extern int monsterupdate(void * elt, void * elm);
extern void update_all_monster(t_map map);
extern void update_all_monster(t_map map);
extern void add_new_monster(t_map map, int x, int y);
extern int monster_move_aux(t_monster monster, t_map map, int x1, int y1,
		int x2, int y2);
extern void monster_dec_nb_life(t_monster monster);
extern t_monster get_monster_from_map(t_map map, int x, int y);

#endif /* MONSTER_H_ */
