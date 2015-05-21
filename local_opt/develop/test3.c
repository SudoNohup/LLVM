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

  int p = -5;
  ub = 4;
  ua = ub/8; 
  x = p/2;
  
  printf("%d\n", x);
  printf("%lu\n", ua);

  /* Case: int */
  for (loopi = 0; loopi < b; loopi++ ) {
    x= LONG_MAX;
    y = 1;
    z = 1;
    x = x + z;
    z = x/y;
    y = y*z;
  }
  printf("x = %d, y = %d, z = %d\n", x, y, z); 

  /* Case: unsigned int */  
  ua = ULONG_MAX;
  ub = 0;
  uc = 1;
  uc = ua/ub;
  ua = ua + uc;
  ub = ub*uc;
  printf("ua = %lu, ub = %lu, uc = %lu\n", ua, ub, uc); 

  /* Case: long long int */
  la = LLONG_MAX;
  lb = 2;
  lc = 1;
  lc = la/lb;
  la = la + lc;
  lb = lb*lc;
  printf("la = %lld, lb = %lld, lc = %lld\n", la, lb, lc);

  /* Case: unsigned long long int */
  ula = ULLONG_MAX;
  ulb = 2;
  ulc = 1;
  ulc = ula/ulb;
  ula = ula + ulc;
  ulb = ulb*ulc;
  printf("ula = %llu, ulb = %llu, ulc = %llu\n", ula, ulb, ulc);
 
  /* Case: double */
  dx = 1.0;
  dy = 1.0;
  dz = 2.0;
  dz = dx/dy;
  dx = dx + dz;
  dy = dy*dz;
  printf("dx = %lf, dy = %lf, dz = %lf\n", dx, dy, dx);

  result *= (b/b);
  result += (b-b);
  result /= result;
  result -= result;

  return result;
}

int main() {
  int a = 1, b = 2;
  int answer = compute(a, b);
  return 0;
}

