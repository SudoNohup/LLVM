#include <stdio.h>
int compute(int a) {
	int res;
	res = a/a;
	return res;
}

int main() {
	printf("%d\n", compute(0));
	return 0;
}
