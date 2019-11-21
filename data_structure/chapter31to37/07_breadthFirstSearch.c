#include <stdlib.h>
#include <stdlib.h>
#define INF 99999999
#define MAX_SIZE 1001

typedef struct
{
    int index;
    struct Node *next;
} Node;

typedef struct
{
    Node *front;
    Node *rear;
    int count;
} Queue;

Node **a;
int n, m, c[MAX_SIZE];

void addFront(Node *root, int index)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->index = index;
    node->next = root->next;
    root->next = node;
}

// 맨 뒤에 새로운 노드를 넣어줌.
void queuePush(Queue *queue, int index)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->index = index;
    node->next = NULL;
    if (queue->count == 0)
    {
        // 아무것도 없으면 맨 앞에 넣음
        queue->front = node;
    }
    else
    {
        // 뭐가 있으면 queue의 맨 마지막 노드의 다음으로 연결해줌.
        queue->rear->next = node;
    }
    // 맨끝에 node를 넣어줌.
    queue->rear = node;
    queue->count++;
}

// 맨 앞 노드의 값을 pop
int queuePop(Queue *queue)
{
    if (queue->count == 0)
    {
        printf("Queue underflow\n");
        return -INF;
    }
    Node *node = queue->front;
    int index = node->index;
    queue->front = node->next;
    free(node);
    queue->count--;
    return index;
}

void bfs(int start)
{
    // 큐 정의, 초기화
    Queue q;
    q.front = q.rear = NULL;
    q.count = 0;
    // 큐에 시작점을 넣어줌.
    queuePush(&q, start);
    // c에는 해당 노드를 지났는지 표시
    c[start] = 1;
    while (q.count != 0)
    {
        // 맨 위에 있는 값 출력하고 삭제
        int x = queuePop(&q);
        printf("%d ", x);
        // 맨 위에 있는 노드(정점)가 연결된 것들을 큐에 넣어줌.
        // 해당 정점의 다음 노드를 cur로 함.
        Node *cur = a[x]->next;
        while (cur != NULL)
        {
            // cur의 인덱스 가져오기
            int next = cur->index;
            // cur을 방문한적 없으면 큐에 cur의 값을 넣어줌.
            if (!c[next])
            {
                queuePush(&q, next);
                c[next] = 1;
            }
            // 연결된 다음 노드로 넘어감.
            cur = cur->next;
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);
    a = (Node **)malloc(sizeof(Node *) * (MAX_SIZE));
    for (int i = 1; i <= n; i++)
    {
        a[i] = (Node *)malloc(sizeof(Node));
        a[i]->next = NULL;
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        addFront(a[x], y);
        addFront(a[y], x);
        printf("%d %d\n", &x, &y);
    }
    bfs(1);
    return 0;
}