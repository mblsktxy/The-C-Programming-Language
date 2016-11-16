/*
 * Our binary search makes two tests inside the loop, when one would
 * suffice (at the price of more tests outside). Write a version with
 * only one test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Microsecond timestamp function */
int64_t utime_now(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int64_t) tv.tv_sec*1000000 + tv.tv_usec;
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch1(int x, int v[], int n)
{
    int low, high, mid;
    
    low = 0;
    high = n-1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
        	low = mid + 1;
        else
        	return mid;
    }
    return -1;
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch2(int x, int v[], int n)
{
    int low, high, mid;
    
    low = 0;
    high = n-1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid;
        else 
            low = mid + 1;
    }
    return (x == v[low]) ? low : -1;
}

int main(void)
{
    int v[10] = {1, 3, 6, 9, 12, 18, 20, 22, 24, 25};
    int x = 2;
    int index1, index2;
    int64_t t1, t2, t3, t4;

    t1 = utime_now();
    index1 = binsearch1(x, v, 10);
    t2 = utime_now();

    t3 = utime_now();
    index2 = binsearch2(x, v, 10);
    t4 = utime_now();

    printf("%d %d\n", index1, index2);
    printf("Used time: %ld\n", t2 - t1);
    printf("Used time: %ld\n", t4 - t3);
    return EXIT_SUCCESS;
}

