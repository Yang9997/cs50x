#include <cs50.h>
#include <stdio.h>
int get_negative_int(void);

int main()
{
    int i = get_negative_int();
    printf("%i\n", i);

    return 0;
}

int get_negative_int(void)
{
    int n;
    do
    {
        n = get_int("Negative Integer: ");
    }
    while (n > 0);

    return n;
}
