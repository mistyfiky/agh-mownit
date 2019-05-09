#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_chebyshev.h>

double f1(double x, void *p) {
    (void) (p); /* avoid unused parameter warning */

    return exp(pow(x, 2));
}

double f2(double x, void *p) {
    (void) (p); /* avoid unused parameter warning */

    return fabs(x + pow(x, 3));
}

double f3(double x, void *p) {
    (void) (p); /* avoid unused parameter warning */
    return x <= 0 ? -1 : 1;
}

double (*f[])(double, void *) = {f1, f2, f3};

char *a[] = {"pierwsze_1.dat", "pierwsze_2.dat", "pierwsze_3.dat"};

int main(void) {

    int i, n = 10000;
    gsl_cheb_series *cs = gsl_cheb_alloc(40);
    gsl_function F;
    FILE *file;

    for (int j = 0; j < 3; j++) {
        file = fopen(a[j], "w");
        F.function = f[j];
        F.params = 0;

        gsl_cheb_init(cs, &F, -1.0, 1.0);

        for (i = -n; i < n; i++) {
            double x = i / (double) n;
            double r10 = gsl_cheb_eval_n(cs, 10, x);
            double r40 = gsl_cheb_eval(cs, x);
            fprintf(file, "%g %g %g %g\n",
                    x, GSL_FN_EVAL (&F, x), r10, r40);
        }

        fclose(file);
    }

    gsl_cheb_free(cs);

    return 0;
}
