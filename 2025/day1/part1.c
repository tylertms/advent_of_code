#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    FILE* input = fopen("input.txt", "r");

    int dial = 50;
    char rotation[32];
    int zero_hits = 0;

    while (fgets(rotation, 32, input) != NULL) {
        int dir = rotation[0] == 'L' ? -1 : 1;
        int rot = atoi(rotation + 1);

        dial += dir * rot;
        while (dial >= 100) dial -= 100;
        while (dial < 0) dial += 100;

        if (dial == 0)
            zero_hits++;
    }

    printf("PART1: %d\n", zero_hits);

    return 0;
}
