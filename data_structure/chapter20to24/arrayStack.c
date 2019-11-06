#include <stdio.h>
#define SIZE 10
#define INF 99999999

// size가 10인 stack
int stack[SIZE];
// stack의 최상단 인덱스. 결국 배열의 뒤로만 들어갈 수 있고 나올 수 있음.
int top = -1;

// 배열을 이용한 스택 구현
void push(int data) {
    if (top == SIZE -1) {
        // 이미 꽉 찼으면 스택 오버플로우 발생
        printf("스택 오버플로우가 발생했습니다. \n");
        return;
    }
    // 여유가 있으면 stack에 데이터 넣음.
    stack[++top] = data;
}

int pop() {
    if (top == -1) {
        printf("스택 언더플로우가 발생했습니다. \n");
        return -INF;
    }
    return stack[top--];
}

void show() {
    printf("--스택의 최상단--\n");
    
    for (int i = top; i>=0; i--) {
        printf("%d /", stack[i]);
    }
    printf("\n--스택의 최하단--\n");
}

int main(void) {
    push(3);
    push(2);
    push(5);
    push(6);
    push(7);
    push(8);
    show();
    pop();
    pop();
    show();

    return 0;
}