#include <stdio.h>
int cond3(int u, int v) {
	int j;
	int x = 1;
	do {
		printf("%d", x);
		x = 4;
		if (u < v) {
			++u;
		}
		--v;
	} while(v >= 9);
	j = x;
	return j;
}
