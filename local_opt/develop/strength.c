#include <stdio.h>
int compute (int a, int b)
{
  int result = 3;
  
  result += a * 2;
  result += a * 3;
  result += a * 8;
  result -= b / 2;
  result -= b / 4;
  result -= b / 8;
  return result;
}

int main() {
	printf("%d", compute(1, 8));
	return 0;
}
