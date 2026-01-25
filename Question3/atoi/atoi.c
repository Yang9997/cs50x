#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int number = 0;
    // input有不止一个数字
    if (strlen(input) == 1)
    {
        return (input[0] - 48);
    }
    char c = input[strlen(input) - 1];
    number = c - 48;
    input[strlen(input) - 1] = '\0';
    number += 10 * convert(input);
    return number;
}
