#include <stdio.h>
#define NUMBER 7

int tree[NUMBER];

// tree는 인덱스 트리
// 1부터 i까지의 구간 합 구하기
int sum(int i)
{
    int res = 0;
    while (i > 0)
    {
        res += tree[i];
        // 마지막 비트 빼서 앞으로 이동
        i -= (i & -i);
    }
    return res;
}

// 특정 인덱스 수정, 이 함수를 이용해서 인덱스 트리에 초기값도 넣을 수 잇다.
// dif 수정 값
void update(int i, int dif)
{
    while (i <= NUMBER)
    {
        // 비트만큼 빼서 앞으로 이동한 자리에서 변경된 값 만큼을 더해주면된다.
        tree[i] += dif;
        i += (i & -i);
    }
}

int getSection(int start, int end)
{
    return sum(end) - sum(start - 1);
}

int main(void)
{
    update(1, 7);
    update(2, 1);
    update(3, 9);
    update(4, 5);
    update(5, 6);
    update(6, 4);
    update(7, 1);
    printf("1부터 7까지의 구간합: %d\n", getSection(1, 7));
    printf("인덱스 6의 원소를 +3만큼 수정\n");
    update(6, 3);
    printf("4부터 7까지의 구간 합: %d\n", getSection(4, 7));
}