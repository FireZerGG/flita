#include <stdio.h>
#include <limits.h>
#include <string.h>

int main(void)
{
    char s[100000] = {0}; // double max length == 309
    if(scanf("%100000s", s) != 1){  // s - first element address, s[0] - first element, s[1] - second element
        return 1;
    }
    int i = 0;
    char s1[100000] = {0};
    int i1 = 0;
    char s2[100000] = {0};
    int i2 = 0;
    while (s[i] == '0' && i < strlen(s)) {
        i++;
    }
    while (s[i] != '.' && i < strlen(s)) {
        s1[i1] = s[i];
        i1++;
        i++;
    } // s[i] == '.'
    i++;
    while (i < strlen(s)) {
        s2[i2] = s[i];
        i2++;
        i++;
    }
    printf("%s | %s\n", s1, s2);
    return 0;
}
