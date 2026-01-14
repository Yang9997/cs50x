#include <cs50.h>
#include <stdio.h>

long getNumber();
int isVisa(long number);
int main(void)
{
    long id = getNumber();
    int flag = isVisa(id);
    if (flag == 1)
    {
        printf("VISA\n");
    }
    else if (flag == 2)
    {
        printf("MASTERCARD\n");
    }
    else if (flag == 3)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;

}
long getNumber()
{
    long number = 0;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);
    return number;
}
int isVisa(long number)
{
    // 计算*2后的单个数字和
    long sum = 0;
    // 计算位数
    long digit = 0;
    // 取后两位
    long tail = 0;

    long temp = number;
    while (temp > 0)
    {
        tail = temp % 100;
        tail /= 10;
        tail *= 2;
        if (tail >= 10)
        {
            sum += tail / 10;
            sum += tail % 10;
        }
        else
        {
            sum += tail;
        }
        // digit ++;
        // printf("temp = %li, number = %li, tail = %li, sum = %li\n", temp, number, tail, sum);
        temp /= 100;
    }

    // 取倒数第一位
    tail = number % 10;
    sum += tail;
    // digit ++;
    // 去掉最后一位，后续计算加和按前面相似流程计算
    temp = number / 10;
    while (temp > 0)
    {
        tail = temp % 100;
        tail /= 10;
        sum += tail;
        // digit ++;
        temp /= 100;
    }

    // 保留前两位
    temp = number;
    while (!(temp > 9 && temp < 100))
    {
        temp /= 10;
        digit ++;
    }
    digit += 2;
    long digit1 = temp / 10;
    long digit2 = temp % 10;
    // 判断是不是末位为0
    int flag = 0;
    if (sum%10 == 0)
    {
        if ((digit == 13 || digit == 16) && digit1 == 4)
            flag = 1;
        else if (digit == 16 && digit1 == 5 && digit2 >= 1 && digit2 <=5)
            flag = 2;
        else if (digit == 15 && digit1 == 3 && (digit2 == 3 || digit2 == 7))
            flag = 3;
        else
            flag = 4;
    }
    else
    {
        flag = 4;
    }
    printf("digit = %li\n",digit);
    printf("sum = %li\n",sum);
    return flag;
}

