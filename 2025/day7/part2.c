#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LEN 512

int main() {
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) return 1;

    char* line = calloc(MAX_LEN, sizeof(char));
    uint64_t* beams = calloc(MAX_LEN , sizeof(uint64_t));
    uint64_t timelines = 0;

    while (fgets(line, 512, input) != NULL) {
        for (int i = 0; i < strlen(line); i++) {
            switch (line[i]) {
                case 'S':
                    beams[i] = 1;
                    break;

                case '^':
                    if (!beams[i]) break;
                    beams[i - 1] += beams[i];
                    beams[i + 1] += beams[i];
                    beams[i] = 0;
                    break;
            }
        }
    }

    for (int i = 0; i < MAX_LEN; i++) {
        timelines += beams[i];
    }

    printf("\nTIMELINES: %lu\n", timelines);
    return 0;
}
