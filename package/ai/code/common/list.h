/* Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _LIST_H_
#define _LIST_H_

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

#endif /* _LIST_H_ */
