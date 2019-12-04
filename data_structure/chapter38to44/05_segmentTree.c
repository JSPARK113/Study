#include <stdio.h>
#define NUMBER 7

int a[] = {7, 1, 9, 5, 6, 4, 1};
int tree[4 * NUMBER];

// 구간합 구하기 - 구간 합 트리 생성
int init(int start, int end, int node)
{
    // 시작과 끝이 같으면 그 값자체를 해당 tree의 자리에 넣는다.
    if (start == end)
        return tree[node] = a[start];
    // 시작과 끝의 가운데부분을 mid로 해준다.
    int mid = (start + end) / 2;
    // 노드의 양쪽 노드의 합을 해당 노드의 자리에 넣는다.
    return tree[node] = init(start, mid, node * 2) + init(mid + 1, end, node * 2 + 1);
}

// start: 시작 인덱스, end: 끝 인덱스
// left, right: 구간 합을 구하고자 하는 범위
int sum(int start, int end, int node, int left, int right)
{
    if (left > end || right < start)
        // 범위 밖이면 해당 안되므로 0을 반환
        return 0;
    if (left <= start && end <= right)
        // 구간이 범위 안에 있는 경우에는 tree의 해당 노드를 반환
        return tree[node];
    int mid = (start + end) / 2;
    return sum(start, mid, node * 2, left, right) + sum(mid + 1, end, node * 2 + 1, left, right);
}

// start: 시작인덱스, end: 끝 인덱스
// index: 수정하고자 하는 노드, dif: 수정할 값
void update(int start, int end, int node, int index, int dif)
{
    if (index < start || index > end)
        return;
    tree[node] += dif;
    if (start == end)
        return;
    // 바꾸려는 노드의 상위노드는 모두 변경
    int mid = (start + end) / 2;
    update(start, mid, node * 2, index, dif);
    update(mid + 1, end, node * 2 + 1, index, dif);
}

int main(void)
{
    // 원소가 NUMBER개(7개) 있는 트리 초기화 하기
    init(0, NUMBER - 1, 1);
    printf("0부터 6까지의 구간 합: %d\n", sum(0, NUMBER - 1, 1, 0, 6));
    printf("인덱스 5의 원소를 +3만큼 수정\n");
    update(0, NUMBER - 1, 1, 5, 3);
    printf("3부터 6까지의 구간합: %d\n", sum(0, NUMBER - 1, 1, 3, 6));
}