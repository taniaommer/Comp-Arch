

#include <stdio.h>
#include <ctype.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1; // return error
    }
    char *input = argv[1];
    int i = 0;
    while (input[i] != '\0')
    {
        if (isalpha(input[i]))
        {
            char base = islower(input[i]) ? 'a' : 'A';
            int x = input[i] - base;
            int newValue = (x + 13) % 26;
            printf("%c", newValue + base);
        }
        else
        {
            printf("%c", input[i]);
        }
        i++;
    }

    printf("\n");
    return 0;
}
