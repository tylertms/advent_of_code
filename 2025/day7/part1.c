#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 512

int main() {
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) return 1;

    int splits = 0;
    char* line = calloc(MAX_LEN, sizeof(char));
    int* beams = calloc(MAX_LEN , sizeof(int));

    while (fgets(line, 512, input) != NULL) {
        for (int i = 0; i < strlen(line); i++) {
            switch (line[i]) {
                case 'S':
                    beams[i] = 1;
                    break;

                case '^':
                    if (!beams[i]) break;
                    splits++;
                    for (int n = -1; n <= 1; n++) beams[i + n] = n;
                    break;
            }
        }
    }

    printf("SPLITS: %d\n", splits);
    return 0;
}
