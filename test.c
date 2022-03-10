#include <stdio.h>

int main(int a, char** c, char **env)
{
    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}