/**********************************************************************
 * Copyright (C) 2014 Cadence Design Systems, Inc.
 * All rights reserved worldwide.
 ***********************************************************************
 * sduc_list.h
 * Function for creating and management circular list
 *
 ***********************************************************************/
#ifndef CDN_LIST_H
#define CDN_LIST_H

#include "cdn_stdtypes.h"

/*Function initialize list*/
static inline void listInit(ListHead *list) {
    list->next = list;
    list->prev = list;
}

/*Add new element to the list between prev and next*/
static inline void listAddElement(ListHead * new, ListHead * prev, ListHead * next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;

}

/*Add new entry after a specified head*/
static inline void listAdd(ListHead *new,  ListHead * head) {
    listAddElement(new, head, head->next);
}

static inline void listAddTail(ListHead *new, ListHead *head) {
    listAddElement(new, head->prev, head);
}

static inline void listDelete(ListHead * list) {
    list->next->prev = list->prev;
    list->prev->next = list->next;

    list->prev = NULL;
    list->next =NULL;
}

#endif
