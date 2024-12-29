/*
 * @file   board.c
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#include "ncge/board.h"

#include <asm-generic/errno.h>
#include <assert.h>
#include <ncurses.h>
#include <stdlib.h>

#include "ncge/types.h"

static int board_put(const struct board* const b, struct vec2 p)
{
	const struct cell cl = board_at(b, p);

	int err = wattron(b->w, COLOR_PAIR(cl.c));
	if (err < 0)
		return err;

	err = mvwaddch(b->w, p.row, p.col, cl.ch);
	if (err < 0)
		return err;

	return wattroff(b->w, COLOR_PAIR(cl.c));
}

int board_init(struct board* const b, WINDOW* const w)
{
	assert(b != NULL);
	assert(w != NULL);

	b->w                  = w;
	const struct vec2 max = board_max(b);

	b->grid = calloc((u32)max.row, sizeof(struct cell*));
	if (b->grid == NULL)
		return -ENOMEM;

	for (u32 row = 0; row < (u32)max.row; row++) {
		b->grid[row] = calloc((u32)max.col, sizeof(struct cell));
		if (b->grid[row] == NULL)
			return -ENOMEM;
	}

	board_clear(b);

	return 0;
}

void board_destroy(struct board* const b)
{
	assert(b != NULL);
	assert(b->grid != NULL);

	const struct vec2 max = board_max(b);
	for (u32 row = 0; row < (u32)max.row; row++)
		free(b->grid[row]);

	free(b->grid);
}

void board_clear(struct board* const b)
{
	struct vec2 p         = { 0, 0 };
	const struct vec2 max = board_max(b);

	for (; p.row < max.row; p.row++)
		for (p.col = 1; p.col < max.col; p.col++)
			board_at(b, p) = CELL_EMPTY;
}

int board_render(const struct board* const b)
{
	assert(b != NULL);
	assert(b->grid != NULL);
	assert(b->w != NULL);

	struct vec2 p         = { 1, 1 };
	const struct vec2 max = board_max(b);

	for (; p.row < max.row; p.row++) {
		for (p.col = 1; p.col < max.col; p.col++) {
			const int err = board_put(b, p);
			if (err < 0)
				return err;
		}
	}

	return 0;
}

/**** END OF FILE ****/
