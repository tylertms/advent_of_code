#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int check_pos(char* chrs, int x, int y, int x_end, int y_end) {
    int min_x = x == 0 ? 0 : x - 1;
    int min_y = y == 0 ? 0 : y - 1;
    int max_x = x == x_end - 1 ? x_end - 1 : x + 1;
    int max_y = y == y_end - 1 ? y_end - 1 : y + 1;

    int sum = 0;
    for (int pos_x = min_x; pos_x <= max_x; pos_x++)
        for (int pos_y = min_y; pos_y <= max_y; pos_y++) {
            if (pos_x == x && pos_y == y) continue;
            if (chrs[pos_y * (x_end + 1) + pos_x] == '@') sum++;
        }

    return sum;
}

int main() {
    FILE* input = fopen("./input.txt", "r");
    if (input == NULL) return 1;

    if (fseek(input, 0, SEEK_END) != 0) return 1;
    int file_len = ftell(input);
    rewind(input);

    char* chrs = (char*)malloc(file_len * sizeof(char));
    if (chrs == NULL) return 1;
    if (fread(chrs, 1, file_len, input) != file_len) return 1;

    int x_end = 0;
    int y_end = 0;
    for (int i = 0; i < file_len; i++) {
        if (chrs[i] == '\n') {
            if (!x_end) x_end = i;
            y_end++;
        }
    }

    uint32_t total_removed = 0;
    uint32_t last_removed = -1;

    while (last_removed != 0) {
        last_removed = 0;
        for (int y = 0; y < y_end; y++) {
            for (int x = 0; x < x_end; x++) {
                if (chrs[y * (x_end + 1) + x] == '@') {
                    if (check_pos(chrs, x, y, x_end, y_end) < 4) {
                        chrs[y * (x_end + 1) + x] = '.';
                        last_removed++;
                    }
                }
            }
        }
        total_removed += last_removed;
    }


    printf("Total: %d\n", total_removed);
    return 0;
}
