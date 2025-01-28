/**
 * @file   ncge.c
 * @brief  ncurses game backend
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#include "ncge/ncge.h"

#include <assert.h>
#include <errno.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "ncge/board.h"
#include "ncge/ll.h"

#define DELAY_INIT INT16_MAX
#define DELAY_STEP (1 << 9)
#define DELAY_INC  (1 << 6)

static const u8 colors[] = {
	COLOR_CYAN,  COLOR_YELLOW, COLOR_BLUE,  COLOR_MAGENTA,
	COLOR_GREEN, COLOR_RED,    COLOR_WHITE, COLOR_BLACK,
};

static inline void win_dtor(void* w)
{
	delwin(w);
}

static inline void board_dtor(void* b)
{
	board_destroy(b);
}

static int create_colors(void)
{
	if (has_colors() == FALSE)
		return ERR;

	int err = use_default_colors();
	if (err < 0)
		return err;

	err = start_color();
	if (err < 0)
		return err;

	for (u8 i = 0; i < ARR_SIZE(colors); i++) {
		err = init_pair(i + 1, colors[i], -1);
		if (err < 0)
			return err;
	}

	return err;
}

static int create_env(void)
{
	if (initscr() == NULL)
		return ERR;

	int err = cbreak();
	if (err < 0)
		return err;

	err = keypad(stdscr, 1);
	if (err < 0)
		return err;

	err = noecho();
	if (err < 0)
		return err;

	err = curs_set(0);
	if (err < 0)
		return err;

	timeout(1);
	srand((u32)time(NULL));

	err = atexit((void (*)(void))endwin);
	if (err < 0)
		return err;

	err = create_colors();
	if (err < 0)
		return err;

	return wrefresh(stdscr);
}

static int update(struct ncge* const ctx)
{
	ll_foreach (&ctx->boards) {
		const int err = board_render(n->d);
		if (err < 0)
			return err;
	}

	ll_foreach (&ctx->wins) {
		const int err = wrefresh(n->d);
		if (err < 0)
			return err;
	}

	return 0;
}

int ncge_init(struct ncge* const ctx, const struct ncge_ops* const ops, u32 delay_step)
{
	assert(ctx != NULL);
	assert(ops != NULL);

	const int err = create_env();
	if (err < 0)
		return err;

	ll_init(&ctx->wins, sizeof(WINDOW*), win_dtor);
	ll_init(&ctx->boards, sizeof(struct board), board_dtor);

	ctx->state      = STATE_INIT;
	ctx->ops        = ops;
	ctx->delay_step = (delay_step == 0) ? DELAY_STEP : delay_step;

	return 0;
}

void ncge_destroy(struct ncge* const ctx)
{
	assert(ctx != NULL);

	ll_destroy(&ctx->wins);
	ll_destroy(&ctx->boards);

	ctx->state = STATE_EXIT;
}

int ncge_create_win(struct ncge* const ctx, const struct win_cfg* const cfg)
{
	assert(ctx != NULL);
	assert(cfg != NULL);

	WINDOW* w = newwin(cfg->dim.row, cfg->dim.col, cfg->pos.row, cfg->pos.col);
	if (w == NULL)
		return -ENOMEM;

	int err = 0;
	if (cfg->border) {
		err = box(w, 0, 0);
		if (err < 0)
			goto dealloc;
	}

	err = wrefresh(w);
	if (err < 0)
		goto dealloc;

	err = ll_add(&ctx->wins, w, true);
	if (err < 0)
		goto dealloc;

	return 0;

dealloc:
	win_dtor(w);
	return err;
}

int ncge_create_board(struct ncge* const ctx, u32 id)
{
	assert(ctx != NULL);

	struct board* const b = malloc(sizeof(struct board));
	if (b == NULL)
		return -ENOMEM;

	WINDOW* w = ll_get(&ctx->wins, id);
	if (w == NULL)
		return -ENODATA;

	int err = board_init(b, w);
	if (err < 0)
		return err;

	err = ll_add(&ctx->boards, b, true);
	if (err < 0)
		goto dealloc;

	return 0;

dealloc:
	board_dtor(b);
	return err;
}

int ncge_run(struct ncge* const ctx)
{
	assert(ctx != NULL);

	i32 delay = DELAY_INIT;

	while (true) {
		delay -= (i32)ctx->delay_step;
		if (delay < 0) {
			int err = ctx->ops->on_frame(ctx);
			if (err < 0)
				return err;

			delay = INT16_MAX;
		}

		int err = ctx->ops->state_ops[ctx->state](ctx);
		if (err < 0)
			return err;
		if (err == NCGE_EXIT)
			break;

		err = update(ctx);
		if (err < 0)
			return err;
	}

	return 0;
}

/**** END OF FILE ****/
