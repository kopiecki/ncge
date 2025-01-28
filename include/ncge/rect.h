/**
 * @file   rect.h
 * @brief  Drawable rectangle
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef RECT_H_INCLUDED_
#define RECT_H_INCLUDED_

#include <assert.h>

#include "ncge/board.h"
#include "ncge/types.h"

/**
 * @brief   Aggregated rectangle data
 * @details Since we're working with ASCII symbols, rectangle consists of two
 *          `blocks` - one on the left, one on the right.
 */
struct rect {
	struct vec2 left;  /**< Left block*/
	struct vec2 right; /**< Right block*/
	enum color col;    /**< Rectangle color*/
};

/**
 * @brief Create rectangle
 *
 * @param[in] p        Rectangle position
 * @param[in] c        Rectangle color
 * @return struct rect Created rectangle
 */
static inline struct rect rect_create(struct vec2 p, enum color c)
{
	return (struct rect) {
		.left  = p,
		.right = { p.row, p.col + 1 },
		.col   = c,
	};
}

/**
 * @brief Fill rectangle data
 *
 * @param[in] r Rectangle to fill
 * @param[in] p Position
 * @param[in] c Color
 */
static inline void rect_fill(struct rect* const r, struct vec2 p, enum color c)
{
	assert(r != NULL);

	r->col   = c;
	r->left  = p;
	r->right = p;
	r->right.col++;
}

/**
 * @brief Draw rectangle on the board
 *
 * @param[in] r Rectangle to draw
 * @param[in] b Board on which we're drawing
 */
static inline void rect_draw(const struct rect* const r, struct board* const b)
{
	assert(r != NULL);
	assert(b != NULL);

	board_at(b, r->left)  = cell_create(BLOCK, r->col);
	board_at(b, r->right) = cell_create(BLOCK, r->col);
}

/**
 * @brief Check if two rectangles are equal (same position)
 *
 * @param lhs    Left hand side rectangle
 * @param rhs    Right hand side rectangle
 * @return true  Are equal
 * @return false Aren't equal
 */
static inline bool rect_eq(const struct rect* const lhs, const struct rect* const rhs)
{
	assert(lhs != NULL);
	assert(rhs != NULL);

	return vec2_eq(lhs->right, rhs->right) || vec2_eq(lhs->left, rhs->left);
}

#endif /* RECT_H_INCLUDED_ */

/**** END OF FILE ****/
