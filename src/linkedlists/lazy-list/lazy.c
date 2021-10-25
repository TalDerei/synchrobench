/*
 * File:
 *   lazy.c
 * Author(s):
 *   Vincent Gramoli <vincent.gramoli@epfl.ch>
 * Description:
 *   Lazy linked list implementation of an integer set based on Heller et al. algorithm
 *   "A Lazy Concurrent List-Based Set Algorithm"
 *   S. Heller, M. Herlihy, V. Luchangco, M. Moir, W.N. Scherer III, N. Shavit
 *   p.3-16, OPODIS 2005
 *
 * Copyright (c) 2009-2010.
 *
 * lazy.c is part of Synchrobench
 * 
 * Synchrobench is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "lazy.h"
#include <memory>

inline int is_marked_ref(long i) {
    printf("is_marked_ref!\n");
	return (int) (i &= LONG_MIN+1);
}

inline long unset_mark(long i) {
	i &= LONG_MAX-1;
	return i;
}

inline long set_mark(long i) {
	i = unset_mark(i);
	i += 1;
	return i;
}

//inline node_l_t *get_unmarked_ref(node_l_t *n) {
//	return (node_l_t *) unset_mark((long) n);
//}

inline std::shared_ptr<node_l_t> get_unmarked_ref(std::shared_ptr<node_l_t> &n) {
    printf("get_unmarked_ref!\n");
    return std::shared_ptr<node_l_t>((node_l_t *) unset_mark((long) n.get()));
}


//inline node_l_t *get_marked_ref(node_l_t *n) {
//	return (node_l_t *) set_mark((long) n);
//}

inline std::shared_ptr<node_l_t> get_marked_ref(std::shared_ptr<node_l_t> &n) {
    return std::shared_ptr<node_l_t>((node_l_t *) set_mark((long) n.get()));
}

/*
 * Checking that both curr and pred are both unmarked and that pred's next pointer
 * points to curr to verify that the entries are adjacent and present in the list.
 */
//inline int parse_validate(node_l_t *pred, node_l_t *curr) {
inline int parse_validate(std::shared_ptr<node_l_t>& pred, std::shared_ptr<node_l_t>& curr) {
	return (!is_marked_ref((long) &pred->next) && !is_marked_ref((long) &curr->next) && (pred->next == curr));
}

int parse_find(intset_l_t *set, val_t val) {
    printf("parse_find!\n");
	std::shared_ptr<node_l_t> curr;
	curr = set->head;
	printf("mesure SIZE!\n");
	int size = set_size_l(set);
    printf("size: %d\n", size);
	while (curr->val < val) {
        printf("val: %d\n", val);
        curr = get_unmarked_ref(curr->next);
        printf("curr: %d, %d\n", curr.get(), curr->val);
    }
    printf("pass?\n");
	if (curr->val == val) {
        printf("curr->val == val\n");
	} else {
        printf("curr->val != val\n");
	}
	printf("long: %ld\n", (long) &curr->next);
    return ((curr->val == val) && !is_marked_ref((long) &curr->next));
}

int parse_insert(intset_l_t *set, val_t val) {
    printf("parse_insert!\n");
	//node_l_t *curr, *pred, *newnode;
    std::shared_ptr<node_l_t> pred, curr, newnode;
	int result, validated, notVal;
	
	while (1) {
		pred = set->head;
		curr = get_unmarked_ref(pred->next);
		while (curr->val < val) {
			pred = curr;
			curr = get_unmarked_ref(curr->next);
		}
		LOCK(&pred->lock);
		LOCK(&curr->lock);
		printf("start validated!\n");
		validated = parse_validate(pred, curr);
        printf("validated: %d\n", validated);
        printf("end validated!\n");
		notVal = (curr->val != val);
		result = (validated && notVal);
		if (result) {
		    printf("result = true\n");
			newnode = new_node_l(val, curr, 0);
			pred->next = newnode;
		}
		UNLOCK(&curr->lock);
		UNLOCK(&pred->lock);
		if(validated)
			return result;
	}
}

/*
 * Logically remove an element by setting a mark bit to 1 
 * before removing it physically.
 *
 * NB. it is not safe to free the element after physical deletion as a 
 * pre-empted find operation may currently be parsing the element.
 * TODO: must implement a stop-the-world garbage collector to correctly 
 * free the memory.
 */
//int parse_delete(intset_l_t *set, val_t val) {
int parse_delete(intset_l_t *set, val_t val) {
    printf("parse_delete!\n");
	//node_l_t *pred, *curr;
	std::shared_ptr<node_l_t> pred, curr;
	int result, validated, isVal;
	while(1) {
		pred = set->head;
		curr = get_unmarked_ref(pred->next);
		while (curr->val < val) {
			pred = curr;
			curr = get_unmarked_ref(curr->next);
		}
		LOCK(&pred->lock);
		LOCK(&curr->lock);
		validated = parse_validate(pred, curr);
		isVal = val == curr->val;
		result = validated && isVal;
		if (result) {
			curr->next = get_marked_ref(curr->next);
			pred->next = get_unmarked_ref(curr->next);
		}
		UNLOCK(&curr->lock);
		UNLOCK(&pred->lock);
		if(validated)
			return result;
	}
}
