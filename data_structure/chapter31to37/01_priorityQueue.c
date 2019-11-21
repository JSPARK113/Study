#include <stdio.h>
#define MAX_SIZE 10000

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 우선순위 큐 정의
typedef struct
{
    int heap[MAX_SIZE];
    int count;
} priorityQueue;

// 우선순위 큐에 값 삽입
void push(priorityQueue *pq, int data)
{
    if (pq->count >= MAX_SIZE)
        return;
    // 일단 heap의 맨 뒤에 data를 넣음
    pq->heap[pq->count] = data;
    // 새로 넣은 데이터의 인덱스
    int now = pq->count;
    // 부모 노드의 위치 인덱스. 부모노드는 항상 (자신의 인덱스 -1)을 2로 나눈 몫
    int parent = (pq->count - 1) / 2;

    // 새로 넣은 데이터가 크면 위로 올리는 작업
    while (now > 0 && pq->heap[now] > pq->heap[parent])
    // 지금 넣은 데이터와 parent의 데이터를 비교해서 크면 지금 데이터와 parent의 값을 바꿔줌.
    {
        swap(&pq->heap[now], &pq->heap[parent]);
        now = parent;
        //parent갱신 - parent자리로 올라왔으므로 parent의 부모노드를 다시 parent에 넣어줌.
        parent = (parent - 1) / 2;
    }
    // 위작업이 다 끝나면 개수를 하나 늘려줌
    pq->count++;
}

// 우선순위 큐에서 값 추출
// 맨 위값을 추출함. -> 마지막 노드를 루트노드로 올림 -> 아래로 내려가면서 최대힙을 구성
int pop(priorityQueue *pq)
{
    if (pq->count <= 0)
        return -9999;
    // res = 루트노드의 값(=최대힙에서의 가장 큰값)
    int res = pq->heap[0];
    // 개수에서 하나 뺌
    pq->count--;
    // 루트노드에 마지막 노드에 있던 값을 넣어줌.
    pq->heap[0] = pq->heap[pq->count];
    // 새 원소 추출 이후에 하향식으로 힙 구성
    int now = 0, leftChild = 1, rightChild = 2;
    int target = now;
    while (leftChild < pq->count)
    {
        // 자식중에 부모보다 값이 큰 걸로 target을 잡음
        if (pq->heap[target] < pq->heap[leftChild])
            target = leftChild;
        if (pq->heap[target] < pq->heap[rightChild] && rightChild < pq->count)
            target = rightChild;
        // target이 now와 같을때 = 더이상 내려가지 않아도 되면 종료
        if (target == now)
            break;
        // target이 현재 노드(now)보다 크면 둘의 자리를 바꿔주고, 바꿔준 노드로 내려감.
        else
        {
            swap(&pq->heap[now], &pq->heap[target]);
            now = target;
            leftChild = now * 2 + 1;
            rightChild = now * 2 + 2;
        }
    }
    return res;
}

int main(void) {
    int n, data;
    scanf("%d", &n);
    priorityQueue pq;
    pq.count = 0;
    for (int i=0; i<n; i++) {
        scanf("%d", &data);
        push(&pq, data);
    }
    for (int i=0; i<n; i++) {
        int data = pop(&pq);
        printf("%d", data);
    }
    return 0;
}