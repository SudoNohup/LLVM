int test1(int t) {
int x = t;
x = x + 1;
int a = x + 2;
int b = a - 3;
int c = a + b;

return 0;
}

int test2(int t) {
int x = 1;
for (int i = 0; i < t; i ++) {
x = x + 1;
}

return 0;
}

int test3(int t) {
int x = t;
x = x + 1;
int a = x + 2;
int b = a - 3;
int c = a + b;

return c;
}

int test4(int t) {
int x = t;
x = x + 1;
int a = x + 2;
int b = a - 3;
int c = a + b;

return a;
}
