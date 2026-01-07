// #include<stdio.h>
// #include<cs50.h>
// int main(void){
//     // int score1 = 72;
//     // int score2=73;
//     // int score3=33;

//     int scores[3];
//     // scores[0] = 72;
//     // scores[1]=73;
//     // scores[2]=33;

//     for(int i =0;i<3;i++){
//         scores[i]=get_int("Score: ");
//     }
//     printf("Average: %f\n",(scores[1]+scores[2]+scores[0])/3.0);
// }

#include <cs50.h>
#include <stdio.h>
const int N = 3;
void get_array(int scores[]);
float average(int length, int scores[]);
int main(void)
{
    int scores[N];
    get_array(scores);
    printf("average: %f\n", average(N, scores));
}
void get_array(int scores[]){
    for(int i = 0;i<N;i++){
        scores[i]=get_int("Enter the number: ");
    }
}
float average(int length,int scores[]){
    int sum = 0;
    for(int i = 0;i<length;i++){
        sum+=scores[i];
    }
    return sum/(float)length;
}
