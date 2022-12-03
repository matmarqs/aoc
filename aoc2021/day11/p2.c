#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int energy, flashed;
} octopus;

void print_grid(octopus grid[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            printf("%d%c", grid[i][j].energy, (j == 9) ? '\n' : ' ');
}

void zero_flash(octopus grid[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            grid[i][j].flashed = 0;
}

void increase_one(octopus grid[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            grid[i][j].energy++;
}

void local_flash(octopus grid[10][10], int i, int j) {
    int top = (i > 0), bot = (i < 9);
    int left = (j > 0), right = (j < 9);
    if (top) {
        grid[i-1][j].energy++;
        if (left)
            grid[i-1][j-1].energy++;
        if (right)
            grid[i-1][j+1].energy++;
    }
    if (bot) {
        grid[i+1][j].energy++;
        if (left)
            grid[i+1][j-1].energy++;
        if (right)
            grid[i+1][j+1].energy++;
    }
    if (left)
        grid[i][j-1].energy++;
    if (right)
        grid[i][j+1].energy++;

    grid[i][j].flashed = 1; /* now the octopus has flashed */
}

void check_flashed_reset_energy(octopus grid[10][10], int *all_flashed_ptr) {
    *all_flashed_ptr = 1;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (grid[i][j].flashed)
                grid[i][j].energy = 0;
            else
                *all_flashed_ptr = 0;
        }
}

int flashes(octopus grid[10][10], int *all_flashed_ptr) {
    int i, j;
    int step_flashes = 0, last_flashes;
    int may_flash = 1;
    while (may_flash) {
        last_flashes = step_flashes;
        for (i = 0; i < 10; i++)
            for (j = 0; j < 10; j++)
                if (grid[i][j].energy > 9 && !grid[i][j].flashed) { /* se tem energia suficiente */
                    local_flash(grid, i, j);                        /* e ainda nao flashou */
                    step_flashes++;
                }
        if (step_flashes == last_flashes)   /* there was no flashes, then we can stop */
            may_flash = 0;
    }
    /* now we can reset the energy */
    check_flashed_reset_energy(grid, all_flashed_ptr);
    return step_flashes;
}

/* return number of flashes in the step */
int step(octopus grid[10][10], int *all_flashed_ptr) {
    zero_flash(grid);
    increase_one(grid);
    return flashes(grid, all_flashed_ptr);
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

    octopus grid[10][10];

    int i = 0, j;
    /* getting input */
    while ((getline(&line, &len, stream)) != -1) {  /* getline returns -1 when EOF */
        for (j = 0; j < 10; j++)
            grid[i][j].energy = line[j] - '0';
        i++;
    }
    //printf("\ngrid =\n\n");
    //print_grid(grid);

    int total_flashes = 0, all_flashed = 0;
    for (i = 0; !all_flashed; i++) {
        total_flashes += step(grid, &all_flashed);
        //printf("\ngrid step %d = \n\n", i+1);
        //print_grid(grid);
    }

    printf("total flashes = %d\n", total_flashes);
    printf("first step all flashed = %d\n", i);

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
    return 0;
}
