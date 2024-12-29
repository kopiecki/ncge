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

#define board_at(b, p)   ((b)->grid[(p).row][(p).col])
#define board_max_row(b) (getmaxy(b->w) - 1)
#define board_max_col(b) (getmaxx(b->w) - 1)
#define board_max(b)     vec2_create(board_max_row(b), board_max_col(b))
#define board_is(b, p)   (board_at(b, p) != CELL_EMPTY)

#define board_in(b, p)                                                         \
	(in_range(p.row, 0, board_max_row(b))                                      \
	 && in_range(p.col, 0, board_max_col(b)))

int board_init(struct board* const b, WINDOW* const w);
void board_destroy(struct board* const b);

void board_clear(struct board* const b);
int board_render(const struct board* const b);

#endif /* BOARD_H_INCLUDED_ */

/**** END OF FILE ****/
