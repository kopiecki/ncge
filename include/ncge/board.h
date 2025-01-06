/*
 * @file   board.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef BOARD_H_INCLUDED_
#define BOARD_H_INCLUDED_

#include <ncurses.h>

#include "ncge/types.h"

#define BLOCK ' ' | A_REVERSE
#define EMPTY ' '

struct board {
	WINDOW* w;
	struct cell** grid;
};

int board_init(struct board* const b, WINDOW* const w);
void board_destroy(struct board* const b);

void board_clear(struct board* const b);
int board_render(const struct board* const b);

#define board_at(b, p) ((b)->grid[(p).row][(p).col])

static inline int board_max_row(const struct board* const b)
{
	return getmaxy(b->w) - 1;
}

static inline int board_max_col(const struct board* const b)
{
	return getmaxx(b->w) - 1;
}

static inline struct vec2 board_max(const struct board* const b)
{
	return vec2_create(board_max_row(b), board_max_col(b));
}

static inline bool board_in(const struct board* const b, struct vec2 p)
{
	return (in_range(p.row, 0, board_max_row(b))
			&& in_range(p.col, 0, board_max_col(b)));
}

static inline bool board_is(const struct board* const b, struct vec2 p)
{
	return cell_neq(board_at(b, p), CELL_EMPTY);
}

#endif /* BOARD_H_INCLUDED_ */

/**** END OF FILE ****/
