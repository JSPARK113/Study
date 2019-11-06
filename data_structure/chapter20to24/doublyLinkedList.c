#include <stdio.h>
#include <stdlib.h>

// 양방향 연결 리스트 선언
typedef struct {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *head, *tail;

void insert(int data) {
    // 입력한 데이터에 대해 노드를 오름차순으로 넣음
    // 3을 넣으면 2와 4 사이의 자리에 노드가 입력됨.
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    Node *cur;
    cur = head->next;
    while (cur->data < data && cur != tail) {
        cur = cur->next;
    }
    Node *prev = cur->prev;
    // cur은 삽입할 노드 뒷 노드
    // prev는 삽입할 노드 앞 노드
    node->prev = prev;
    node->next = cur;
    cur->prev = node;
    prev->next = node;   
}

void removeFront() {
    // 맨 앞 노드를 삭제
    Node *node = head->next;
    head->next = node->next;
    Node *next = node->next;
    next->prev = head;
    free(node);
}

void show() {
    Node *cur = head->next;
    while (cur != tail) {
        printf("%d /", cur->data);
        // 다음 노드를 cur에 넣어줌.
        cur = cur->next;
    }
}

int main(void) {
    head = (Node*) malloc(sizeof(Node));
    tail = (Node*) malloc(sizeof(Node));
    head->next = tail;
    head->prev = head;
    tail->next = tail;
    tail->prev = head;
    
    insert(2);
    insert(3);
    insert(6);
    insert(7);
    show();
    printf("\n");
    removeFront();
    removeFront();
    show();

    return 0;
}