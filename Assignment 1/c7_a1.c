#include <stdio.h>
#include <string.h>
#define MAX_LINE 1000

int getline_custom(char s[], int lim) {
    int c, i = 0;
    while (i < lim - 1 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

void trim(char s[]) {
    int i = strlen(s) - 1;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t')) {
        i--;
    }
    s[i + 1] = '\0';
}

int main() {
    char line[MAX_LINE];
    while (getline_custom(line, MAX_LINE) > 0) {
        trim(line);
        if (line[0] != '\0') {
            printf("%s\n", line);
        }
    }
    return 0;
}
