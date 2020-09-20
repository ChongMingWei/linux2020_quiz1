#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
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
    if(!(*head))
        return;
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
    if(!(*head))
        return;
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
    if (!head || !head->next) {
        return head;
    }
    node_t *first = head;
    node_t *rest = head->next;
    rest = rev_recursive(rest);
    first->next->next = first;
    first->next = NULL;
    return rest;
}

void Fisher_Yates_shuffle(node_t **head, int size)
{
    if(!*head)
        return;
    srand(time(NULL));
    int i = size - 1;
    while(i > 0){//1<=i<=size-1
        //printf("i=%d\n",i); //current round
        node_t **indirect = head;
        int cnt = 0;
        int j = rand() % (i + 1); //0<=j<=i
        //printf("current j=%d\n",j); //current choosen index j
        if (i==j){
            //printf("skip: j=%d\n",j);
            --i;
            continue;
        }
        else{
            node_t *node_prei = NULL;
            node_t *node_prej = NULL;
            node_t *tmp_pre = NULL;
            node_t *tmp_next = NULL;
            if (j == 0) {
                int cnt = 1;
                /* find node i and j */
                node_prej = *indirect;
                while (cnt < i){
                    indirect = &(*indirect)->next;
                    ++cnt;
                }
                node_prei = *indirect;
                tmp_pre = *head;
                tmp_next = (*head)->next;
                /* exchange node i and j */
                if(node_prej == node_prei){//node_prei, node_prej and *head point to same node(head node)
                    (*head)->next = node_prei->next->next;
                    *head = tmp_next;
                    (*head)->next = tmp_pre;
                }
                else{
                    (*head)->next = node_prei->next->next;
                    *head = node_prei->next;
                    node_prei->next->next = tmp_next;
                    node_prei->next = tmp_pre;
                }
            } else {
                /* find node i and j */
                int cnt = 1;
                while(cnt < i){
                    if (cnt==j)
                        node_prej = *indirect;
                    indirect = &(*indirect)->next;
                    ++cnt;
                }
                node_prei = *indirect;
                /* exchange node i and j */
                tmp_pre = node_prej->next;
                tmp_next = node_prej->next->next;
                if (node_prei == node_prej->next){
                    node_prei->next = tmp_next->next;
                    node_prej->next = tmp_next;
                    tmp_next->next = tmp_pre;
                }
                else {
                    node_prej->next->next = node_prei->next->next;
                    node_prej->next = node_prei->next;
                    node_prei->next->next = tmp_next;
                    node_prei->next = tmp_pre;
                }
            }
        }
        --i;
    }
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
    Fisher_Yates_shuffle(&head,5);
    print_list(head);
    return 0;
}
