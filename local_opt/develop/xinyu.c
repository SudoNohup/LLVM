#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

signed int testSi32 (signed int a, signed int b) {
  signed int result = 2;

  // constant folding 
  signed int x = INT_MAX - 40000;
  signed int y = 3;
  signed int z = 0;
  signed int w = 1;

  printf("%s\n", "---------------test signed i64---------------");
  result = x + y;
  printf("%d\n", result);
  result -= y; 
  printf("%d\n", result);
  result *= x; // overflow
  printf("%d\n", result);
  result /= y; 
  printf("%d\n", result);
  // dump
  //result /= z;
  //printf("%d\n", result);


  // indentity
  result += z;
  printf("%d\n", result);
  result = z + y;
  printf("%d\n", result);
  result -= x;
  printf("%d\n", result);
  result *= w;
  printf("%d\n", result);
  result = w * x;
  printf("%d\n", result);
  result *= z;
  printf("%d\n", result);
  result = z * result;
  printf("%d\n", result);
  result = a / w;
  printf("%d\n", result);
  result = a - a;
  printf("%d\n", result);
  result = b / b;
  printf("%d\n", result);
  // dump
  //result = y / z;
  //printf("%d\n", result);

  // reduction
  result = 16 * a;
  printf("%d\n", result);
  result *= 16;
  printf("%d\n", result);
  result /= 4;
  printf("%d\n", result);
  result /= 5;
  printf("%d\n", result);
  result *= 19;
  printf("%d\n", result);
  result = a * 7;
  printf("%d\n", result);
  result = a >> 4;
  printf("%d\n", result);

  printf("%s\n", "----------------Extensive Tests-------------");
  result = 5 * a;
  printf("%d\n", result);
  result *= 10;
  printf("%d\n", result);
  result = 12 * result;
  printf("%d\n", result);

  result = (2 + a) + 3 + b + 6;
  printf("%d\n", result);
  result = (a * 5) * b * (7 * a);
  printf("%d\n", result);
  result = (a >> 2) >> 3 >> 4;
  printf("%d\n", result);
  result = (a << 2) << 4 << 3;
  printf("%d\n", result);
  result = (a / 4) / 4 / 20;
  printf("%d\n", result);
  result = (a + 5) - b + 3 - (2 * a) + 3;
  printf("%d\n", result);

  


  return result;
}

signed long long int testSi64 (signed long long int a, signed long long int b) {
  signed long long int result;
  signed long long int x = LONG_MAX - 40000;
  signed long long int y = 3;
  signed long long int z = 0;
  signed long long int w = 1;

  printf("%s\n", "---------------test signed i64---------------");
  result = x + y;
  printf("%llo\n", result);
  result -= y; 
  printf("%llo\n", result);
  result *= x; // overflow
  printf("%llo\n", result);
  result /= y; 
  printf("%llo\n", result);
  // dump
  //result /= z;
  //printf("%d\n", result);


  // indentity
  result += z;
  printf("%llo\n", result);
  result = z + y;
  printf("%llo\n", result);
  result -= x;
  printf("%llo\n", result);
  result *= w;
  printf("%llo\n", result);
  result = w * x;
  printf("%llo\n", result);
  result *= z;
  printf("%llo\n", result);
  result = z * result;
  printf("%llo\n", result);
  result = a / w;
  printf("%llo\n", result);
  result = a - a;
  printf("%llo\n", result);
  result = b / b;
  printf("%llo\n", result);
  // dump
  //result = y / z;
  //printf("%llo\n", result);

  // reduction
  result = 16 * a;
  printf("%llo\n", result);
  result *= 16;
  printf("%llo\n", result);
  result /= 4;
  printf("%llo\n", result);
  result /= 5;
  printf("%llo\n", result);
  result *= 19;
  printf("%llo\n", result);
  result = a * 7;
  printf("%llo\n", result);
  result = a >> 4;
  printf("%llo\n", result);

  printf("%s\n", "----------------Extensive Tests-------------");
  result = 5 * a;
  printf("%llo\n", result);
  result *= 10;
  printf("%llo\n", result);
  result = 12 * result;
  printf("%llo\n", result);

  result = (2 + a) + 3 + b + 6;
  printf("%llo\n", result);
  result = (a * 5) * b * (7 * a);
  printf("%llo\n", result);
  result = (a >> 2) >> 3 >> 4;
  printf("%llo\n", result);
  result = (a << 2) << 4 << 3;
  printf("%llo\n", result);
  result = (a / 4) / 4 / 20;
  printf("%llo\n", result);
  result = (a + 5) - b + 3 - (2 * a) + 3;
  printf("%llo\n", result);
  return result;
}

