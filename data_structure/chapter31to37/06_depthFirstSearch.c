#include <stdlib.h>
#include <stdlib.h>
#define MAX_SIZE 1001

typedef struct
{
    int index;
    struct Node *next;
} Node;

// Node의 배열 a
Node **a;
int n, m, c[MAX_SIZE];

// 연결리스트 맨 앞에 삽입하는함수
// root는 항상 맨 위고, root 다음에 node를 삽입
void addFront(Node *root, int index)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->index = index;
    node->next = root->next;
    root->next = node;
}

void dfs(int x)
{
    //c[x]는 x를 이미 확인한 경우에는 1 아니면 0
    if (c[x])
        return;
    // 방금 x를 확인했으니 1을 넣어준다.
    c[x] = 1;
    // x를 출력
    printf("%d ", x);
    // cur에 다음 노드를 넣어준다.
    Node *cur = a[x]->next;
    while (cur != NULL)
    {
        // 다음노드의 인덱스를 다시 이 함수에 넣어줌.
        int next = cur->index;
        dfs(next);
        // 다음 노드로 넘어감.
        cur = cur->next;
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
    }
    dfs(2);
    return 0;
}