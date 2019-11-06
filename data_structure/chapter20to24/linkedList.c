#include <stdio.h>
#include <stdlib.h>

// 연결리스트 선언. Node라는 구조체를 생성
typedef struct {
    int data;
    struct Node *next;
} Node;

// Node 구조체 형태의 head를 정의
Node *head;

// 연결 리스트 삽입 함수
// 삽입하고 싶은 노드의 바로 전 노드가 root. 즉, root 뒤로 들어감
void addFront(Node *root, int data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    // root의 next를 node의 next로 넣고
    node->next = root->next;
    // root의 next를 node로 넣어줌.
    root->next = node;
}

// 연결 리스트 삭제 함수
// 삭제하고 싶은 노드의 바로 전 노드가 root. 즉, root 뒤의 노드가 삭제
void removeFront(Node *root) {
    Node *front = root->next;
    // front의 next를 root의 next로
    root->next = front->next;
    // front의 메모리를 해제. front는 삭제.
    free(front);

    // TODO: 삭제할 원소가 없는 삭제하는 경우 방지
}

// 연결리스트 메모리 해제함수
void freeAll(void) {
    Node *cur = head->next;
    Node *next;
    while (cur != NULL) {
        next = cur->next;
        // Node *next = cur->next;
        free(cur);
        cur = next;
    }
}

void showAll(void) {
    Node *cur = head->next;
    while (cur != NULL){
        printf("%d /", cur->data);
        cur = cur->next;
    }
}

int main(void) {
    // 최초 예시
    // head = (Node*) malloc(sizeof(Node));
    // Node *node1 = (Node*) malloc(sizeof(Node));
    // node1->data = 1;
    // Node *node2 = (Node*) malloc(sizeof(Node));
    // node2->data = 2;
    // head->next = node1;
    // node1->next = node2;
    // node2->next = NULL;
    // Node *cur = head->next;
    // while (cur != NULL) {
    //     printf("%d /", cur->data);
    //     cur = cur->next;
    // }

    // 함수들을 이용한 예시
    head = (Node*) malloc(sizeof(Node));
    head->next = NULL;
    addFront(head, 2);
    addFront(head, 3);
    addFront(head, 5);
    addFront(head, 6);
    showAll();
    printf("\n");
    removeFront(head);
    showAll();
    freeAll();
    return 0;
}