#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main() {
    FILE* input = fopen("input.txt", "r");

    if (fseek(input, 0, SEEK_END) != 0) return 1;
    int file_len = ftell(input);
    rewind(input);

    char* chrs = (char*)malloc(file_len * sizeof(char));
    if (chrs == NULL) return 1;
    if (fread(chrs, 1, file_len, input) != file_len) return 1;

    int pairs = 1;
    for (int i = 0; i < file_len; i++)
        if (chrs[i] == ',') pairs++;

    uint64_t sum = 0;

    // brute force, there is a better but more complex way to do this
    for (int i = 0; i < pairs; i++) {
        uint64_t min = atoi(strsep(&chrs, "-"));
        uint64_t max = atoi(strsep(&chrs, ","));
        for (uint64_t n = min; n <= max; n++) {
            uint64_t digits = log10(n) + 1;
            if ((digits & 1) == 0) {
                uint64_t mask = pow(10, digits >> 1);
                if ((uint64_t)(n % mask) - (uint64_t)(n / mask) == 0) {
                    sum += n;
                }
            }
        }
    }

    printf("SUM: %llu\n", sum);

    return 0;
}
