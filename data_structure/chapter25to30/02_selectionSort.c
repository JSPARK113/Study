#include <stdio.h>
#include <limits.h>
#define SIZE 1000

int a[SIZE];

int swap(int *a, int *b) {
    // a의 값을 temp에 넣고
    int temp = *a;
    // b의 값을 a에 넣고
    *a = *b;
    // b에 temp 값을 넣어서 a와 b의 자리를 바꿈
    *b = temp;
}

int main(void) {
    int n, min, index;
    scanf("%d", &n);
    // i가 0부터 n-1까지 값을 받아서 a 배열에 넣는다.
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    // a배열의 처음부터 끝까지 반복
    for (int i = 0; i < n; i++) {
        min = INT_MAX;
        // i부터 끝까지 가장 작은 수를 찾아서 i자리에 넣어줌
        for (int j = i; j < n; j++) {
            if (min > a[j]) {
                min = a[j];
                index = j;
            }
        }
        // &a[index]가 가장 작은 수
        swap(&a[i], &a[index]);
    }
    // 제대로 정렬이 됐는지 출력
    for (int i=0; i<n; i++) {
        printf("%d", a[i]);
    }
    return 0;
}