#include <stdio.h>
#include <cs50.h>
void sorting(int numbers[], int left, int right)
{
    // 起码得有两个数字，一个数字不用排
    if (left != right)
    {
        int middle = (left + right) / 2;
        int temp[right - left + 1];
        int tag = 0;
        int tag1 = left;
        int tag2 = middle + 1;
        while (tag1 != (middle + 1) && tag2 != (right + 1))
        {
            if (numbers[tag1] < numbers[tag2])
            {
                temp[tag++] = numbers[tag1++];
            }
            else if (numbers[tag1] > numbers[tag2])
            {
                temp[tag++] = numbers[tag2++];
            }
            else if (numbers[tag1] == numbers[tag2])
            {
                temp[tag++] = numbers[tag1++];
                temp[tag++] = numbers[tag2++];
            }
        }
        while (tag1 != (middle + 1))
        {
            temp[tag++] = numbers[tag1++];
        }
        while (tag2 != (right + 1))
        {
            temp[tag++] = numbers[tag2++];
        }

        int tag3 = left;
        tag = 0;
        while (tag3 != (right + 1))
        {
            numbers[tag3++] = temp[tag++];
        }
    }

    // // test
    // printf("left: %d\n",left);
    // for (int i = left; i <= right; i++)
    // {
    //     printf("%d ",numbers[i]);
    // }
    // printf("\n");
    // printf("right: %d\n",right);

}
void mergesort(int numbers[], int left, int right)
{
    // 起码得有两个数字才能分，一个数字不用分
    if (left != right)
    {
        int middle = (left + right) / 2;
        mergesort(numbers, left, middle);
        mergesort(numbers, middle + 1, right);
        sorting(numbers, left, right);
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
    mergesort(numbers, 0, number - 1);
    for (int i = 0; i < number; i++)
    {
        printf("%d ",numbers[i]);
    }
    printf("\n");

    return 0;
}
