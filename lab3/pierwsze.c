#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_chebyshev.h>
#include <math.h>

double f1(double x, void *p) {
    (void) (p);
    double a = pow(x, 2);
    return exp(a);
}

double f2(double x, void *p) {
    (void) (p);
    double a = pow(x, 3);
    double b = x + a;
    return fabs(b);
}

double f3(double x, void *p) {
    (void) (p);
    return x <= 0 ? -1 : 1;
}

int main(void) {

    int n = 10000;
    double (*functions[])(double, void *) = {f1, f2, f3};
    char *filenames[] = {"pierwsze_1.dat", "pierwsze_2.dat", "pierwsze_3.dat"};

    for (int i = 0; i < 3; i++) {
        FILE *file = fopen(filenames[i], "w");
        gsl_cheb_series *cs = gsl_cheb_alloc(40);
        gsl_function F;

        F.function = functions[i];
        F.params = 0;

        gsl_cheb_init(cs, &F, -1.0, 1.0);

        for (int j = -10000; j < n; j++) {
            double x = j / (double) n;
            double r10 = gsl_cheb_eval_n(cs, 10, x);
            double r40 = gsl_cheb_eval(cs, x);
            fprintf(file, "%g %g %g\n", x, r10, r40);
        }

        gsl_cheb_free(cs);
        fclose(file);
    }

    return 0;
}
