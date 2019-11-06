#include <stdio.h>
#define INF 10000

int arr[INF];
int count = 0;

void addBack(int data) {
    // count 인덱스 순서에 데이터를 넣고
    arr[count] = data;
    // count를 하나 늘려줌.
    count++;
}

void addFirst(int data) {
    // 기존 데이터를 한칸씩 뒤로 미루고
    for (int i = count; i>=1; i--) {
        arr[i] = arr[i-1];
    }
    // 새로운 데이터를 맨 앞에 넣어주고
    arr[0] = data;
    // count에 1을 더한다.
    count++;
}

void show() {
    for (int i=0; i < count; i++) {
        printf("%d", arr[i]);
    }
}

// 특정 위치의 원소 삭제
void removeAt(int index){
    // 지우고 싶은 인덱스 다음부터의 값을 하나씩 땡겨줌.
    for (int i = index; i < count -1; i++) {
        arr[i] = arr[i+1];
    }
    // count에서 하나 뺌
    count--;
}

int main(void) {
    addFirst(4);
    addFirst(5);
    addFirst(1);
    show();
    printf("\n");
    addBack(7);
    addBack(4);
    show();
    return 0;
}