#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 1000

char **array;
int founded;

int main(void)
{
    int n; // 배열 길이
    char *word; // 찾는 문자열
    word = malloc(sizeof(char) * LENGTH);
    scanf("%d %s", &n, word);
    array = (char **)malloc(sizeof(char *) * n); 
    for (int i = 0; i < n; i++)
    {
        // array에 문자입력
        array[i] = malloc(sizeof(char) * LENGTH);
        scanf("%s", array[i]);
    }
    for (int i = 0; i < n; i++)
    {
        // 인덱스 돌아가면서 array[i]와 word를 비교
        if (!strcmp(array[i], word))
        {
            printf("%d번째 원소입니다.\n", i + 1);
            founded = 1;
        }
    }
    if (!founded)
        printf("원소를 찾을 수 없습니다.\n");
    return 0;
}