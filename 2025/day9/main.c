#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// this code is particularly bad...

#define LEN 512
int x[LEN];
int y[LEN];

int inside(int cx, int cy, int segments) {
    int c_up = 0;
    int c_down = 0;
    int c_left = 0;
    int c_right = 0;

    for (int i = 0; i < segments; i++) {
        int x1 = x[i], y1 = y[i];
        int x2 = x[(i + 1) % segments], y2 = y[(i + 1) % segments];

        if (x1 == x2) {
            if (y1 <= cy && cy <= y2 && cx <= x1) c_right = 1;
            if (y2 <= cy && cy <= y1 && cx >= x1) c_left = 1;
        }

        if (y1 == y2) {
            if (x1 <= cx && cx <= x2 && cy >= y1) c_down = 1;
            if (x2 <= cx && cx <= x1 && cy <= y1) c_up = 1;
        }
    }

    return c_up && c_down && c_left && c_right;
}

int outline_inside(int x1, int y1, int x2, int y2, int segments) {
    int x_min = x1 <= x2 ? x1 : x2;
    int x_max = x1 >= x2 ? x1 : x2;
    int y_min = y1 <= y2 ? y1 : y2;
    int y_max = y1 >= y2 ? y1 : y2;

    for (int cx = x_min; cx <= x_max; cx++)
        if (!inside(cx, y1, segments) || !inside(cx, y2, segments))
            return 0;

    for (int cy = y_min; cy <= y_max; cy++)
        if (!inside(x1, cy, segments) || !inside(x2, cy, segments))
            return 0;

    return 1;
}

int main() {
    FILE* input = fopen("input.txt", "r");
    int index = 0;

    char* line = (char*)malloc(LEN * sizeof(char));
    while (fgets(line, LEN, input) != NULL) {
        char* temp = line;
        x[index] = atoi(strsep(&temp, ","));
        y[index] = atoi(temp);
        index++;
    }

    int segments = index;
    int x1, y1, x2, y2;
    long area = 0;

    for (int i = 0; i < segments - 1; i++) {
        for (int j = i + 1; j < segments; j++) {
            long tmp_area = (long)(abs(x[j] - x[i]) + 1) * (long)(abs(y[j] - y[i]) + 1);
            if (tmp_area > area) {
                area = tmp_area;
                x1 = x[j], x2 = x[i];
                y1 = y[j], y2 = y[i];
            }
        }
    }

    printf("PART1: (%d,%d) to (%d,%d) has area %ld\n", x1, y1, x2, y2, area);


    area = 0;
    // very very brute force, not great
    for (int i = 0; i < segments - 1; i++) {
        for (int j = i + 1; j < segments; j++) {
            if (outline_inside(x[i], y[i], x[j], y[j], segments)) {
                long tmp_area = (long)(abs(x[j] - x[i]) + 1) * (long)(abs(y[j] - y[i]) + 1);
                if (tmp_area > area) {
                    area = tmp_area;
                    x1 = x[j], x2 = x[i];
                    y1 = y[j], y2 = y[i];
                }
            }
            printf("j: %d\n", j);
        }
        printf("%d\n", i);
    }

    printf("PART2: (%d,%d) to (%d,%d) has area %ld\n", x1, y1, x2, y2, area);

    return 0;
}
