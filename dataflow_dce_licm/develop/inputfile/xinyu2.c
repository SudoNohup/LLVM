#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int test1(int a, int b) {
    int x = 1;
    int y = 1;
    int z = 1;
    long long int count = 1;
    long long int count1 = 1;
    int i = 0;
    int j = 0;
    for (i = 0; i < 30; i ++) {
        do {
            z = a + b;
            //printf("%s%d\n", "z is ", z);
            for (j = 0; j < 30; j ++) {
                do {
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    y = a + b;
                    //printf("%s%d\n", "y is ", y);
                    x = a + b;
                    x = a + b;
                    x = a + b;
                    x = a + b;
                    x = a + b;
                    x = a + b;
                    x = a + b;
                    x = a + b;
                    x = a + b;
                    //printf("%s%d\n", "x is ", x);
                    count ++;
                } while (count < 300000000);
                if (x > 10) {
                    break;
                }
            }
            count1 ++;
        } while (count1 < 30000);     
    } 

    //printf("%s%d\n", "z is ", z);
    //printf("%s%d\n", "y is ", y);
    //printf("%s%d\n", "x is ", x);
    return a;
}


int main() {
    clock_t start, finish;
    double  duration;
    int a = 1, b = 2;

    start = clock();
    
    test1(a, b);
       
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );

    return 0;
}


/*
int test2(int a, int b) {
    int x = 1;
    int y = 1;
    int z = 1;
    do {
        x = a + b;
        do {
            y = a + b;
            z = z + 1;
        } while ( b < 10);
    } while (a < 10);

    return a;
}
*/
