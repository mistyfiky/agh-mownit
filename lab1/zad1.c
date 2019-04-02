#include <stdio.h>

float f_calc(float xn) {
    float a, b, c, d;
    a = 1 - xn;
    b = xn * a;
    c = 3.0 * b;
    d = xn + c;
    return d;
}

double d_calc(double xn) {
    double a, b, c, d;
    a = 1 - xn;
    b = xn * a;
    c = 3.0 * b;
    d = xn + c;
    return d;
}

int main() {
    int n = 100;
    float f_xn = 0.01;
    double d_xn = 0.01;
    printf("n\tfloat\tdouble\n");
    for (int i = 0; i < n; i++) {
        printf("%i\t%.30f\t%.30lf\n", i, f_xn, d_xn);
        f_xn = f_calc(f_xn);
        d_xn = d_calc(d_xn);
    }
    return 0;
}
