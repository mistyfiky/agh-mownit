#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f1(double x, void *params) {
    (void) (params); /* avoid unused parameter warning */
    return pow(x, 2);
}

double fi1(double x) {
    return pow(x, 3) / 3;
}

double f2(double x, void *params) {
    (void) (params); /* avoid unused parameter warning */
    if (0 == x) {
        return 0;
    }
    return 1 / sqrt(x);
}

double fi2(double x) {
    return 2 * sqrt(x);
}

double pi(double (*fi)(double), double x1, double x2) {
    return fi(x2) - fi(x1);
}

double e(double p1, double p2) {
    return fabs(p1 - p2);
}

int main(int argc, char *argv[]) {
    double a, b, pg1, e1, pi1, pg2, e2, pi2;
    if (argc < 2) {
        errno = EINVAL;
        perror("");
        return errno;
    }
    a = strtod(argv[1], NULL);
    b = strtod(argv[2], NULL);
    if (0 != errno) {
        perror("");
        return errno;
    }
    gsl_integration_workspace *w1
            = gsl_integration_workspace_alloc(1000);
    gsl_function F1;
    F1.function = &f1;
    gsl_integration_qags(&F1, a, b, 0, 1e-7, 1000,
                         w1, &pg1, &e1);
    pi1 = pi(fi1, a, b);
    gsl_integration_workspace *w2
            = gsl_integration_workspace_alloc(1000);
    gsl_function F2;
    F2.function = &f2;
    gsl_integration_qags(&F2, a, b, 0, 1e-7, 1000,
                         w2, &pg2, &e2);
    pi2 = pi(fi2, a, b);
    printf("%f\t%f\n", pg1, pg2);
    printf("%f\t%f\n", pi1, pi2);
    printf("%e\t%e\n", e(pg1, pi1), e(pg2, pi2));
    printf("%zu\t%zu\n", w1->size, w2->size);
    gsl_integration_workspace_free(w1);
    gsl_integration_workspace_free(w2);
    return EXIT_SUCCESS;
}
