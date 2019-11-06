#include <stdio.h>
#include <stdlib.h>
#define INF 99999999

typedef struct {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int count;
} Queue;

// 큐 삽입함수
void push(Queue *queue, int data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    // 삽입할 노드는 끝에 들어가니까 next가 NULL임.
    node->next = NULL;
    // queue에 값이 하나도 없으면 front를 node로 함.
    if (queue->count == 0) {
        queue->front = node;
    }
    else {
        // 이미 노드가 있으면 맨 끝 노드(rear)의 next를 node로 함.
        queue->rear->next = node;
    }
    // 그리고 마지막 노드(rear)를 node로 바꿔줌
    queue->rear = node;
    queue->count++;
}

// 큐 추출함수
int pop(Queue *queue) {
    // 큐에 하나도 없으면 언더플로우
    if (queue->count ==0){
        printf("queue underflow\n");
        return -INF;
    }
    // 큐는 앞에서부터 나가니까 맨 첫 노드를 삭제
    Node *node = queue->front;
    int data = node->data;
    // 두번째 노드(node->next)를 큐의 front로 한다.
    queue->front = node->next;
    free(node);
    queue->count--;
    return data;
}

// 전체 출력함수
void show(Queue *queue) {
    Node *cur = queue->front;
    printf("--queue front--\n");
    while(cur != NULL) {
        printf("%d\n", cur->data);
        cur = cur->next;
    }
    printf("--queue rear--\n");
}

int main(void) {
    Queue queue;
    queue.front = queue.rear = NULL;
    queue.count = 0;
    push(&queue, 8);
    push(&queue, 2);
    push(&queue, 4);
    push(&queue, 3);
    push(&queue, 6);
    show(&queue);
    printf("--3 times pop--\n");
    pop(&queue);
    pop(&queue);
    pop(&queue);
    show(&queue);
    return 0;
}