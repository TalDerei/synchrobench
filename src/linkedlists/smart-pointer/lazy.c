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

/* custom "marking" function for marking nodes as logically deleted */
inline bool marked_node(std::shared_ptr<node_l_t> &node) {
    if (node != nullptr) {
        return node->marked.load(std::memory_order_seq_cst);
    } else {
        return false;
    }
}

/*
 * Checking that both curr and pred are both unmarked and that pred's next pointer
 * points to curr to verify that the entries are adjacent and present in the list.
 */
inline int parse_validate(std::shared_ptr<node_l_t> &pred, std::shared_ptr<node_l_t> &curr) {
    return !marked_node(pred) && !marked_node(curr) && (pred->next == curr);
}

int parse_find(intset_l_t *set, val_t val) {
	/** curr is smart pointer to node_l_t structs */
	std::shared_ptr<node_l_t> curr;
	/** atomically load head of set */
	curr = std::atomic_load(&set->head);
	while (curr->val < val)
        curr = std::atomic_load(&curr->next);
    return ((curr->val == val) && !curr->next->marked.load(std::memory_order_seq_cst));
}

int parse_insert(intset_l_t *set, val_t val) {
	/** pred, curr, and newnode are smart pointers to node_l_t structs */
	std::shared_ptr<node_l_t> newnode, curr, pred;
	int result, validated, notVal;
	
	while (1) {
		/** atomically load in pred and curr */
		pred = std::atomic_load(&set->head);
		curr = std::atomic_load(&pred->next);
		while (curr->val < val) {
			pred = std::atomic_load(&curr);
			curr = std::atomic_load(&curr->next);
		}
		LOCK(&pred->lock);
		LOCK(&curr->lock);
		validated = parse_validate(pred, curr);
		notVal = (curr->val != val);
		result = (validated && notVal);
		if (result) {
            newnode = new_node_l(val, pred->next, 0);
			std::atomic_store(&pred->next, newnode);
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
int parse_delete(intset_l_t *set, val_t val) {
	/** pred and curr are smart pointers to node_l_t structs */
	std::shared_ptr<node_l_t> pred, curr;

	int result, validated, isVal;
	while (1) {
		/** atomically load in the head node */
		pred = std::atomic_load(&set->head);
		/** atomically load the next pointer of the head node */
		curr = std::atomic_load(&pred->next);
		while (curr->val < val) {
			/** atomically load curr and curr->next */
			pred = std::atomic_load(&curr);
			curr = std::atomic_load(&curr->next);
		}
		/** lock pred and curr */
		LOCK(&pred->lock);
		LOCK(&curr->lock);
		/** validate pred and curr */
		validated = parse_validate(pred, curr);
		isVal = val == curr->val;
		result = validated && isVal;
		if (result) {
			/** mark curr->next as true */
			curr->marked.store(true, std::memory_order_seq_cst);
			/* attomically stored pred->next as curr->nexy */
			std::atomic_store(&pred->next, curr->next);
		}
		/** unlock pred and curr */
		UNLOCK(&curr->lock);
		UNLOCK(&pred->lock);
		if(validated) {
            return result;
        }
	}
}
