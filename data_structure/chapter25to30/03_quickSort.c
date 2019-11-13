#include <stdio.h>
#define SIZE 1000

int a[SIZE];

int swap(int *a, int *b)
{
    // a의 값을 temp에 넣고
    int temp = *a;
    // b의 값을 a에 넣고
    *a = *b;
    // b에 temp 값을 넣어서 a와 b의 자리를 바꿈
    *b = temp;
}

void quickSort(int start, int end)
{
    if (start >= end)
        return;
    int key = start, i = start + 1, j = end, temp;
    // i는 큰 값의 인덱스, j는 작은 값의 인덱스
    // 작은 값이 큰 값보다 뒤에 있는 동안에는 이 작업을 반복
    while (i <= j)
    {
        // 앞에서부터 key(피벗) 기준 큰 값을 찾음.
        while (i <= end && a[i] <= a[key])
            i++;
        // 뒤에서부터 key(피벗) 기준 작은 값을 찾음.
        while (j > start && a[j] >= a[key])
            j--;
        // 큰 값이 작은 값보다 뒤에 있으면 key의 위치와 작은 값의 위치를 바꿈
        if (i > j)
            swap(&a[key], &a[j]);
        // 작은 값이 큰 값보다 뒤에 있으면 둘의 자리를 바꿈
        else
            swap(&a[i], &a[j]);
    }
    // 작은 값이 큰 값보다 앞에 있어서 key와 j 인덱스의 자리가 바꿔지면 아래 실행(=반으로 나누기) 
    // start부터 j까지(작은 값이 있는 곳까지)
    quickSort(start, j - 1);
    // j+1부터 끝까지
    quickSort(j + 1, end);
}
int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    quickSort(0, n - 1);
    for (int i = 0; i < n; i++)
        printf("%d", a[i]);

    return 0;
}