#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *insertNode(TreeNode *root, int data)
{
    if (root == NULL)
    {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->value = data;
        printf("inserted\n");
        return newNode;
    }
    if (data < root->value)
    {
        root->left = insertNode(root->left, data);
    }
    else if (data > root->value)
    {
        root->right = insertNode(root->right, data);
    }
    else
    {
        printf("not inserted\n");
    }
    return root;
}

void searchValue(TreeNode *root, int data)
{
    if (root == NULL)
    {
        printf("absent\n");
        return;
    }
    if (data == root->value)
    {
        printf("present\n");
    }
    else if (data < root->value)
    {
        searchValue(root->left, data);
    }
    else
    {
        searchValue(root->right, data);
    }
}

void printTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("(");
    printTree(root->left);
    printf("%d", root->value);
    printTree(root->right);
    printf(")");
}

int findMaximum(TreeNode *root)
{
    while (root->right != NULL)
    {
        root = root->right;
    }
    return root->value;
}

TreeNode *deleteNode(TreeNode *root, int data)
{
    if (root == NULL)
    {
        printf("absent\n");
        return root;
    }
    if (data < root->value)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->value)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            root = NULL;
            printf("deleted\n");
        }
        else if (root->left == NULL)
        {
            TreeNode *temp = root;
            root = root->right;
            free(temp);
            printf("deleted\n");
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root;
            root = root->left;
            free(temp);
            printf("deleted\n");
        }
        else
        {
            int maxLeft = findMaximum(root->left);
            root->value = maxLeft;
            root->left = deleteNode(root->left, maxLeft);
        }
    }
    return root;
}

void freeTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    TreeNode *root = NULL;

    char action;
    int data;

    while (scanf(" %c", &action) != EOF)
    {
        if (action == 'i')
        {
            scanf("%d", &data);
            root = insertNode(root, data);
        }
        else if (action == 's')
        {
            scanf("%d", &data);
            searchValue(root, data);
        }
        else if (action == 'p')
        {
            if (root != NULL)
            {
                printTree(root);
            }
            printf("\n");
        }
        else if (action == 'd')
        {
            scanf("%d", &data);
            root = deleteNode(root, data);
        }
    }
    freeTree(root);
    return 0;
}
