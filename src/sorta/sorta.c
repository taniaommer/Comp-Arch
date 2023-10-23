
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *tmp;
    for (int i = 1; i < argc; i++)
    {
        for (int j = i + 1; j < argc; j++)
        {
            if (strcmp(argv[i], argv[j]) > 0)
            {
                tmp = argv[i];
                argv[i] = argv[j];
                argv[j] = tmp;
            }
        }
    }
    int n = 1;
    while (n < argc)
    {
        printf("%s\n", argv[n]);
        n++;
    }

    return 0;
}