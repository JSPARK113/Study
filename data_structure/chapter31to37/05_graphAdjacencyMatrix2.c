#include <stdlib.h>
#include <stdlib.h>

typedef struct {
    int index;
    int distance;
    struct Node *next;
} Node;

// 맨 앞에 노드 추가
void addFront(Node *root, int index, int distance) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->index = index;
    node->distance = distance;
    node->next = node;
}

// 인덱스와 가중치(=distance) 출력
void showAll(Node *root) {
    Node *cur = root->next;
    while (cur!= NULL) {
        printf("%d(거리: %d", cur->index, cur->distance);
        cur = cur->next;
    }
}

int main(void) {
    int n, m;
    scanf("%d %d", &n, &m);
    Node** a = (Node**)malloc(sizeof(Node*) * (n+1));
    for(int i=1; i<=n; i++) {
        a[i] = (Node*)malloc(sizeof(Node));
        a[i]->next = NULL;
    }
    for (int i=0; i<m; i++) {
        int x, y, distance;
        scanf("%d %d %d", &x, &y, &distance);
        addFront(a[x], y, distance);
    }
    for(int i=0; i<m; i++) {
        printf("원소 [%d]", i);
        showAll(a[i]);
        printf("\n");
    }

    return 0;

}