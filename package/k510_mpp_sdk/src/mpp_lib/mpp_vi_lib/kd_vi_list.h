/* Copyright 2022 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
  File Name     : kd_vi.h
  Version       : Initial Draft
  Author        : 
  Created       : 
  Description   : 
  History       :
  1.Date        : 
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef _KD_VI_LIST_H_
#define _KD_VI_LIST_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct list_entry {
	struct list_entry *prev;
	struct list_entry *next;
};

static inline void list_init(struct list_entry *list)
{
	list->next = list;
	list->prev = list;
}

static inline void list_append(struct list_entry *entry, struct list_entry *list)
{
	entry->next = list;
	entry->prev = list->prev;
	list->prev->next = entry;
	list->prev = entry;
}

static inline void list_prepend(struct list_entry *entry, struct list_entry *list)
{
	entry->next = list->next;
	entry->prev = list;
	list->next->prev = entry;
	list->next = entry;
}

#define list_entry(entry, type, member) \
	(type *)((char *)(entry) - offsetof(type, member))

#define list_for_each(entry, list) \
	for (entry = (list)->next; entry != (list); entry = entry->next)

#define list_for_each_entry(entry, list, member) \
	for (entry = list_entry((list)->next, typeof(*entry), member); \
	     &entry->member != (list); \
	     entry = list_entry(entry->member.next, typeof(*entry), member))

#define list_for_each_safe(entry, __next, list) \
	for (entry = (list)->next, __next = entry->next; entry != (list); \
	     entry = __next, __next = entry->next)

#define list_for_each_entry_safe(entry, __next, list, member) \
	for (entry = list_entry((list)->next, typeof(*entry), member), \
	     __next = list_entry(entry->member.next, typeof(*entry), member); \
	     &entry->member != (list); \
	     entry = __next, __next = list_entry(entry->member.next, typeof(*entry), member))


#ifdef __cplusplus
}
#endif

#endif /* _KD_VI_LIST_H_ */
