/*
 * list.c
 *
 *  Created on: 26 févr. 2013
 *      Author: charles-damien,Martin Ladure
 */

#include "../include/list.h"
#include <assert.h>

 struct s_list {
 	void * val;
 	struct s_list * next;
 	struct s_list * prev;
 };

 list list_new() {
 	list l = malloc(sizeof(*l));
 	l->val = NULL;
 	l->next = NULL;
 	l->prev = NULL;
 	return l;
 }

 list list_add(list l, void *elt) {
 	if (elt != 0) {
 		if (l->val != NULL) {
 			list new = list_new();
 			new->val = elt;
 			new->next = l;
 			l->prev = new;
 			return new;
 		} else {
 			l->val = elt;
 			return l;
 		}
 	} else
 	return l;
 }

//if the code is return 0, this is going to remove the element
 list list_execute(list l, void * elm, int (*function)(void *, void *)) {
 	list begin = l;
 	list current = l;
	int check; //the return code
	while (current != NULL) {
		check = (*function)(current->val, elm);
		if (check == 0) {
			if (current->next != NULL)
				(current->next)->prev = current->prev;
			if (current->prev != NULL)
				(current->prev)->next = current->next;
			free(current->val);
			current->val = NULL;
			if (current->prev == NULL) {
				if (current->next != NULL) {
					begin = current->next;
				}
			} else {
				free(current);
			}
		}
		current = current->next;
	}
	return begin;
}

void list_free(list l) {
	assert(l);
	list curr_list = l;
	while (curr_list != NULL) {
		assert(curr_list);
		list next_list = curr_list->next;
		free(curr_list->val);
		free(curr_list);
		curr_list = next_list;
	}

}

list list_get_next(list l) {
	assert(l);
	if (l != NULL && l->next != NULL)
		return l->next;
	else
		return NULL;
}

void* list_get_element(list l) {
	assert(l);
	return l->val;
}

