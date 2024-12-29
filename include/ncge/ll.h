/*
 * @file   ll.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef LL_H_INCLUDED_
#define LL_H_INCLUDED_

#include <stdbool.h>

#include "ncge/types.h"

struct node {
	void* d;
	struct node* next;
};

struct ll {
	u32 dsize;
	u32 cnt;
	void (*dtor)(void* d);
	struct node* head;
};

#define ll_dcast(n, tp) *(tp*)((n)->d)
#define ll_for(l, n)    for (; n != NULL; n = n->next)
#define ll_foreach(l)   for (struct node* n = (l)->head; n != NULL; n = n->next)

#define ll(size, dtor)                                                         \
	(struct ll)                                                                \
	{                                                                          \
		(size), 0, (dtor), NULL                                                \
	}

void ll_init(struct ll* const l, u32 dsize, void (*dtor)(void* d));
void ll_destroy(struct ll* const l);

int ll_add(struct ll* const l, void* const d, bool prealloc);
int ll_rm(struct ll* const l);

void* ll_back(struct ll* const l);
void* ll_get(struct ll* const l, u32 id);

#endif /* LL_H_INCLUDED_ */

/**** END OF FILE ****/
