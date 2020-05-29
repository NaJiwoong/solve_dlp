#include <stdint.h>

int independent(int64_t * a, int64_t * b, int64_t len);

int ref(int64_t ** m, int64_t row, int64_t col, int64_t p);

int ref2(int64_t ** m, int64_t row, int64_t col, int64_t p);

void rref(int64_t ** m, int64_t size, int64_t p);
