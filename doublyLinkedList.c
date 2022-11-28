#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define listNode struct list_node *
#define list_append_string(list, myString) list_append((listNode *)&list, (listNode)string_item_new(myString))
struct list_node
{
    listNode prev;
    listNode next;
};
listNode list_get_tail(listNode *head)
{
    listNode current_node = *head;
    listNode last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}
listNode list_append(listNode *head, listNode item)
{
    listNode tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}
listNode list_pop(listNode *head)
{
    listNode current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    (*head)->prev = NULL;
    current_head->next = NULL;
    return current_head;
}
struct string_item
{
    struct list_node node;
    const char *string;
};
struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}
listNode DeleteNode(listNode *head, int position)
{
    listNode currentNode = *head;
    if (position <= 0)
    {
        return list_pop(head);
    }

    for (int i = 0; i < position; i++)
    {
        if (!currentNode->next)
        {
            return NULL;
        }
        currentNode = currentNode->next;
    }
    currentNode->next->prev = currentNode->prev;
    currentNode->prev->next = currentNode->next;
    currentNode->next = NULL;
    currentNode->prev = NULL;
    return currentNode;
}
void InsertAfter(listNode refNode, listNode item)
{
    item->prev = refNode;
    item->next = refNode->next;
    if(refNode->next)
        refNode->next->prev = item;
    refNode->next = item;
}
void InsertBefore(listNode refNode, listNode item)
{
    item->next = refNode;
    item->prev = refNode->prev;
    if(refNode->prev)
        refNode->prev->next = item;
    refNode->prev = item;
}
void InsertAfterIndex(listNode *head, int index, listNode item)
{
    listNode currentNode = *head;
    for (int i = 0; i < index; i++)
    {
        if (!currentNode->next)
            return;
        currentNode = currentNode->next;
    }
    listNode succ = currentNode->next;
    item->next = succ;
    item->prev = currentNode;
    succ->prev = item;
    currentNode->next = item;
}
void InsertBeforeIndex(listNode *head, int index, listNode item)
{
    listNode currentNode = *head;
    for (int i = 0; i < index; i++)
    {
        if (!currentNode->next)
            return;
        currentNode = currentNode->next;
    }
    listNode _prev = currentNode->prev;
    item->next = currentNode;
    item->prev = _prev;
    _prev->next = item;
    currentNode->prev = item;
}
int GetLength(listNode *head)
{
    listNode currentNode = *head;
    int i = 1;
    while (currentNode->next)
    {
        i++;
        currentNode = currentNode->next;
    }
    return i;
}

void Shuffle(listNode *head)
{
    int length = GetLength(head);
    listNode currentNode = *head;
    for (int i = 0; i < length; i++)
    {
        int r = rand() % length;
        printf("i = %d; r = %d\n", i, r);
        if(i==r){
            currentNode = currentNode->next;
            continue;
        }
        listNode swappingNode = currentNode;
        for (int j = i; j < r; j++)
        {
            swappingNode = swappingNode->next;
        }
        for (int j = i; j > r; j--)
        {
            swappingNode = swappingNode->prev;
        }
        

        if(i + 1 == r){
            currentNode->next = swappingNode->next;
            if(currentNode->next)
                currentNode->next->prev = currentNode;

            swappingNode->prev = currentNode->prev;
            if(swappingNode->prev)
                swappingNode->prev->next=swappingNode;

            currentNode->prev = swappingNode;
            swappingNode->next = currentNode;
        }
        else if(i == r + 1){
            swappingNode->next = currentNode->next;
            if(swappingNode->next)
                swappingNode->next->prev = swappingNode;

            currentNode->prev = swappingNode->prev;
            if(currentNode->prev)
                currentNode->prev->next=currentNode;

            currentNode->next = swappingNode;
            swappingNode->prev = currentNode;
        }
        else{
            listNode currNext = currentNode->next;
            listNode currPrev = currentNode->prev;
            
            currentNode->next = swappingNode->next;
            currentNode->prev = swappingNode->prev;

            swappingNode->next = currNext;
            swappingNode->prev = currPrev;
            if(currentNode->next)
                currentNode->next->prev = currentNode;
            if(currentNode->prev)
                currentNode->prev->next = currentNode;
            if(swappingNode->next)
                swappingNode->next->prev = swappingNode;
            if(swappingNode->prev)
                swappingNode->prev->next = swappingNode;
        }
        if(i == 0) *head = swappingNode;
        if(r == 0) *head = currentNode;
        currentNode = swappingNode->next;
    }
}
//int main()
//{
//    struct string_item *my_linked_list = NULL;
//    list_append_string(my_linked_list, "Hello World");
//    list_append_string(my_linked_list, "Test001");
//    list_append_string(my_linked_list, "Test002");
//    list_append_string(my_linked_list, "Last Item of the Linked List");
//    //DeleteNode((listNode *)&my_linked_list, 0);
//    Shuffle((listNode *)&my_linked_list);
//    Shuffle((listNode *)&my_linked_list);
//    Shuffle((listNode *)&my_linked_list);
//
//    //InsertBeforeIndex((listNode *)&my_linked_list, 2, (listNode)string_item_new("myString"));
//    struct string_item *string_item = my_linked_list;
//
//    while (string_item)
//    {
//        printf("%s\n", string_item->string);
//        string_item = (struct string_item *)string_item->node.next;
//    }
//
//    return 0;
//}