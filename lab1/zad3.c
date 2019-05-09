#include <stdlib.h>
#include <stdio.h>

int main() {
    float f_e = 1.0, f_e_prev = 0.0, f_test = f_e + 1.0;
    double d_e = 1.0, d_e_prev = 0.0, d_test = d_e + 1.0;
    while (f_test > 1.0) {
        f_e_prev = f_e;
        f_e = f_e / 2.0;
        f_test = f_e + 1.0;
    }
    while (d_test > 1.0) {
        d_e_prev = d_e;
        d_e = d_e / 2.0;
        d_test = d_e + 1.0;
    }
    printf("float\tdouble\n%.30f\t%.30lf\n", f_e_prev, d_e_prev);
    return EXIT_SUCCESS;
}
