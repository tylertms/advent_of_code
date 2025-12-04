#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* input = fopen("input.txt", "r");

    int dial = 50;
    char rotation[32];
    int zero_hits = 0;

    while (fgets(rotation, 32, input) != NULL) {
        int dir = rotation[0] == 'L' ? -1 : 1;
        int rot = atoi(rotation + 1);

        if (dial == 0 && dir < 0) {
            zero_hits--;
        }

        dial += dir * rot;

        while (dial >= 100) {
            dial -= 100;
            zero_hits++;
        }

        while (dial < 0) {
            dial += 100;
            zero_hits++;
        }

        if (dial == 0 && dir < 0) {
            zero_hits++;
        }
    }

    printf("PART2: %d\n", zero_hits);

    return 0;
}
