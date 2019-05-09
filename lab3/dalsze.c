#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_fit.h>
#include <gsl/gsl_chebyshev.h>

double f(double x, void *p) {
    (void) (p); /* avoid unused parameter warning */
    return pow(0.5, pow(x, 2) + 2 * x);
}

int main(void) {

    int i, j, n = 10000;
    gsl_function F;
    F.function = f;
    F.params = 0;
    gsl_cheb_series *cs = gsl_cheb_alloc(40);
    FILE *file;

    double *x = malloc(2*n*sizeof(double));
    double *w = malloc(2*n*sizeof(double));
    double *y = malloc(2*n*sizeof(double));
    for (i = -n, j = 0; i < n; i++, j++) {
        double xf = i / (double) n;
        x[j] = xf;
        w[j] = 1;
        y[j] = GSL_FN_EVAL (&F, xf);
    }
    double c0, c1, cov00, cov01, cov11, chisq;
    gsl_fit_wlinear(x, 1, w, 1, y, 1, n,
                    &c0, &c1, &cov00, &cov01, &cov11,
                    &chisq);

    gsl_cheb_init(cs, &F, -1.0, 1.0);

    file = fopen("dalsze.dat", "w");

    for (i = -n; i < n; i++) {
        double xf = i / (double) n;
        double yf, yf_err;
        gsl_fit_linear_est(xf,
                           c0, c1,
                           cov00, cov01, cov11,
                           &yf, &yf_err);
        double r10 = gsl_cheb_eval_n(cs, 10, xf);
        double r40 = gsl_cheb_eval(cs, xf);
        fprintf(file, "%g %g %g %g %g\n",
                xf, GSL_FN_EVAL (&F, xf), yf, r10, r40);
    }

    free(x);
    free(y);
    free(w);

    gsl_cheb_free(cs);

    fclose(file);

    return 0;
}
