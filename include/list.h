/*
 * list.h
 *
 *  Created on: 26 févr. 2013
 *      Author: charles-damien
 */

#ifndef LIST_H_
#define LIST_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct s_list* list;

//crée une liste vide
extern list list_new(void);

//Retounr une nouvelle liste l avec elt en tete de la liste
extern list list_add(list l, void *elt);

//Affiche tous les elements de l
extern list list_execute(list l, void * elm, int (*function)(void *, void *));

extern void list_free(list l);

extern list list_get_next(list l);

extern void* list_get_element(list l);

#endif /* LIST_H_ */
