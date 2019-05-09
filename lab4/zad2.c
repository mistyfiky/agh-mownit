#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

double f1(double x) {
    return pow(x, 2);
}

double f2(double x) {
    return 1 / sqrt(x);
}

double p(double y1, double y2, double ab) {
    return (y1 + y2) * ab / 2;
}

int main(int argc, char *argv[]) {
    double a, b, ab, x1, x2, p1 = 0, p2 = 0;
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
        p1 += p(f1(x1), f1(x2), ab);
        p2 += p(f2(x1), f2(x2), ab);
    }
    printf("%g %g\n", p1, p2);
    return EXIT_SUCCESS;
}
