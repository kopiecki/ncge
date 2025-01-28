/**
 * @file   vec2.h
 * @brief  Generic vector with two elements
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef VEC2_H_INCLUDED_
#define VEC2_H_INCLUDED_

#include <stdbool.h>

#include "ncge/types.h"

/**
 * @brief Generic vector with two elements
 */
struct vec2 {
	i32 row; /**< X coordinate*/
	i32 col; /**< Y coordinate*/
};

/**
 * @brief Create vector
 *
 * @param[in] x            X coordinate
 * @param[in] y            Y coordinate
 * @return struct vec2
 */
static inline struct vec2 vec2_create(i32 x, i32 y)
{
	return (struct vec2) {
		.row = x,
		.col = y,
	};
}

/**
 * @brief Add vector to vector
 *
 * @param[in] lhs          Left hand side vector
 * @param[in] rhs          Right hand side vector
 * @return struct vec2 Result
 */
static inline struct vec2 vec2_add_v(const struct vec2 lhs, const struct vec2 rhs)
{
	return vec2_create(lhs.row + rhs.row, lhs.col + rhs.col);
}

/**
 * @brief Check if vectors are equal
 *
 * @param[in] lhs     Left hand side vector
 * @param[in] rhs     Right hand side vector
 * @return true   Equal
 * @return false  Not equal
 */
static inline bool vec2_eq(const struct vec2 lhs, const struct vec2 rhs)
{
	return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

#endif /* VEC2_H_INCLUDED_ */

/**** END OF FILE ****/
