/**
 * @file   cell.h
 * @brief  Board cell representation
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef CELL_H_INCLUDED_
#define CELL_H_INCLUDED_

#include "ncge/types.h"

/**
 * @brief Cell representation
 */
struct cell {
	u32 ch;       /**< Cell character*/
	enum color c; /**< Cell character color*/
};

/**
 * @brief Create cell
 *
 * @param ch            Cell character
 * @param c             Cell color
 * @return struct cell  Created cell
 */
static inline struct cell cell_create(u32 ch, enum color c)
{
	return (struct cell) {
		.ch = ch,
		.c  = c,
	};
}

/**
 * @brief Empty cell, whitespace as symbol with no color
 */
#define CELL_EMPTY cell_create(EMPTY, COL_NONE)

/**
 * @brief Check if cells are equal (same symbol and color)
 *
 * @param lhs    Left hand side cell
 * @param rhs    Right hand side cell
 * @return true  Are equal
 * @return false Aren't equal
 */
static inline bool cell_eq(const struct cell lhs, const struct cell rhs)
{
	return (lhs.c == rhs.c) && (lhs.ch == rhs.ch);
}

/**
 * @brief Check if cells are not equal
 *
 * @param lhs    Left hand side cell
 * @param rhs    Right hand side cell
 * @return true  Aren't equal
 * @return false Are equal
 */
static inline bool cell_neq(const struct cell lhs, const struct cell rhs)
{
	return (lhs.c != rhs.c) && (lhs.ch != rhs.ch);
}

#endif /* CELL_H_INCLUDED_ */

/**** END OF FILE ****/
