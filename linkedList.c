#include <stddef.h> // required for NULL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define listNode struct list_node *
#define list_append_string(list, myString) list_append((listNode *)&list, (listNode )string_item_new(myString))
struct list_node
{
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
    listNode removedNode;
    if(position <= 0){
        return list_pop(head);
    }

    for (int i = 1; i < position; i++) 
    {
        if (!currentNode)
        {
            return NULL;
        }
        currentNode = currentNode->next; 
    }
    removedNode = currentNode->next;
    currentNode->next = currentNode->next->next; 
    removedNode->next = NULL;
    return removedNode;
}

listNode ReverseList(listNode *head){
    listNode currentNode = *head;
    listNode reversedList = NULL;
    listNode prevNode = reversedList;
    while (currentNode)
    {
        prevNode = currentNode;
        currentNode = currentNode -> next;
        prevNode -> next = reversedList;
        reversedList = prevNode;
    }
    *head = reversedList;
    return *head;
}
//int main()
//{
//    struct string_item *my_linked_list = NULL;
//    list_append_string(my_linked_list, "Hello World");
//    list_append_string(my_linked_list, "Test001");
//    list_append_string(my_linked_list, "Test002");
//    list_append_string(my_linked_list, "Last Item of the Linked List");
//    DeleteNode((listNode *)&my_linked_list, 2);
//    ReverseList((listNode *)&my_linked_list);
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