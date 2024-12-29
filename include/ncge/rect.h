/*
 * @file   rect.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef RECT_H_INCLUDED_
#define RECT_H_INCLUDED_

#include <assert.h>

#include "ncge/board.h"
#include "ncge/types.h"

struct rect {
	struct vec2 left;
	struct vec2 right;
	enum color col;
};

#define rect_create(p, c)                                                      \
	(struct rect)                                                              \
	{                                                                          \
		.left = (p), .right = { (p).row, (p).col + 1 }, (c)                    \
	}

static inline void rect_fill(struct rect* const r, struct vec2 p, enum color c)
{
	assert(r != NULL);

	r->col   = c;
	r->left  = p;
	r->right = p;
	r->right.col++;
}

static inline void rect_draw(const struct rect* const r, struct board* const b)
{
	assert(r != NULL);
	assert(b != NULL);

	board_at(b, r->left)  = cell_create(BLOCK, r->col);
	board_at(b, r->right) = cell_create(BLOCK, r->col);
}

static inline bool rect_eq(const struct rect* const lhs, const struct rect* const rhs)
{
	assert(lhs != NULL);
	assert(rhs != NULL);

	return vec2_eq(lhs->right, rhs->right) || vec2_eq(lhs->left, rhs->left);
}

#endif /* RECT_H_INCLUDED_ */

/**** END OF FILE ****/
