#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double t_root(int vy, int yi) {
    double u = (double) (2*vy + 1);
    return (u + sqrt(u*u - 8.0*yi)) / 2.0;
}

/* if t >= vx, x = x_max */
int fx(int t, int v) {
    if (t < v)
        return v * t - (t * (t-1)) / 2;
    else
        return (v * (v + 1)) / 2;
}

/* returns 1 if there exists natural n such that x <= n <= y */
/* returns 0 otherwise */
int int_btw(double x, double y, int *tmin, int *tmax) {
    *tmax = floor(y);
    *tmin = ceil(x);
    return tmin <= tmax;
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

    /* na verdade, o x e o y sao exatamente simetricos, tirando o fato de quando vx = 0 acaba o movimento em x */
    int limit_vy = abs(y1) + 1, limit_vx = abs(x2) + 1;
    int tmin, tmax, count = 0;
    for (int vy = -limit_vy; vy < limit_vy; vy++)
        if (int_btw(t_root(vy, y2), t_root(vy, y1), &tmin, &tmax))
            for (int vx = 0; vx < limit_vx; vx++) {
                for (int t = tmin; t <= tmax; t++) {
                    int x = fx(t, vx);
                    if (x1 <= x && x <= x2) {
                        //printf("%d, %d\n", vx, vy);
                        count++;
                        break;
                    }
                }
            }


    printf("count = %d\n", count);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
