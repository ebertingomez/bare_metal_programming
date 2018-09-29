#include <stdio.h>
char *p = "Jello World!\n";
int main()
{
    p[0] = 'H';
    printf("%s", p);
    return 0;
}