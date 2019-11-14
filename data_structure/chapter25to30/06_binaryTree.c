#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    Node *leftChild;
    Node *rightChild;
};

Node* initNode(int data, Node* leftChild, Node* rightChild) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->leftChild = leftChild;
    node->rightChild = rightChild;
    return node;
}

// 전위순회
// 자기자신 - 왼쪽 자식 - 오른쪽 자식
void preorder(Node* root)
{
    if (root)
    {
        printf("%d ", root->data);
        preorder(root->leftChild);
        preorder(root->rightChild);
    }
}

// 중위 순회
// 왼쪽 자식 - 자기자신 - 오른쪽 자식
void inorder(Node* root)
{
    if (root)
    {
        inorder(root->leftChild);
        printf("%d ", root->data);
        inorder(root->rightChild);
    }
}

// 후위순회
// 왼쪽자식-오른쪽자식-자기자신
void postorder(Node* root)
{
    if (root)
    {
        postorder(root->leftChild);
        postorder(root->rightChild);
        printf("%d ", root->data);
    }
}

int main(void) {
    Node* n7 = initNode(50, NULL, NULL);
    Node* n6 = initNode(30, NULL, NULL);
    Node* n5 = initNode(23, NULL, NULL);
    Node* n4 = initNode(37, NULL, NULL);
    Node* n3 = initNode(56, n6, n7);
    Node* n2 = initNode(96, n4, n5);
    Node* n1 = initNode(83, n2, n3);

    preorder(n1);
    printf("\n");
    inorder(n1);
    printf("\n");
    postorder(n1);
}