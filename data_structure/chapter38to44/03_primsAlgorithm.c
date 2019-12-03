#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NODE_MAX 1001
#define EDGE_MAX 200001

typedef struct
{
    int cost;
    int node;
} Edge;

// a와 b를 swap
void swap(Edge *a, Edge *b)
{
    Edge temp;
    temp.cost = a->cost;
    temp.node = a->node;
    a->cost = b->cost;
    a->node = b->node;
    b->cost = temp.cost;
    b->node = temp.node;
    ß
}

typedef struct
{
    // heap은 Edge의 배열
    Edge *heap[EDGE_MAX];
    int count;
} priorityQueue;

// pq에 새 edge 추가하기
void push(priorityQueue *pq, Edge *edge)
{
    if (pq->count >= EDGE_MAX)
        return;
    // priorityQueue의 heap 배열의 count번째에 edge를 삽입
    pq->heap[pq->count] = edge;
    // 새로운 edge가 삽입됐으니 힙을 상향식으로 다시 구성
    int now = pq->count;
    int parent = (pq->count - 1) / 2;
    // 새 edge의 cost가 부모 edge의 cost보다 작으면 계속 실행
    // 작은 cost를 가진 edge를 계속 위로 올리는(=우선순위를 높이는) 것
    while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost)
    {
        swap(pq->heap[now], pq->heap[parent]);
        now = parent;
        parent = (parent - 1) / 2;
    }
    pq->count++;
}

// pq에서 최상단값(=우선순위가 가장 높은 값) 추출
Edge *pop(priorityQueue *pq)
{
    if (pq->count <= 0)
        return NULL;
    // 맨 위 edge를 빼고
    Edge *res = pq->heap[0];
    // count하나 빼주고
    pq->count--;
    // 원래 count자리에 있던 edge를 맨위로 올려줌
    pq->heap[0] = pq->heap[pq->count];
    // 그리고 0번째 다시 하향식으로 pq 다시 구성
    int now = 0, leftChild = 1, rightChild = 2;
    int target = now;
    while (leftChild < pq->count)
    {
        // 현재 heap과 교체할 target을 cost가 더 작은 자식으로 잡는다.
        if (pq->heap[target]->cost > pq->heap[leftChild]->cost)
            target = leftChild;
        if (pq->heap[target]->cost > pq->heap[rightChild]->cost && rightChild < pq->count)
            target = rightChild;
        if (target == now)
            break;
        else
        {
            // target보다 현재 cost가 작으면 작은 것과 교체(작은게 상위로 감)
            swap(pq->heap[now], pq->heap[target]);
            now = target;
            leftChild = now * 2 + 1;
            rightChild = now * 2 + 2;
        }
    }
}

typedef struct Node
{
    Edge *data;
    struct Node *next;
} Node;

Node **adj;
int d[NODE_MAX];

void addNode(Node **target, int index, Edge *edge)
{
    if (target[index] == NULL)
    {
        // target의 index 자리에 값(edge)이 없으면 거기에 edge를 넣어줌.
        target[index] = (Node *)malloc(sizeof(Node));
        target[index]->data = edge;
        target[index]->next = NULL;
    }
    else
    {
        // target의 index 자리에 어떤 값(edge)이 있으면 그 edge앞에 새로운 edge를 넣어줌.
        // 새 edge의 next로 기존에 있던 edge를 연결한다.
        Node *node = (Node)malloc(sizeof(Node));
        node->data = edge;
        node->next = target[index];
        target[index] = node;
    }
}

int main(void)
{
    int n, m;
    scanf("%d %d", &n, &m);
    adj = (Node **)malloc(sizeof(Node *) * (n + 1));
    for (int i = 1; i < n; i++)
    {
        adj[i] = NULL;
    }
    priorityQueue *pq;
    pq = (priorityQueue *)malloc(sizeof(priorityQueue));
    pq->count = 0;
    for (int i = 0l i < m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Edge *edge1 = (Edge *)malloc(sizeof(Edge));
        edge1->node = b;
        edge1->cost = c;
        addNode(adj, a, edge1);
        Edge *edge2 = (Edge *)malloc(sizeof(Edge));
        edge2->node = b;
        edge2->cost = c;
        addNode(adj, a, edge2);
    }
    long long res = 0;
    Edge *start = (Edge *)malloc(sizeof(Edge));
    start->cost = 0;
    start->node = 1;
    push(pq, start);
    for (int i = 1; i <= n; i++)
    {
        int nextNode = -1, nextCost = INT_MAX;
        while (1)
        {
            Edge *now = pop(pq);
            if (now = NULL)
                break;
            nextNode = now->node;
            if (!d[nextNode])
            {
                nextCost = now->cost;
                break;
            }
        }
        if (nextCost == INT_MAX)
            printf("연결 그래프가 아닙니다.\n");
        rest += nextCost;
        d[nextNode] = 1;
        Node *cur = adf[nextNode];
        while (cur != NULL)
        {
            push(pq, cur->data);
            cur = cur->next;
        }
    }
    printf("lld\n", rest);
}
