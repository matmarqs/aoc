#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double t_root(int vy, int yi) {
    double u = (double) (2*vy + 1);
    return (u + sqrt(u*u - 8.0*yi)) / 2.0;
}

///* x(t) = s(t, vx), y(t) = s(t, vy) */
//int s(int t, int vu) {
//    return vu * t - (t * (t-1)) / 2;
//}

/* x(t) = s(t, vx), y(t) = s(t, vy) */
int max_height(int v) {
    return (v * (v+1)) / 2;
}

/* returns n if there exists natural n such that x <= n <= y */
/* returns -1 otherwise */
int int_btw(double x, double y) {
    int f = floor(y);
    return (ceil(x) <= f) ? f : -1;
}

int main(int argc, char *argv[]) {
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    //ssize_t num;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (!stream) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /* o input eh somente de uma linha */
    getline(&line, &len, stream);
    int x1, x2, y1, y2;
    sscanf(line, "target area: x= %d .. %d , y= %d .. %d \n", &x1, &x2, &y1, &y2);
    printf("x1 = %d, x2 = %d, y1 = %d, y2 = %d\n", x1, x2, y1, y2);

    int limit_vy = 2 * abs(y1), max_vy = 0;
    for (int vy = 0; vy < limit_vy; vy++) {
        if (int_btw(t_root(vy, y2), t_root(vy, y1)) != -1)
            max_vy = vy;
    }

    printf("\nmax_vy = %d\n", max_vy);
    printf("max_height = %d\n", max_height(max_vy));

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
