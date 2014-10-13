/*
 * constant.h
 *
 *  Created on: 15 nov. 2010
 *      Author: Nicolas Aucouturier, Laurent Reveillere
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#define WINDOW_NAME "[PG110] Bomberman 2013"

// Size (# of pixels) of a cell of the map
#define SIZE_BLOC       40
#define WINDOW_BPP      16

// Size (# of pixels) of banner
#define SIZE_LINE		4
#define SIZE_BANNER		40

// Time management
#define DEFAULT_GAME_FPS 300

// Sprites general
#define IMG_MAP_CASE        "sprite/wood_box.png"
#define IMG_MAP_GOAL        "sprite/flag.png"
#define IMG_MAP_KEY			"sprite/key.png"
#define IMG_MAP_DOOR		"sprite/door.png"
#define IMG_MAP_CLOSED_DOOR	"sprite/closed_door.png"

// Scenery elements
#define IMG_MAP_STONE		"sprite/stone.png"
#define IMG_MAP_TREE        "sprite/tree.png"

// Sprites of Banner
#define IMG_BANNER_LINE		"sprite/banner_line.png"
#define IMG_BANNER_LIFE		"sprite/banner_life.png"
#define IMG_BANNER_BOMB		"sprite/bomb3.png"
#define IMG_BANNER_RANGE	"sprite/banner_range.png"
#define IMG_BANNER_0		"sprite/banner_0.jpg"
#define IMG_BANNER_1		"sprite/banner_1.jpg"
#define IMG_BANNER_2		"sprite/banner_2.jpg"
#define IMG_BANNER_3		"sprite/banner_3.jpg"
#define IMG_BANNER_4		"sprite/banner_4.jpg"
#define IMG_BANNER_5		"sprite/banner_5.jpg"
#define IMG_BANNER_6		"sprite/banner_6.jpg"
#define IMG_BANNER_7		"sprite/banner_7.jpg"
#define IMG_BANNER_8		"sprite/banner_8.jpg"
#define IMG_BANNER_9		"sprite/banner_9.jpg"
#define IMG_BANNER_KEY		"sprite/key.png"	
#define IMG_BANNER_PAUSE	"sprite/pause.png"	
#define IMG_MAP_1			"sprite/map_1.png"
#define IMG_FLAG			"sprite/flag.png"

// Sprites of Bombs
#define IMG_BOMB_TTL1       "sprite/bomb1.png"
#define IMG_BOMB_TTL2       "sprite/bomb2.png"
#define IMG_BOMB_TTL3       "sprite/bomb3.png"
#define IMG_BOMB_TTL4       "sprite/bomb4.png"

// Sprites of Bonus
#define IMG_BONUS_BOMB_RANGE_INC  "sprite/bonus_bomb_range_inc.png"
#define IMG_BONUS_BOMB_RANGE_DEC  "sprite/bonus_bomb_range_dec.png"
#define IMG_BONUS_BOMB_NB_INC     "sprite/bonus_bomb_nb_inc.png"
#define IMG_BONUS_BOMB_NB_DEC     "sprite/bonus_bomb_nb_dec.png"

// Sprites of Players
#define IMG_PLAYER_LEFT     "sprite/player_left.png"
#define IMG_PLAYER_UP       "sprite/player_up.png"
#define IMG_PLAYER_RIGHT    "sprite/player_right.png"
#define IMG_PLAYER_DOWN     "sprite/player_down.png"

// Sprites of Monsters
#define IMG_MONSTER_LEFT     "sprite/monster_left.png"
#define IMG_MONSTER_UP       "sprite/monster_up.png"
#define IMG_MONSTER_RIGHT    "sprite/monster_right.png"
#define IMG_MONSTER_DOWN     "sprite/monster_down.png"

 // Sprites of Bomber women
#define IMG_BOMBERWOMEN     "sprite/bomberwoman.png"

// Sprites of Menu
#define IMG_MENU_BACK_DEFAULT "sprite/menu_back_default.png"
#define IMG_MENU_BACK_0 	"sprite/menu_back_0.png"
#define IMG_MENU_BACK_1 	"sprite/menu_back_1.png"
#define IMG_MENU_BACK_2 	"sprite/menu_back_2.png"
#define IMG_MENU_BACK_3 	"sprite/menu_back_3.png"
#define IMG_END_DEFAULT		"sprite/menu_end_1.png"
#define IMG_END_EXIT		"sprite/menu_end_2.png"
#define IMG_END_VICTORY		"sprite/victory.png"
#define IMG_GAME_OVER		"sprite/game_over.png"

// Maximum power of a bomb
#define BOMB_RANGE_MAX      4
// Default power of a bomb
#define BOMB_RANGE_DEFAULT	1

// Lifetime of a bomb in second
#define BOMB_LIFETIME		4
// Base de temps (bombes ,...)
#define BASE_TIME 600

// Number of Monster move per second
#define MONSTER_MOVE_PER_SEC 2

// Bonus
// Probability that a box contains a bonus
#define PROBA_BONUS 80

#define PROBA_BONUS_BOMB_RANGE 30

// Increase the power of a bomb +1
#define PROBA_BONUS_BOMB_RANGE_INC 50

// Decrease the power of a bomb -1
#define PROBA_BONUS_BOMB_RANGE_DEC 50

#define PROBA_BONUS_BOMB_NB    30

// Increase the number of bombs
#define PROBA_BONUS_BOMB_NB_INC  40
// Decrease the number of bombs
#define PROBA_BONUS_BOMB_NB_DEC  70

#define PROBA_BONUS_MONSTER      20

#define PROBA_BONUS_LIFE      20

enum e_way {
	NORTH = 0, SOUTH, WEST, EAST
};

#endif /* CONSTANT */
