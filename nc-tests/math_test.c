#include <stdio.h>
#include <math.h>
#define PI 3.14159265
int main() {
    double x = 45.0, ret, val = PI/180;
    ret = sin(x*val);
    printf("The sine of %lf is %lf degrees\n", x, ret);
    return 0;
}
