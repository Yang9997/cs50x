#include <stdio.h>
#include <cs50.h>

void insertsort(int numbers[], int number)
{
    for (int i = 1; i < number; i++)
    {
        int key = numbers[i];
        int j = i - 1;
        while (j >= 0 && numbers[j] > key)
        {
            numbers[j + 1] = numbers[j];
            j--;
        }
        numbers[j + 1] = key;
    }
}

int main()
{
    int number;
    do
    {
        number = get_int("Enter a number: ");
    }
    while (number < 1);

    int numbers[number];
    for (int i = 0; i < number; i++)
    {
        numbers[i] = get_int("Number %d: ",i);
    }
    insertsort(numbers, number);
    for (int i = 0; i < number; i++)
    {
        printf("%d ",numbers[i]);
    }
    printf("\n");

    return 0;
}
