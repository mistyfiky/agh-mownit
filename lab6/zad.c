#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/resource.h>
#include <string.h>

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

double drand() {
    return (double) rand() / RAND_MAX;
}

void ptime(struct rusage *ru0, struct rusage *ru1) {

    double utime = 0, stime = 0, ttime = 0;

    utime = (double) ru1->ru_utime.tv_sec
            + 1.e-6 * (double) ru1->ru_utime.tv_usec
            - ru0->ru_utime.tv_sec
            - 1.e-6 * (double) ru0->ru_utime.tv_usec;
    stime = (double) ru1->ru_stime.tv_sec
            + 1.e-6 * (double) ru1->ru_stime.tv_usec
            - ru0->ru_stime.tv_sec
            - 1.e-6 * (double) ru0->ru_stime.tv_usec;
    ttime = stime + utime;

    printf("%3f\n", ttime);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        errno = EINVAL;
        perror("");
        return errno;
    }
    int n = strtol(argv[1], NULL, 10);
    if (0 != errno) {
        perror("");
        return errno;
    }

    srand(time(NULL));

    int els = n * n;
    double *A_data = (double *) malloc(els * sizeof(double));
    for (int i = 0; i < els; i++) {
        A_data[i] = drand();
    }
    double *b_data = (double *) malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        b_data[i] = drand();
    }

    gsl_matrix_view A
            = gsl_matrix_view_array(A_data, n, n);
    gsl_matrix *A_copy = gsl_matrix_alloc(n, n);
    gsl_matrix_memcpy(A_copy, &A.matrix);
    fprintf(stderr, "A = [\n");
    gsl_matrix_fprintf(stderr, &A.matrix, "%g");
    fprintf(stderr, "]\n");

    gsl_vector_view b
            = gsl_vector_view_array(b_data, n);
    fprintf(stderr, "b = [\n");
    gsl_vector_fprintf(stderr, &b.vector, "%g");
    fprintf(stderr, "]\n");

    gsl_vector *x = gsl_vector_alloc(n);

    struct rusage t0, t1, t2;
    int s;

    gsl_permutation *p = gsl_permutation_alloc(n);

    getrusage(RUSAGE_SELF, &t0);
    gsl_linalg_LU_decomp(&A.matrix, p, &s);
    getrusage(RUSAGE_SELF, &t1);
    gsl_linalg_LU_solve(&A.matrix, p, &b.vector, x);
    getrusage(RUSAGE_SELF, &t2);

    fprintf(stderr, "x = [\n");
    gsl_vector_fprintf(stderr, x, "%g");
    fprintf(stderr, "]\n");

    fprintf(stderr, "%s \n", "decomposition time:");
    ptime(&t0, &t1);
    fprintf(stderr, "%s \n", "solve time:");
    ptime(&t1, &t2);
    fprintf(stderr, "%s \n", "together time:");
    ptime(&t0, &t2);

    gsl_vector *y = gsl_vector_alloc(n);
    gsl_blas_dgemv(CblasNoTrans, 1.0, A_copy, x, 0, y);
    fprintf(stderr, "y = [\n");
    gsl_vector_fprintf(stderr, y, "%g");
    fprintf(stderr, "]\n");

    gsl_permutation_free(p);
    gsl_vector_free(x);
    return EXIT_SUCCESS;
}
