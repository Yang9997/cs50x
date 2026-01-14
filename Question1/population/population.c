#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int startSize;
    do
    {
        startSize = get_int("startSize: ");
    }
    while (startSize < 9);
    int endSize;
    do
    {
        endSize = get_int("endSize: ");
    }
    while (endSize < startSize);

    int birth;
    int dead;
    int temp = startSize;
    int year = 0;
    while (endSize > temp)
    {
        year++;
        birth = temp / 3;
        dead = temp / 4;
        temp += birth - dead;
    }
    printf("Years: %i\n", year);

    return 0;
}
