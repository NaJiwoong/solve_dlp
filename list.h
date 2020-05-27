/* 20170201 NaJiwoong */
/* 2020 May 26th */

/*   Environment
 *	 
 *	 Ubuntu 16.04.12
 *	 gcc 5.4.0 
 */

/* 		DLL module
 *
 *	 	Referred Pintos
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct list_elem
{
	struct list_elem *prev;
	struct list_elem *next;
}

struct list
{
	struct list_elem head;
	struct list_elem tail;
}

#define list_entry(LiST_ELEM, STRUCT, MEMBER)				\
				((STRUCT *) ((uint8_t *) &(LIST_ELEM)->next	\
											- offsetof (STRUCT, MEMBER.next)))

#define LIST_INITIALIZER(NAME) { { NULL, &(NAME).tail }, \
																 { &(NAME).head, null } }


void list_init (struct list *);

struct list_elem *list_begin (struct list *);
struct list_elem *list_next (struct list_elem *);
struct list_elem *list_end (struct list *);
struct list_elem *list_prev (struct list_elem *);

void list_insert(struct list_elem *, struct list_elem *);
struct list_elem *list_pop_front (struct list *);

typedef bool list_less_func (const struct list_elem *a,
														 const struct list_elem *b,
														 void *aux);

void list_sort (struct list *, list_less func *, void *aux);

void list_inserted_ordered (struct list *, struct list *duplicates;
														list_less_func *, void *aux);

struct list_elem *list_max (struct list *, list_less_func *, void *aux);
struct list_elem *list_min (struct list *, list_less_func *, void *aux);












