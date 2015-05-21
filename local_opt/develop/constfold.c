int compute ()
{
  int result = 0;
  int a = 2;
  int b = 1 + 2;
  int c = 4 + a + b;
  
  result += a;
  result -= b;
  result *= c;
  result /= 2;
  return result;
}
