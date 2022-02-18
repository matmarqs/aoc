#include <stdio.h>

int main() {
    int prev = 0, curr, count = 0;
    while (scanf("%d", &curr) != EOF) {
        if (curr > prev)
            count++;
        prev = curr;
    }
    printf("count = %d\n", count-1);
    return 0;
}
