#include <stdio.h>
int compute(int x) {
	int y = 2;
	int z = x / y;
	return z;
}

int main() {
	printf("%d", compute(-5));
	return 0;
}
