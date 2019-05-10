#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <string.h>

struct quadratic_params
{
    double a, b, c;
};

double
quadratic (double x, void *params)
{
    struct quadratic_params *p
            = (struct quadratic_params *) params;

    double a = p->a;
    double b = p->b;
    double c = p->c;

    return (a * x + b) * x + c;
}

double
quadratic_deriv (double x, void *params)
{
    struct quadratic_params *p
            = (struct quadratic_params *) params;

    double a = p->a;
    double b = p->b;

    return 2.0 * a * x + b;
}

void
quadratic_fdf (double x, void *params,
               double *y, double *dy)
{
    struct quadratic_params *p
            = (struct quadratic_params *) params;

    double a = p->a;
    double b = p->b;
    double c = p->c;

    *y = (a * x + b) * x + c;
    *dy = 2.0 * a * x + b;
}

int
main (int argc, char *argv[])
{
    int status;
    int iter = 0, max_iter = 100;
    const gsl_root_fdfsolver_type *T;
    gsl_root_fdfsolver *s;
    double x0, x = 5.0, r_expected = sqrt (5.0);
    gsl_function_fdf FDF;
    struct quadratic_params params = {1.0, -2.0, 1.0};

    FDF.f = &quadratic;
    FDF.df = &quadratic_deriv;
    FDF.fdf = &quadratic_fdf;
    FDF.params = &params;

    if (argc < 2) {
        errno = EINVAL;
        perror("");
        return errno;
    }
    char *method = argv[1];
    if (0 == strcmp("newton", method)) {
        T = gsl_root_fdfsolver_newton;
    } else if (0 == strcmp("secant", method)) {
        T = gsl_root_fdfsolver_secant;
    } else if (0 == strcmp("steffenson", method)) {
        T = gsl_root_fdfsolver_steffenson;
    } else {
        errno = EINVAL;
        perror("");
        return errno;
    }
    s = gsl_root_fdfsolver_alloc (T);
    gsl_root_fdfsolver_set (s, &FDF, x);

    printf ("using %s method\n",
            gsl_root_fdfsolver_name (s));

    printf ("%-5s %10s %10s %10s\n",
            "iter", "root", "err", "err(est)");
    do
    {
        iter++;
        status = gsl_root_fdfsolver_iterate (s);
        x0 = x;
        x = gsl_root_fdfsolver_root (s);
        status = gsl_root_test_delta (x, x0, 0, 1e-3);

        if (status == GSL_SUCCESS)
            printf ("Converged:\n");

        printf ("%5d %10.7f %+10.7f %10.7f\n",
                iter, x, x - r_expected, x - x0);
    }
    while (status == GSL_CONTINUE && iter < max_iter);

    gsl_root_fdfsolver_free (s);
    return status;
}
