/*
 * File:
 *   linkedlist-lock.c
 * Author(s):
 *   Vincent Gramoli <vincent.gramoli@epfl.ch>
 * Description:
 *   Lock-based linked list implementation of an integer set
 *
 * Copyright (c) 2009-2010.
 *
 * linkedlist-lock.c is part of Synchrobench
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

#include "intset.h"
#include <memory>

//node_l_t *new_node_l(val_t val, node_l_t *next, int transactional)
std::shared_ptr<node_l_t> new_node_l(val_t val, std::shared_ptr<node_l_t> next, int transactional)
{
  //node_l_t *node_l;

  //node_l = (node_l_t *)malloc(sizeof(node_l_t));
  //if (node_l == NULL) {
  //  perror("malloc");
  //  exit(1);
  //}
  //std::shared_ptr<node_l_t> node_l = std::make_shared<node_l_t>();
  std::shared_ptr<node_l_t> node_l(new node_l_t);
  printf("new node!\n");

  node_l->val = val;
  //node_l->next = next;
  node_l->next = std::move(next);
  INIT_LOCK(&node_l->lock);
  printf("new-node-val: %ld\n", node_l->val);
  printf("return??~~~~~~~~!\n");
  return node_l;
}

intset_l_t *set_new_l()
{
  intset_l_t *set;
  //node_l_t *min, *max;
  std::shared_ptr<node_l_t> min, max;

  if ((set = (intset_l_t *)malloc(sizeof(intset_l_t))) == NULL) {
    perror("malloc");
    exit(1);
  }
  printf("set_new_l before!\n");
  //max = new_node_l(VAL_MAX, NULL, 0);
  max = new_node_l(VAL_MAX, nullptr, 0);
  printf("set_new_l (max)!\n");
  min = new_node_l(VAL_MIN, max, 0);
  printf("set_new_l (min)!\n");
  //set->head = min;
  set->head = std::shared_ptr<node_l_t>(min);
  return set;
}

//void node_delete_l(node_l_t *node) {
//void node_delete_l(std::shared_ptr<node_l_t> node) {
//   DESTROY_LOCK(&node->lock);
//   //free(node);
//   node.reset();
//}

//void set_delete_l(intset_l_t *set)
//{
//  //node_l_t *node, *next;
//  std::shared_ptr<node_l_t> node, next;
//
//  node = set->head;
//  //while (node != NULL) {
//  while (node != nullptr) {
//    next = node->next;
//    DESTROY_LOCK(&node->lock);
//    //free(node);
//    node.reset();
//    node = next;
//  }
//  free(set);
//}

int set_size_l(intset_l_t *set)
{
  int size = 0;
  //node_l_t *node;
  std::shared_ptr<node_l_t> node;

  /* We have at least 2 elements */
  node = set->head->next;
  //while (node->next != NULL) {
  while (node->next != nullptr) {
    size++;
    node = node->next;
  }

  return size;
}



	
