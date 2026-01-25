#include <stdio.h>
#include <cs50.h>
/* 代码原逻辑没问题，优化：needchange
    某一趟在冒泡比较时没发生交换，说明已经排序完成了 */
void bubblesort(int numbers[], int n)
{
    int temp ;
    bool needchange ;
    for (int i = 0; i < (n - 1); i++)
    {
        // 默认冒泡比较后不需要冒泡交换
        needchange = false;
        // 大数字放在右边，每趟右边数字少一个
        for (int j = 0; j < (n - 1 - i); j++)
        {
            // 大数字放在右边
            // 冒泡比较
            if (numbers[j] > numbers[j + 1])
            {
                // 冒泡交换位置
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                needchange = true;
            }
        }
        if (!needchange)
            break;
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
    bubblesort(numbers, number);
    for (int i = 0; i < number; i++)
    {
        printf("%d ",numbers[i]);
    }
    printf("\n");

    return 0;
}
