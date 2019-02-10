#include "alloc.h"


long double fact(int N)
{
	if (N < 0) return 0;
	else if (N == 0)
		return 1;
	else
		return N * fact(N - 1);
}

