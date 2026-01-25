#include<stdio.h>
void insertsort(int numbers[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = numbers[i];
        int j = i - 1;

        // 移动位置并找插入位置下标
        while (j >= 0 && numbers[j] > key)
        {
            numbers[j + 1] = numbers[j];
            j--;
        }
        // 插
        numbers[j] = key;
    }
}
