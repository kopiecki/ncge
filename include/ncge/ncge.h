/**
 * @file   ncge.h
 * @brief  ncurses game backend
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef NCGE_H_INCLUDED_
#define NCGE_H_INCLUDED_

#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>

#include "ncge/ll.h"
#include "ncge/vec2.h"

/**
 * @brief Exit code, return this if you want to close main loop
 */
#define NCGE_EXIT 0xC0FFEE

/**
 * @brief ESC key code
 */
#define KEY_ESC 27

/**
 * @brief Window configuration
 */
struct win_cfg {
	struct vec2 dim; /**< Window dimensions*/
	struct vec2 pos; /**< Window position*/
	bool border;     /**< Border indicator*/
};

/**
 * @brief Backend states
 */
enum state {
	STATE_INIT, /**< Initialization state*/
	STATE_PLAY, /**< Play state*/
	STATE_LOSE, /**< Lose state*/
	STATE_EXIT, /**< Exit state*/
	NUM_STATES, /**< Enum guard*/
};

/**
 * @brief Forward declaration for \p struct ncge_ops
 */
struct ncge;

/**
 * @brief Game loop operation callbacks
 */
struct ncge_ops {
	int (*on_frame)(struct ncge* const ctx); /**< On frame callback*/
	int (*state_ops[NUM_STATES])(struct ncge* const ctx); /**< States callback*/
};

/**
 * @brief Backend representation
 */
struct ncge {
	enum state state;           /**< Current state*/
	const struct ncge_ops* ops; /**< Game loop operations*/
	u32 delay_step;             /**< Wait period between frames*/
	struct ll wins;             /**< List with windows*/
	struct ll boards;           /**< List with boards*/
};

/**
 * @brief Initialize ncurses game backend
 *
 * @param[in] ctx        Instance pointer
 * @param[in] ops        Game loop operations
 * @param[in] delay_step Frame delay
 * @return int           0 on success, negative error code otherwise
 */
int ncge_init(
	struct ncge* const ctx, const struct ncge_ops* const ops, u32 delay_step);

/**
 * @brief Destriy ncurses backend
 *
 * @param[in] ctx Instance pointer
 */
void ncge_destroy(struct ncge* const ctx);

/**
 * @brief Create new window
 *
 * @param[in] ctx  Instance pointer
 * @param[in] cfg  Window config
 * @return int     0 on success, negative errno otherwise
 */
int ncge_create_win(struct ncge* const ctx, const struct win_cfg* const cfg);

/**
 * @brief Create new board
 *
 * @param[in] ctx Instance pointer
 * @param[in] id  Window ID (board wraps window)
 * @return int    0 on success, negative errno otherwise
 */
int ncge_create_board(struct ncge* const ctx, u32 id);

/**
 * @brief Run game loop
 *
 * @param[in] ctx Instance pointer
 * @return int    0 on success, negative errno otherwise
 */
int ncge_run(struct ncge* const ctx);

/**
 * @brief Get window by id
 *
 * @param[in] ctx  Instance pointer
 * @param[in] id   Window id
 * @return WINDOW* Obtained window
 */
static inline WINDOW* ncge_get_win(struct ncge* const ctx, u32 id)
{
	return ll_get(&ctx->wins, id);
}

/**
 * @brief Get board by id
 *
 * @param[in] ctx        Instance pointer
 * @param[in] id         Board id
 * @return struct board* Obtained board
 */
static inline struct board* ncge_get_board(struct ncge* const ctx, u32 id)
{
	return ll_get(&ctx->boards, id);
}

#endif /* NCGE_H_INCLUDED_ */

/**** END OF FILE ****/
