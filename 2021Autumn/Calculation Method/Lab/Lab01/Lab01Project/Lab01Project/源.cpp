#include <stdio.h>
#include <math.h>
#define epsilon 0.00001              //定义误差限
double f(double x) {                  //定义f函数
    return (x - 1) * (x - 1) * (x - 1) - x * x + x;
}
double h(double x) {                  //定义f'函数
    return 3 * (x - 1) * (x - 1) - 2 * x + 1;
}

int main() {
    double x;
    int i = 1;
    printf("choose an initial vaule between 2 and 3\n");
    scanf_s("%lf", &x);
    while ((fabs(f(x))) > epsilon) {
        x = x - f(x) / h(x);
        printf("iteration%d f(%lf)=%lf\n", i++, x, f(x));
    }
    printf("the result is %lf\n", x);
    return 0;
}