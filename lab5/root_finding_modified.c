/*
Pierwszy program stosuje metode Brenta
gsl_root_fsolver_brent 
dla rownania
x^2 - 5 = 0

rozwiazaniem jest x = \sqrt 5 = 2.236068...
*/
#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <string.h>

#include "demo_fn.h"

int
main (int argc, char *argv[])
{
  int status;
  int iter = 0, max_iter = 100;
  const gsl_root_fsolver_type *T;
  gsl_root_fsolver *s;
  double r = 0, r_expected = sqrt (5.0);
  double x_lo = 0.0, x_hi = 5.0;
  gsl_function F;
  struct quadratic_params params = {1.0, -2.0, 1.0};

  F.function = &quadratic;
  F.params = &params;

  if (argc < 2) {
      errno = EINVAL;
      perror("");
      return errno;
  }
  char *method = argv[1];
  if (0 == strcmp("bisection", method)) {
      T = gsl_root_fsolver_bisection;
  } else if (0 == strcmp("secant", method)) {
      T = gsl_root_fsolver_brent;
  } else if (0 == strcmp("steffenson", method)) {
      T = gsl_root_fsolver_falsepos;
  } else {
      errno = EINVAL;
      perror("");
      return errno;
  }

  T = gsl_root_fsolver_bisection;
  s = gsl_root_fsolver_alloc (T);
  gsl_root_fsolver_set (s, &F, x_lo, x_hi);

  printf ("using %s method\n", 
          gsl_root_fsolver_name (s));

  printf ("%5s [%9s, %9s] %9s %10s %9s\n",
          "iter", "lower", "upper", "root", 
          "err", "err(est)");

  do
    {
      iter++;
      status = gsl_root_fsolver_iterate (s);
      r = gsl_root_fsolver_root (s);
      x_lo = gsl_root_fsolver_x_lower (s);
      x_hi = gsl_root_fsolver_x_upper (s);
      status = gsl_root_test_interval (x_lo, x_hi,
                                       0, 0.001);

      if (status == GSL_SUCCESS)
        printf ("Converged:\n");

      printf ("%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
              iter, x_lo, x_hi,
              r, r - r_expected, 
              x_hi - x_lo);
    }
  while (status == GSL_CONTINUE && iter < max_iter);
  return status;
}


