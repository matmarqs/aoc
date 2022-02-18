/* day 2, part 1 */
#include <stdio.h>
#include <stdlib.h>

int main() {
    char direction; int x;
    int depth = 0, horiz = 0;
    while (scanf("%c%d\n", &direction, &x) != EOF) {
        switch (direction) {
            case 'u':
                depth -= x;
                break;
            case 'd':
                depth += x;
                break;
            case 'f':
                horiz += x;
                break;
            default:
                break;
        }
    }
    printf("horiz * depth = %d\n", horiz * depth);
    return 0;
}
