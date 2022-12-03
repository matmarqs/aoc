/* day 2, part 2 */
#include <stdio.h>
#include <stdlib.h>

int main() {
    char direction; int x;
    int depth = 0, horiz = 0, aim = 0;
    while (scanf("%c%d\n", &direction, &x) != EOF) {
        switch (direction) {
            case 'u':
                aim -= x;
                break;
            case 'd':
                aim += x;
                break;
            case 'f':
                horiz += x;
                depth += aim * x;
                break;
            default:
                break;
        }
    }
    printf("horiz * depth = %d\n", horiz * depth);
    return 0;
}
