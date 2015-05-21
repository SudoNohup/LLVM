int g;
int loop (int a, int b, int c);
int g_incr (int c)
{
  g += c;
  loop(0, 1, 2);
  g_incr(c-1);
  loop(2, 3, 4);
  return 0;
}
int loop (int a, int b, int c)
{
  int i;
  int ret = 0;
  for (i = a; i < b; i++) {
   g_incr(c);
  }

  return ret + g;
}

