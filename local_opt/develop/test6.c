#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

int compute (int a, int b)
{
  int result = (a/a);
  int x, y, z, loopi;
  long long int la, lb, lc;
  double dx, dy, dz;
  unsigned long int ua, ub, uc;
  unsigned long long int ula, ulb, ulc;
;
  
  /* Case: int */
    x= LONG_MAX;
    y = 0;
    z = 1;
    x = x + z;
    z = x/y;
    y = y*z;
  printf("x = %d, y = %d, z = %d\n", x, y, z); 
  return 1;
}

int main() {
  int a = 1, b = 2;
  int answer = compute(a, b);
  return 0;
}

