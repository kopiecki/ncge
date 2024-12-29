/*
 * @file   types.h
 *
 * SPDX-FileCopyrightText: 2024 Daniel Kopiecki
 * SPDX-License-Identifier: MIT
 */

#ifndef TYPES_H_INCLUDED_
#define TYPES_H_INCLUDED_

#include <stdbool.h>
#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;
typedef int64_t i64;
typedef int32_t i32;
typedef int8_t i8;

#define ARR_SIZE(arr) sizeof(arr) / sizeof(arr[0])
#define UNUSED(v)     (void)v

#define in_range(v, l, h) (((v) > (l)) && ((v) < (h)))

enum color {
	color_none,
	color_cyan,
	color_yellow,
	color_blue,
	color_magenta,
	color_green,
	color_red,
};

struct cell {
	u32 ch;
	enum color c;
};

#define cell_create(ch, c)                                                     \
	(struct cell)                                                              \
	{                                                                          \
		(ch), (c)                                                              \
	}

#define CELL_EMPTY cell_create(EMPTY, color_none)

enum dir {
	dir_down,
	dir_up,
	dir_right,
	dir_left,
};

struct vec2 {
	i32 row;
	i32 col;
};

#define vec2_create(row, col)                                                  \
	(struct vec2)                                                              \
	{                                                                          \
		(row), (col)                                                           \
	}

static inline struct vec2 vec2_add_v(const struct vec2 lhs, const struct vec2 rhs)
{
	return vec2_create(lhs.row + rhs.row, lhs.col + rhs.col);
}

static inline bool vec2_eq(const struct vec2 lhs, const struct vec2 rhs)
{
	return (lhs.row == rhs.row) && (lhs.col == rhs.col);
}

#endif /* TYPES_H_INCLUDED_ */

/**** END OF FILE ****/
