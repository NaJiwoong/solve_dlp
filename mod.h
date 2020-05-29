#include <stdint.h>

int64_t modmult(int64_t a, int64_t b, int64_t N);

int64_t mod(int64_t N,int64_t b,int64_t e);

int64_t inverse(int64_t a,int64_t N);

int64_t moddiv(int64_t a, int64_t b, int64_t p);

int64_t modplus(int64_t a, int64_t b, int64_t p);

int64_t modminus(int64_t a, int64_t b, int64_t p);

int64_t gcd(int64_t a, int64_t b);

int64_t * factorize(int64_t g, int64_t k, int64_t p, int64_t * s, int64_t plus, int len);
