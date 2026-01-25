#include<stdio.h>
#include<cs50.h>
void selectsort(int numbers[], int number)
{
    // 下标
    int tag = 0;
    // 数值
    int temp = numbers[0];
    for (int i = 0; i < (number - 1); i++)
    {
        tag = i;
        for (int j = (i + 1); j < number; j++)
        {
            // 选最小值
            if (numbers[j] < numbers[tag])
            {
                tag = j;
            }
        }
        if ( numbers[tag] != numbers[i])
        {
            temp = numbers[tag];
            numbers[tag] = numbers[i];
            numbers[i] = temp;
        }
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
    selectsort(numbers, number);
    for (int i = 0; i < number; i++)
    {
        printf("%d ",numbers[i]);
    }
    printf("\n");

    return 0;
}
