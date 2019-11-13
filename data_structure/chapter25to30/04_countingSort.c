#include <stdio.h>
#define MAX_VALUE 10001

int n, m;
int a[MAX_VALUE];

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        // 값을 입력하면 해당 값 인덱스의 배열값이 1씩 늘어남
        // 인덱스 1의 배열값이 3이라면, 정렬시에 1을 3번 출력하면 되는 것
        scanf("%d", &m);
        a[m]++;
    }
    // 인덱스에 있는 배열 값만큼 인덱스를 출력하면 됨.
    for (int i = 0; i < MAX_VALUE; i++)
    {
        while (a[i] != 0)
        {
            printf("%d", i);
            a[i]--;
        }
    }
}
