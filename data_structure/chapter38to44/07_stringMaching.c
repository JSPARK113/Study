#include <stdio.h>
#include <string.h>

char *parent = "ABCDEFG";
char *pattern = "EF";

// 단순 문자열 매칭
int main(void)
{
    int parentSize = strlen(parent);
    int patternSize = strlen(pattern);
    for (int i = 0; i <= parentSize - patternSize; i++)
    {
        // 앞글자(i자리)를 먼저 비교
        int found = 1;
        for (int j = 0; i < parentSize - patternSize; i++)
        {
            // i자리부터 pattern과 parent를 한자리씩 비교
            if (parent[i + j] != pattern[j])
            {
                // parent와 pattern이 같지 않으면 break
                found = 0;
                break;
            }
        }
        if (found)
        {
            // found가 1이면 찾았다고 출력
            printf("%d번째에서 찾았습니다.\n", i + 1);
        }
    }
}