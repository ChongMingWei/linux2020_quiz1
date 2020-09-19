#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);//AA1
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;//AA2
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

node_t *swap_pair(node_t *head)
{
    for (node_t **node = &head; *node && (*node)->next; node = &(*node)->next->next) {//BB1
        node_t *tmp = *node;
        *node = (*node)->next;//BB2
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return head;
}

void swap_pair_modified(node_t **head)
{
    for(node_t **node = head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

node_t *reverse(node_t *head)
{
    node_t *cursor = NULL;
    while (head) {
        node_t *next = head->next;
        /*CCC*/
        head->next = cursor;
        cursor = head;
        head = next;
    }
    return cursor;
}

void reverse_modified(node_t **head)
{
    node_t **indirect = head;
    node_t *cursor = NULL;
    while (*indirect) {
        node_t *next = (*indirect)->next;
        (*indirect)->next = cursor;
        cursor = (*indirect);
        (*indirect) = next;
    }
    *head = cursor;
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

node_t *rev_recursive(node_t *head)
{
    if (!head->next) {
        return head;
    }
    node_t *first = head;
    node_t *rest = head->next;
    rest = rev_recursive(rest);
    first->next->next = first;
    first->next = NULL;
    return rest;
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);
    add_entry(&head, 112);
    
    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    //head = swap_pair(head);
    swap_pair_modified(&head);
    print_list(head);

    //head = reverse(head);
    //reverse_modified(&head);
    head = rev_recursive(head);
    print_list(head);

    return 0;
}