unsigned int testUi32 (unsigned int a, unsigned int b) {
  unsigned int result = 2;

  // constant folding 
  unsigned int x = UINT_MAX - 40000;
  unsigned int y = 3;
  unsigned int z = 0;
  unsigned int w = 1;

  printf("%s\n", "---------------test unsigned i32---------------");
  result = x + y;
  printf("%u\n", result);
  result -= y; 
  printf("%u\n", result);
  result *= x; // overflow
  printf("%u\n", result);
  result /= y; 
  printf("%u\n", result);
  // dump
  //result /= z;
  //printf("%d\n", result);


  // indentity
  result += z;
  printf("%u\n", result);
  result = z + y;
  printf("%u\n", result);
  result -= x;
  printf("%u\n", result);
  result *= w;
  printf("%u\n", result);
  result = w * x;
  printf("%u\n", result);
  result *= z;
  printf("%u\n", result);
  result = z * result;
  printf("%u\n", result);
  result = a / w;
  printf("%u\n", result);
  result = a - a;
  printf("%u\n", result);
  result = b / b;
  printf("%u\n", result);
  // dump
  //result = y / z;
  //printf("%u\n", result);

  // reduction
  result = 16 * a;
  printf("%u\n", result);
  result *= 16;
  printf("%u\n", result);
  result /= 4;
  printf("%u\n", result);
  result /= 5;
  printf("%u\n", result);
  result *= 19;
  printf("%u\n", result);
  result = a * 7;
  printf("%u\n", result);
  result = a / 16;
  printf("%u\n", result);

  printf("%s\n", "----------------Extensive Tests-------------");
  result = 5 * a;
  printf("%u\n", result);
  result *= 10;
  printf("%u\n", result);
  result = 12 * result;
  printf("%u\n", result);

  result = (2 + a) + 3 + b + 6;
  printf("%u\n", result);
  result = (a * 5) * b * (7 * a);
  printf("%u\n", result);
  result = (a >> 2) >> 3 >> 4;
  printf("%u\n", result);
  result = (a << 2) << 4 << 3;
  printf("%u\n", result);
  result = (a / 4) / 4 / 20;
  printf("%u\n", result);
  result = (a + 5) - b + 3 - (2 * a) + 3;
  printf("%u\n", result);
  return result;
}

unsigned int long long testUi64 (unsigned long long int a, unsigned long long int b) {
  unsigned long long int result = 2;

  // constant folding 
  unsigned long long int x = UINT_MAX - 40000;
  unsigned long long int y = 3;
  unsigned long long int z = 0;
  unsigned long long int w = 1;

  printf("%s\n", "---------------test unsigned i64---------------");
  result = x + y;
  printf("%llu\n", result);
  result -= y; 
  printf("%llu\n", result);
  result *= x; // overflow
  printf("%llu\n", result);
  result /= y; 
  printf("%llu\n", result);
  // dump
  //result /= z;
  //printf("%d\n", result);


  // indentity
  result += z;
  printf("%llu\n", result);
  result = z + y;
  printf("%llu\n", result);
  result -= x;
  printf("%llu\n", result);
  result *= w;
  printf("%llu\n", result);
  result = w * x;
  printf("%llu\n", result);
  result *= z;
  printf("%llu\n", result);
  result = z * result;
  printf("%llu\n", result);
  result = a / w;
  printf("%llu\n", result);
  result = a - a;
  printf("%llu\n", result);
  result = b / b;
  printf("%llu\n", result);
  // dump
  //result = y / z;
  //printf("%u\n", result);

  // reduction
  result = 16 * a;
  printf("%llu\n", result);
  result *= 16;
  printf("%llu\n", result);
  result /= 4;
  printf("%llu\n", result);
  result /= 5;
  printf("%llu\n", result);
  result *= 19;
  printf("%llu\n", result);
  result = a * 7;
  printf("%llu\n", result);
  result = a / 16;
  printf("%llu\n", result);

  printf("%s\n", "----------------Extensive Tests-------------");
  result = 5 * a;
  printf("%llu\n", result);
  result *= 10;
  printf("%llu\n", result);
  result = 12 * result;
  printf("%llu\n", result);

  result = (2 + a) + 3 + b + 6;
  printf("%llu\n", result);
  result = (a * 5) * b * (7 * a);
  printf("%llu\n", result);
  result = (a >> 2) >> 3 >> 4;
  printf("%llu\n", result);
  result = (a << 2) << 4 << 3;
  printf("%llu\n", result);
  result = (a / 4) / 4 / 20;
  printf("%llu\n", result);
  result = (a + 5) - b + 3 - (2 * a) + 3;
  printf("%llu\n", result);

  result = 2 + a;

  int zero = 0;
  result = result / zero;

  return result;
}

int main() {
  signed int t1_1 = 3, t1_2 = 8;
  signed int a1 = testSi32(t1_1, t1_2);

  signed long long int t2_1 = 2, t2_2 = 7;
  signed long long int a2 = testSi64(t2_1, t2_2);

  unsigned int t3_1 = 3, t3_2 = 5;
  unsigned int a3 = testUi32(t3_1, t3_2);

  unsigned long long int t4_1 = 7, t4_2 = 3;
  unsigned int a4 = testUi64(t4_1, t4_2);

  return 0;
}

