#include <stdlib.h>

int a[1001][1001];
int n, m;

int main(void)
{
    // 그래프를 2차원 배열로 표현
    scanf("%d %d", &n, &m);
    for (int i = 0, i < m, i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        // x와 y가 관계가 있다고하면 (x, y), (y, x) 모두 1을 써줌.
        a[x][y] = 1;
        a[y][x] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d", a[i][j]);
        }
        printf("\n");
    }
}