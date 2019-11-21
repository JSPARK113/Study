#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int data;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

// 이진 탐색 트리의 삽입
Node *insertNode(Node *root, int data)
{
    if (root == NULL)
    {
        // root가 비었으면 root에 data 노드 입력
        root = (Node *)malloc(sizeof(Node));
        root->leftChild = root->rightChild = NULL;
        root->data = data;
        return root;
    }
    else
    {
        if (root->data > data)
        {
            // root가 data보다 크면 data를 왼쪽에 넣음
            // 아래 노드에서 재귀적으로 반복
            root->leftChild = insertNode(root->leftChild, data);
        }
        else
        {
            // root가 data보다 작으면 data를 오른쪽에 넣음
            // 아래 노드에서 재귀적으로 반복
            root->rightChild = insertNode(root->rightChild, data);
        }
    }
    return root;
}

// 이진 탐색 트리의 탐색
Node *searchNode(Node *root, int data)
{
    // root부터 데이터 탐색
    if (root == NULL)
        return NULL;
    if (root->data == data)
        // 루트가 데이터면 루트 반환
        return root;
    else if (root->data > data)
        // 루트가 데이터보다 크면 루트의 왼쪽만 탐색
        return searchNode(root->leftChild, data);
    else
        // 루트가 데이터보다 작으면 루트의 오른쪽만 탐색
        return searchNode(root->rightChild, data);
}

// preorder로 출력
void preorder(Node* root) {
    if (root ==NULL) return;
    printf("%d ", root->data);
    preorder(root->leftChild);
    preorder(root->rightChild);
}

int main(void){
    Node* root = NULL;
    root = insertNode(root, 30);
    root = insertNode(root, 17);
    root = insertNode(root, 48);
    root = insertNode(root, 5);
    root = insertNode(root, 23);
    root = insertNode(root, 37);
    root = insertNode(root, 50);
    preorder(root);
}
