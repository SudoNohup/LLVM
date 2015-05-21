#include <stdio.h>
int compute (unsigned a) {
	//unsigned a = 2 << 31;
	return a / 16;
}
int main() {
	unsigned a = 1 << 31;
	printf("%d", compute(a));
	return 0;
}
