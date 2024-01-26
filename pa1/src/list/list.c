

#include <stdlib.h>
#include <stdio.h>

int n = 0;
struct node
{
    int val;
    struct node *next;
};

struct node *insert_node(struct node *head, struct node *temp)
{
    int val = temp->val;
    if (head == NULL || head->val > val)
    {
        temp->next = head;
        head = temp;
        n++;
        return head;
    }
    struct node *p = head;
    struct node *prev;
    while (p != NULL)
    {
        if (p->val < val)
        {
            prev = p;
            p = p->next;
        }
        else if (p->val == val)
        {
            free(temp);
            return head;
        }
        else if (p->val > val)
        {
            temp->next = p;
            prev->next = temp;
            n++;
            return head;
        }
    }
    if (p == NULL)
    {
        prev->next = temp;
        n++;
    }
    return head;
}

struct node *delete_node(struct node *head, int val)
{
    struct node *p = head;
    struct node *temp;
    if (head == NULL)
    {
        return head;
    }
    else if (head->val == val)
    {
        head = p->next;
        free(p);
        n--;
        return head;
    }
    while (p->next != NULL)
    {
        if (p->next->val == val)
        {
            temp = p->next;
            p->next = temp->next;
            free(temp);
            n--;
            return head;
        }
        else if (p->val < val)
        {
            p = p->next;
        }
        else if (p->val > val)
        {
            return head;
        }
    }
    return head;
}

void printLinkedList(struct node *head)
{
    struct node *p = head;
    printf("%d :", n);
    for (; p != NULL; p = p->next)
    {
        printf(" %d", p->val);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    struct node *head = NULL;
    char c;
    int i;
    while (scanf(" %c%d", &c, &i) != EOF)
    {
        if (c == 'i')
        {
            struct node *temp = malloc(sizeof(struct node));
            temp->val = i;
            temp->next = NULL;

            head = insert_node(head, temp);
            printLinkedList(head);
        }
        else if (c == 'd')
        {
            head = delete_node(head, i);
            printLinkedList(head);
        }
    }
    struct node *p = head;
    while (p->next != NULL) {
        head = p;
        p = p -> next;
        free(head);
    }

    free(p);
    p = NULL;
    return EXIT_SUCCESS;
}
