/**
 * @file   ll.h
 * @brief  Trivial singly linked list
 * @author Daniel Kopiecki <daniel.kopiecki@protonmail.com>
 * @date   2025-01-26
 *
 * @copyright Copyright (c) 2025 Daniel Kopiecki
 * @par       License: MIT
 */

#ifndef LL_H_INCLUDED_
#define LL_H_INCLUDED_

#include <stdbool.h>

#include "ncge/types.h"

/**
 * @brief Linked list node
 */
struct node {
	void* d;           /**< Data*/
	struct node* next; /**< Next node*/
};

/**
 * @brief Linked list representation
 */
struct ll {
	u32 dsize;             /**< Data size*/
	u32 cnt;               /**< Linked list size (element count)*/
	void (*dtor)(void* d); /**< Element destructor*/
	struct node* head;     /**< Linked list head*/
};

/**
 * @brief Cast linked list element to certain type
 */
#define ll_dcast(n, tp) *(tp*)((n)->d)

/**
 * @brief Iterate starting at `n` element
 */
#define ll_for(l, n) for (; n != NULL; n = n->next)

/**
 * @brief Iterate through whole list
 * @details Nodes are accessed via `n` variable
 */
#define ll_foreach(l) for (struct node* n = (l)->head; n != NULL; n = n->next)

/**
 * @brief Initialize linked list
 *
 * @param[in] l     Instance pointer
 * @param[in] dsize List size
 * @param[in] dtor  Element destructor, leave as NULL to select basic `free()`
 */
void ll_init(struct ll* const l, u32 dsize, void (*dtor)(void* d));

/**
 * @brief Destroy linked list
 *
 * @param[in] l Instance pointer
 */
void ll_destroy(struct ll* const l);

/**
 * @brief Add element to linked list
 *
 * @param[in] l        Instance pointer
 * @param[in] d        Data to add
 * @param[in] prealloc If yes, then element is preallocated
 * @return int         0 on success, negative errno otherwise
 */
int ll_add(struct ll* const l, void* const d, bool prealloc);

/**
 * @brief Get last element from list
 *
 * @param[in] l  Instance pointer
 * @return void* Last element
 */
void* ll_back(struct ll* const l);

/**
 * @brief Get element with specific index
 *
 * @param[in] l  Instance pointer
 * @param[in] id Element index
 * @return void* Element
 */
void* ll_get(struct ll* const l, u32 id);

#endif /* LL_H_INCLUDED_ */

/**** END OF FILE ****/
