#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

double f1(double x) {
    return pow(x, 2);
}

double fi1(double x) {
    return pow(x, 3) / 3;
}

double f2(double x) {
    return 1 / sqrt(x);
}

double fi2(double x) {
    return 2 * sqrt(x);
}

double pc(double y1, double y2, double ab) {
    return (y1 + y2) * ab / 2;
}

double pi(double (*fi)(double), double x1, double x2) {
    return fi(x2) - fi(x1);
}

double e(double p1, double p2) {
    return fabs(p1 - p2);
}

int main(int argc, char *argv[]) {
    double a, b, ab, x1, x2, pc1 = 0, pi1, pc2 = 0, pi2;
    int n, i;
    if (argc < 3) {
        errno = EINVAL;
        perror("");
        return errno;
    }
    a = strtod(argv[1], NULL);
    b = strtod(argv[2], NULL);
    n = strtol(argv[3], NULL, 10);
    if (0 != errno) {
        perror("");
        return errno;
    }
    ab = (b - a) / n;
    for (i = 0; i < n; i++) {
        x1 = a + i * ab;
        x2 = a + (i + 1) * ab;
        pc1 += pc(f1(x1), f1(x2), ab);
        pc2 += pc(f2(x1), f2(x2), ab);
    }
    pi1 = pi(fi1, a, b);
    pi2 = pi(fi2, a, b);
    printf("%f %f %e\n%f %f %e\n",
           pc1, pi1, e(pc1, pi1),
           pc2, pi2, e(pc2, pi2));
    return EXIT_SUCCESS;
}
