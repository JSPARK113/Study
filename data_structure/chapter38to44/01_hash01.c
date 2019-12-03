#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

// 해시테이블 선형조사법 구현하기

typedef struct
{
    int id;
    char name[20];
} Student;

// 해시 테이블 초기화
void init(Student **hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }
}

// 해시 테이블의 메모리를 반환
void destructor(Student **hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i] != NULL)
        {
            free(hashTable[i])
        }
    }
}

// 해시 테이블 내 빈공간 탐색
int findEmpty(Student **hashTable, int id)
{
    // id를 통해 해시값을 구해 i에 먼저 넣어주고
    int i = id % TABLE_SIZE;
    while (1)
    {
        // 빈칸이면 i를 반환하고, 아니면 i에 1을 더해서 다시 null인지 확인한다.
        if (hashTable[i % TABLE_SIZE] == NULL)
        {
            return i % TABLE_SIZE;
        }
        i++;
    }
}

// id에 매칭되는 데이터를 해시 테이블 내에서 찾음.
int search(Student **hashTable, int id)
{
    int i = id % TABLE_SIZE;
    while (1)
    {
        if (hashTable[i % TABLE_SIZE] == NULL)
            return -1;
        else if (hashTable[i % TABLE_SIZE]->id == id)
            return i;
        i++;
    }
}

// 해시테이블에 값 삽입
void add(Student **hashTable, Student *input, int key)
{
    hashTable[key] = input;
}

// 해시테이블에서 값 가져오기
Student *getValue(Student **hashTable, int key)
{
    return hashTable[key];
}

// 해시 테이블 내 모든 데이터 출력
void show(Student **hashTable)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i] != NULL)
        {
            printf("키: [%d] 이름 [%s]\n", i, hashTable[i]->name);
        }
    }
}

int main(void)
{
    // 해시테이블 생성 및 초기화
    Student **hashTable;
    hashTable = (Student **)malloc(sizeof(Student *) * TABLE_SIZE);
    init(hashTable);
    // Student id는 랜덤으로 값을 넣어줌.
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        Student *student = (Student *)malloc(sizeof(Student));
        student->id = rand() % 100000;
        sprintf(student->name, "사람%d", student->id);
        if (search(hashTable, student->id) == -1)
        {
            // 해시 테이블의 빈 곳을 찾아서 값을 넣어주기
            int index = findEmpty(hashTable, student->id);
            add(hashTable, student, index);
        }
    }

    show(hashTable);
    destructor(hashTable);
    return 0;
}
