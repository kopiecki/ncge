/**
 * @file   types.h
 * @brief  Common types and macros
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
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

/**
 * @brief Generic in range macro
 */
#define in_range(v, l, h) (((v) > (l)) && ((v) < (h)))

/**
 * @brief Enum with colors (duplicated from ncurses for verbosity)
 */
enum color {
	COL_NONE = 0,
	COL_CYAN,
	COL_YELLOW,
	COL_BLUE,
	COL_MAGENTA,
	COL_GREEN,
	COL_RED,
	NUM_COLS,
};

/**
 * @brief Directions
 */
enum dir {
	DIR_DOWN,
	DIR_UP,
	DIR_RIGHT,
	DIR_LEFT,
	NUM_DIRS,
};

#endif /* TYPES_H_INCLUDED_ */

/**** END OF FILE ****/
