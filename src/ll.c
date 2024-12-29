/*
 * @file   ll.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include "ncge/ll.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct node* create_node(void* const d, u32 size)
{
	assert(d != NULL);

	struct node* n = calloc(1, sizeof(struct node));
	if (n == NULL)
		return NULL;

	n->d = d;

	if (size != 0) {
		n->d = malloc(size);
		if (n->d == NULL)
			goto dealloc;

		memcpy(n->d, d, size);
	}

	return n;

dealloc:
	free(n);
	return NULL;
}

static void free_node(struct node* const n, void (*const dtor)(void* d))
{
	assert(n != NULL);

	if (dtor == NULL)
		free(n->d);
	else
		dtor(n->d);

	free(n);
}

void ll_init(struct ll* const l, u32 dsize, void (*dtor)(void* d))
{
	assert(l != NULL);

	l->cnt   = 0;
	l->dsize = dsize;
	l->dtor  = dtor;
	l->head  = NULL;
}

void ll_destroy(struct ll* const l)
{
	assert(l != NULL);

	if (l->head == NULL)
		return;

	struct node* n = l->head;
	while (n != NULL) {
		l->head = n->next;
		free_node(n, l->dtor);
		n = l->head;
		l->cnt--;
	}
}

int ll_add(struct ll* const l, void* const d, bool prealloc)
{
	assert(l != NULL);
	assert(d != NULL);

	const u32 size = prealloc ? 0 : l->dsize;

	if (l->head == NULL) {
		l->head = create_node(d, size);
		if (l->head == NULL)
			return -ENOMEM;
	} else {
		struct node* n = l->head;
		while (n->next != NULL)
			n = n->next;

		n->next = create_node(d, size);
		if (n->next == NULL)
			return -ENOMEM;
	}

	l->cnt++;

	return 0;
}

void* ll_back(struct ll* const l)
{
	assert(l != NULL);

	struct node* n = l->head;
	if (n == NULL)
		return NULL;

	while (true)
		if (n->next == NULL)
			return n->d;
		else
			n = n->next;
}

void* ll_get(struct ll* const l, u32 id)
{
	assert(l != NULL);

	u32 i = 0;
	ll_foreach (l)
		if (id == i++)
			return n->d;

	return NULL;
}

/**** END OF FILE ****/
