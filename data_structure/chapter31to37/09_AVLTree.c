#include <stdio.h>
#include <stdlib.h>

int getMax(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

typedef struct
{
    int data;
    int height; // 높이 저장
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

int getHeight(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

void setHeight(Node *node)
{
    // 왼쪽 노드와 오른쪽 노드 중에서 더 높은 노드의 높이 + 1
    node->height = getMax(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

int getDifference(Node *node)
{
    // 왼쪽노드와 오른쪽 노드의 차이를 반환함.
    if (node == NULL)
        return 0;
    Node *leftChild = node->leftChild;
    Node *rightChild = node->rightChild;
    return getHeight(leftChild) - getHeight(rightChild);
}

// LL회전
// node는 원래 루트 노드(엄밀히 말하면 루트는 아니지만, 바꾸려는 노드들의 최상단 노드를 의미)
// 루트 노드의 L자식을 루트 노드로 만들고, 루트를 L자식의 R자식으로 만든다.
// L자식의 R자식을 원래 루트노드의 L자식으로 만든다.
Node *rotateLL(Node *node)
{
    Node *leftChild = node->leftChild;
    node->leftChild = leftChild->rightChild;
    leftChild->rightChild = node;
    // node의 height를 다시 계산
    setHeight(node);
    return leftChild;
}

// RR 회전 - LL회전과 반대
// node는 원래 루트 노드(엄밀히 말하면 루트는 아니지만, 바꾸려는 노드들의 최상단 노드를 의미)
// 루트노드의 R자식을 루트노드로 만들고, 루트를 R자식의 L자식으로 만든다.
// R자식의 L자식을 원래 루트노드의 R자식으로 만든다.
Node *rotateRR(Node *node)
{
    Node *rightChild = node->rightChild;
    node->rightChild = rightChild->leftChild;
    rightChild->leftChild = node;
    // node의 height를 다시 계산
    setHeight(node);
    return rightChild;
}

// LR회전
// 루트노드의 L자식 기준으로 RR회전 실행
// 루트노드 기준으로 LL회전 실행
Node *rotateLR(Node *node)
{
    Node *leftChild = node->leftChild;
    node->leftChild = rotateLL(leftChild);
    return rotateLL(node);
}

// RL회전
// 루트노드의 R자식 기준으로 LL회전 실행
// 루트노드 기준으로 RR회전 실행
Node *rotateRL(Node *node)
{
    Node *rightChild = node->rightChild;
    node->rightChild = rotateLL(rightChild);
    return rotateRR(node);
}

Node *balance(Node *node)
{
    int difference = getDifference(node);
    if (difference >= 2)
    {
        // 왼쪽자식이 더 큰경우
        if (getDifference(node->leftChild) >= 1)
        {
            // 왼쪽 자식의 차이가 1이 넘으면 LL 회전실행
            node = rotateLL(node);
        }
        else
        {
            node = rotateLR(node);
        }
    }
    else if (difference <= -2)
    {
        // 오른쪽 자식이 더 큰 경우
        if (getDifference(node->rightChild <= -1))
        {
            node = rotateRR(node);
        }
        else
        {
            node = rotateRL(node);
        }
    }
    setHeight(node);
    return node;
}

Node *insertNode(Node *node, int data)
{
    printf("%d 입력 \n", data);
    if (!node)
    {
        node = (Node *)malloc(sizeof(Node));
        node->data = data;
        node->height = 1;
        node->leftChild = node->rightChild = NULL;
    }
    else if (data < node->data)
    {
        node->leftChild = insertNode(node->leftChild, data);
        node = balance(node);
    }
    else if (data > node->data)
    {
        node->rightChild = insertNode(node->rightChild, data);
        node = balance(node);
    }
    else
    {
        printf("데이터 중복 발생\n");
    }
    return node;
}

Node *root = NULL;

void display(Node *node, int level)
{
    if (node != NULL)
    {
        display(node->rightChild, level + 1);
        printf("\n");
        if (node == root)
        {
            printf("Root: ");
        }
    }
    for (int i = 0; i < level && node != root; i++)
    {
        printf("    ");
    }
    printf("%d(%d)", node->data, getHeight(node));
    display(node->leftChild, level + 1);
}

int main(void)
{
    root = insertNode(root, 7);
    root = insertNode(root, 6);
    root = insertNode(root, 5);
    root = insertNode(root, 3);
    root = insertNode(root, 1);
    root = insertNode(root, 9);
    root = insertNode(root, 8);
    root = insertNode(root, 12);
    root = insertNode(root, 16);
    root = insertNode(root, 18);
    root = insertNode(root, 23);
    root = insertNode(root, 21);
    root = insertNode(root, 14);
    root = insertNode(root, 15);
    root = insertNode(root, 19);
    root = insertNode(root, 20);
    display(root, 1);
    printf("\n");
}
