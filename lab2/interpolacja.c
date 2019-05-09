#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

static double fun(double x) {
    return x + cos(x * x);
}

int main(void) {
    const double a = 1.0;
    const double b = 10.0;
    const int steps = 10;
    double xi, yi, x[100], y[100], dx;
    FILE *input, *output;
    int i;
    const gsl_interp_type *ts[] = {
            gsl_interp_linear,
            gsl_interp_polynomial,
            gsl_interp_cspline,
            gsl_interp_cspline_periodic,
            gsl_interp_akima,
            gsl_interp_akima_periodic,
            gsl_interp_steffen,
    };
    char *tsn[] = {
            "gsl_interp_linear.txt",
            "gsl_interp_polynomial.txt",
            "gsl_interp_cspline.txt",
            "gsl_interp_cspline_periodic.txt",
            "gsl_interp_akima.txt",
            "gsl_interp_akima_periodic.txt",
            "gsl_interp_steffen.txt",
    };
    int tsc = sizeof(ts) / sizeof(const gsl_interp_type *);
    input = fopen("wartosci.txt", "w");
    dx = (b - a) / (double) steps;
    for (i = 0; i <= steps; ++i) {
        x[i] = a + (double) i * dx + 0.5 * sin((double) i * dx);
        y[i] = fun(x[i]);
        fprintf(input, "%g %g\n", x[i], y[i]);
    }
    for (i = 0; i < tsc; i++) {
        output = fopen(tsn[i], "w");
        gsl_interp_accel *acc = gsl_interp_accel_alloc();
        gsl_spline *spline = gsl_spline_alloc(ts[i], steps + 1);
        gsl_spline_init(spline, x, y, steps + 1);
        for (xi = a; xi <= b; xi += 0.01) {
            yi = gsl_spline_eval(spline, xi, acc);
            fprintf(output, "%g %g\n", xi, yi);
        }
        gsl_spline_free(spline);
        gsl_interp_accel_free(acc);
    }
    return EXIT_SUCCESS;
}


