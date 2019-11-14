#include <stdio.h>
#define MAX 10000

void radixSort(int *a, int n)
{
    // res에는 결과 배열을 넣어줌.
    int res[MAX], maxValue = 0;
    int exp = 1;
    // a 배열에서 가장 큰 값을 찾아서 maxValue에 넣어줌.
    for (int i = 0; i < n; i++)
    {
        if (a[i] > maxValue)
            maxValue = a[i];
    }
    // 1의 자리부터 계산
    while (maxValue / exp > 0)
    {
        // bucket은 자리수가 담긴 배열
        int bucket[10] = {0};
        // 해당 자리수의 숫자가 배열에 있으면 bucket에 1을 더해줌.
        // 예) 1의자리 차례(exp=1)에서 34를 만나면 bucket[4]에 1을 더한다.
        for (int i = 0; i < n; i++)
            bucket[a[i] / exp % 10]++;
        // bucket은 누적값으로 이뤄져있음. 누적계산.
        for (int i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];

        // bucket에 따라 res에 결과를 넣어줌.
        // 원래 배열의 끝부터 res에 넣어줌.
        for (int i = n - 1; i >= 0; i--)
        {
            // bucket의 값이 4면 실제 자리는 3이므로 1을 한번 빼준다.
            res[--bucket[a[i] / exp % 10]] = a[i];
        }
        // res 배열대로 a를 갱신해줌.
        for (int i = 0; i < n; i++)
            a[i] = res[i];
        // 다음 자릿수로 넘어감.
        exp *= 10;
    }
}

int main(void)
{
    int a[MAX];
    int i, n;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    radixSort(a, n);
    // 배열 출력
    for (i = 0; i < n; i++)
    {
        printf("%d\n", a[i]);
    }
}