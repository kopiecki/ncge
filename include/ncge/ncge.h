/*
 * @file   ncge.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef NCGE_H_INCLUDED_
#define NCGE_H_INCLUDED_

#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>

#include "ncge/ll.h"
#include "ncge/types.h"

#define NCGE_EXIT 0xC0FFEE

struct win_cfg {
	struct vec2 dim;
	struct vec2 pos;
	bool border;
};

enum state {
	state_init,
	state_play,
	state_lose,
	state_exit,
	num_states,
};

struct ncge;

struct ncge_ops {
	int (*on_frame)(struct ncge* const ctx);
	int (*state_ops[num_states])(struct ncge* const ctx);
};

struct ncge {
	enum state state;
	const struct ncge_ops* ops;
	u32 delay_step;
	struct ll wins;
	struct ll boards;
};

int ncge_init(
	struct ncge* const ctx, const struct ncge_ops* const ops, u32 delay_step);
void ncge_destroy(struct ncge* const ctx);

int ncge_create_win(struct ncge* const ctx, const struct win_cfg* const cfg);
int ncge_create_board(struct ncge* const ctx, u32 id);

int ncge_run(struct ncge* const ctx);

static inline WINDOW* ncge_get_win(struct ncge* const ctx, u32 id)
{
	return ll_get(&ctx->wins, id);
}

static inline struct board* ncge_get_board(struct ncge* const ctx, u32 id)
{
	return ll_get(&ctx->boards, id);
}

#endif /* NCGE_H_INCLUDED_ */

/**** END OF FILE ****/
