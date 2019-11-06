#include <stdlib.h>
#define SIZE 10000
#define INF 99999999

// 배열을 이용한 큐 선언
// 뒤쪽으로 들어가서 앞쪽으로 나오는 자료구조
int queue[SIZE];
int front = 0;
int rear = 0;

// 큐 삽입 함수
void push(int data) {
    if (rear >= SIZE) {
        printf("queue overflow \n");
        return;
    }
    queue[rear++] = data;
}

int pop() {
    if (front == rear) {
        printf("queue underflow \n");
        return -INF;
    }
    return queue[front++];
}

void show() {
    printf("--- 큐의 앞 ---\n");
    for (int i = front; i < rear; i++) {
        printf("%d\n", queue[i]);
    }
    printf("--- 큐의 뒤 ---\n");
}

int main(void) {
    push(3);
    push(2);
    push(8);
    push(5);
    show();
    printf("--pop--\n");
    pop();
    show();
    return 0;
}