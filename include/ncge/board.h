/**
 * @file   board.h
 * @brief  Board implementation
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef BOARD_H_INCLUDED_
#define BOARD_H_INCLUDED_

#include <ncurses.h>

#include "ncge/cell.h"
#include "ncge/vec2.h"

#define BLOCK ' ' | A_REVERSE
#define EMPTY ' '

/**
 * @brief   Board representation
 * @details Board is like a big matrix wrapping ncurses window. You can draw
 *          rectangles (cells), which resembles pixels on the specific board
 *          coordinates.
 */
struct board {
	WINDOW* w;          /**< ncurses window reference */
	struct cell** grid; /**< Board grid*/
};

/**
 * @brief Initialize board
 *
 * @param b    Instance pointer
 * @param w    ncurses window reference
 * @return int 0 on success, negative errno otherwise
 */
int board_init(struct board* const b, WINDOW* const w);

/**
 * @brief Destroy board
 *
 * @param b  Instance pointer
 */
void board_destroy(struct board* const b);

/**
 * @brief Clear board (set all coordinates to CELL_EMPTY)
 *
 * @param b Instance pointer
 */
void board_clear(struct board* const b);

/**
 * @brief Render board
 * @details Fill ncurses window with programmed grid
 *
 * @param b    Instance pointer
 * @return int 0 on success, negative errno otherwise
 */
int board_render(const struct board* const b);

/**
 * @brief Access specific board coordinate
 *
 * @param b Instance pointer
 * @param p Coordinates
 * @return  Board cell. You can write read or write to it (since it is a macro)
 */
#define board_at(b, p) ((b)->grid[(p).row][(p).col])

/**
 * @brief Get maximal board row
 *
 * @param b    Instance pointer
 * @return int Maximal row
 */
static inline int board_max_row(const struct board* const b)
{
	return getmaxy(b->w) - 1;
}

/**
 * @brief Get maximal board column
 *
 * @param b    Instance pointer
 * @return int Maximal column
 */
static inline int board_max_col(const struct board* const b)
{
	return getmaxx(b->w) - 1;
}

/**
 * @brief Get maximal row and column as vector
 *
 * @param b            Instance pointer
 * @return struct vec2 Maximal row and column
 */
static inline struct vec2 board_max(const struct board* const b)
{
	return vec2_create(board_max_row(b), board_max_col(b));
}

/**
 * @brief Check if certain coordinates are inside board grid
 *
 * @param b      Instance pointer
 * @param p      Coordinates
 * @return true  Are inside board
 * @return false Are outside board
 */
static inline bool board_in(const struct board* const b, struct vec2 p)
{
	return (
		in_range(p.row, 0, board_max_row(b))
		&& in_range(p.col, 0, board_max_col(b)));
}

/**
 * @brief Check if certain cell is empty
 *
 * @param b      Instance pointer
 * @param p      Coordinates
 * @return true  Is empty
 * @return false Is full
 */
static inline bool board_is(const struct board* const b, struct vec2 p)
{
	return cell_neq(board_at(b, p), CELL_EMPTY);
}

#endif /* BOARD_H_INCLUDED_ */

/**** END OF FILE ****/
