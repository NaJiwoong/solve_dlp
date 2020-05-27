#include <stdint.h>
#include <stdlib.h>

struct tuple{
	int64_t index;
	int64_t value;
};

int tupcmp (const void * a, const void * b);
void sort(struct tuple * list, size_t len);

int64_t * shanks(int64_t p, int64_t alpha, int64_t beta);
