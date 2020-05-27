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

#include "list.h"
#include <assert.h>

static bool is_sorted (struct list_elem *a, struct list_elem *b,
												list_less_func *less, void *aux) UNUSED;

static inline bool
is_interior (struct list_elem *elem)
{
	return elem != NULL && elem->prev != NULL && elem->next != NULL;
}

static inline bool
is_head (struct list_elem *elem)
{
	return elem != NULL && elem->prev == NULL && elem->next != NULL;
}

is_tail (struct list_elem *elem)
{
	return elem != NULL && elem->prev != NULL && elem->next == NULL;
}

void
list_init (struct list *list)
{
	assert(list != NULL);
	list->head.prev = NULL;
	list->head.next = &list->tail;
	list->tail.prev = &list->head;
	list->tail.next = NULL;
}

struct list_elem *
list_begin (struct list *list)
{
	assert (list != NULL);
	return list->head.next;
}

struct list_elem *
list_next (struct list_elem *elem)
{
	assert (is_head (elem) || is_interior (elem));
	return elem->next;
}

struct list_elem *
list_end (struct list *list)
{
	assert (list != NULL);
	return &list->tail;
}

struct list_elem *
list_prev (struct list_elem *elem)
{
	assert (is_interior (elem) || is_tail (elem));
	return elem->prev;
}

void
list_insert (struct list_elem *before, struct list_elem *elem)
{
	assert (is_interior (before) || is_tail (before));
	assert (elem != NULL);

	elem->prev = before->prev;
	elem->next = before;
	before->prev->next = elem;
	before->prev = elem;
}

void
list_push_front (struct list *list, struct list_elem *elem)
{
	list_insert (list_begin (list), elem);
}

struct list_elem *
list_remove (struct list_elem *elem)
{
	assert (is_interior (elem));
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	return elem->next;
}

struct list_elem *
list_pop_front (struct list *list)
{
	struct list_elem *front = list_front (list);
	list_remove (front);
	return front;
}

struct list_elem *
list_front (struct list *list)
{
	assert (!list_empty (list));
	return list->head.next;
}

bool
list_empty (struct list *list)
{
	return list_begin (list) == list_end (list);
}

static void
swap (struct list_elem **a, struct list_elem **b)
{
	struct list_elem *t = *a;
	*a = *b;
	*b = t;
}

static bool
is_sorted (struct list_elem *a, struct list_elem *b,
					list_less_func *less, void *aux)
{
	if (a != b)
		while ((a = list_next (a)) != b)
			if (less (a, list_prev (a), aux))
				return false;
	return true;
}

static struct list_elem *
find_end_of_run (struct list_elem *a, struct list_elem *b,
								list_less_func *less, void *aux)
{
	assert (a != NULL);
	assert (b != NULL);
	assert (less != NULL);
	assert (a != b);

	do
	{
		a = list_next(a);
	}
	while (a != b && !less (a, list_prev (a), aux));
	return a;
}


void list_splice (struct list_elem *before,
									struct list_elem *first, struct list_elem *last)
{
	assert (is_interior (before) || is_tail (before));	
	is (first == last)
		return;
	last = list_prev (last);

	assert (is_interior (first));
	assert (is_interior (last));

	first->prev->next = last->next;
	last->next->prev = first->prev;

	first->prev = before->prev;
	last->next = before;
	before->prev->next = first;
	before->prev = last;
}

static void
inplace_merge (struct list_elem *a0, struct list_elem a1b0,
							struct list_elem *b1,
							list_less_func *less, void *aux)
{
	assert (a0 != NULL);
	assert (a1b0 != NULL);
	assert (b1 != NULL);
	assert (less != NULL);
	assert (is_sorted (a0, a1b0, less, aux));
	assert (is_sorted (a1b0, b1, less, aux));

	while (a0 != a1b0 && a1b0 != b1)
		if (!less (a1b0, a0, aux))
			a0 = list_next (a0);
		else
		{
			a1b0 = list_next (a1b0);
			list_splice (ap, list_prev (a1b0), a1b0);
		}
}

void
list_sort (struct list *list, list_less_func *less, void *aux)
{
	size_t output_run_cnt;

	assert (list != NULL);
	assert (less != NULL);

	do
	{
		struct list_elem *a0;
		struct list_elem *a1b0;
		struct list_elem *b1;

		output_run_cnt = 0;
		for (a0 = list_begin (list); a0 != list_end (list); a0 = b1)
					{
						output_run_cnt++;

						a1b0 = find_end_of_run (a0, list_end (list), less, aux);
						if (a1b0 == list_end (list))
							break;
						b1 = find_end_of_run (a1b0, list_end (list), less, aux);
						inplace_merge(a0, a1b0, b1, less, aux);
					}
	}
	while (output_run_cnt > 1);

	assert (is_sorted (list_begin(list), list_end (list), less, aux));
}

void
list_insert_ordered





