/*
 * level.h
 *
 *  Created on: 14 févr. 2013
 *      Author: xderoche
 */

#ifndef LEVEL_H_
#define LEVEL_H_

typedef struct s_level* t_level;

//This functions give the number of maps for the level i
#define NB_MAPS(i) (i + 3)

// return level number num
t_level level_get_level(int num);

extern void level_map_up(t_level level);
extern void level_map_down(t_level level);

// return current map of the level
t_map level_get_curr_map(t_level level);
//return the number of the current map
int level_get_curr_map_number(t_level level);

// return map number num of the level
t_map level_get_map(t_level level, int num);

// free the level
void level_free(t_level level);

// display the level
void level_display(t_level level, SDL_Surface* screen);

// free level struct
void level_free(t_level level);

//save level
extern void save_level(FILE* file, t_level level);
//load level
extern t_level load_level(FILE* file, void* player, int nb_maps);

#endif /* LEVEL_H_ */
