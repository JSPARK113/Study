#include <stdio.h>
#define SIZE 1000

int a[SIZE];

int swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n - 1; i++) {
        int j = i;
        // 앞에 있는 수가 뒤의 수보다 크면 자리바꿈(= 뒤로 보냄)
        while (j >= 0 && a[j] > a[j + 1]) {
            swap(&a[j], &a[j + 1]);
            j--;
        }
    }
    return 0;
}