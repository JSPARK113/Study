#include <stdio.h>
#include <stdlib.h>
#define INF 99999999

typedef struct {
    int data;
    struct Node *next;
} Node;

// top을 가진 Stack을 선언
typedef struct {
    Node *top;
} Stack;

// 스택 삽입 함수
void push(Stack *stack, int data) {
    // stack의 top에 data를 가진 노드 추가
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    // node가 기존 top을 대체해서 top이 됨.
    node->next = stack->top;
    stack->top = node;
}

// 맨 위의 값을 return하고 삭제
int pop(Stack *stack) {
    if (stack->top == NULL) {
        // 더이상 삭제할 노드가 없는 경우
        printf("스택 언더플로우가 발생했습니다.\n");
        return -INF;
    }
    Node *node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);
    return data;
}

void show(Stack *stack) {
    Node *cur = stack->top;
    printf("---스택의 최상단---\n");
    while (cur != NULL) {
        printf("%d\n", cur->data);
        cur = cur->next;
    }
    printf("---스택의 최하단---\n");
}

int main(void){
    Stack stack;
    stack.top = NULL;
    show(&stack);
    push(&stack, 3);
    push(&stack, 5);
    push(&stack, 7);
    push(&stack, 9);
    show(&stack);
    printf("--pop twice--\n");
    pop(&stack);
    pop(&stack);
    show(&stack);
    return 0;
}