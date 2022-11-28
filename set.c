#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SetNode struct set_node *
size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}
struct set_node
{
    const char *key;
    size_t key_len;
    SetNode next;

};
struct set_table
{
    SetNode *nodes;
    size_t hashmap_size;
};

struct set_table *set_table_new(const size_t hashmap_size)
{
    struct set_table *table = malloc(sizeof(struct set_table));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(SetNode));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}
struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct set_node *head = table->nodes[index];
    if (!head)
    {
        table->nodes[index] = malloc(sizeof(struct set_node));
        if (!table->nodes[index])
        {
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;
        return table->nodes[index];
    }
    struct set_node *new_item = malloc(sizeof(struct set_node));
    if (!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;
    struct set_node *tail = head;
    while (head)
    {
        if (head->key == key)
            return NULL;
        tail = head;
        head = head->next;
    }
    tail->next = new_item;
    return new_item;
}

SetNode SearchWithLoop(struct set_table *table, char *key)
{
    SetNode current = *table->nodes;
    while (current->next)
    {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}
size_t GetIndex(struct set_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    return hash % table->hashmap_size;
}

SetNode Search(struct set_table *table, char *key, const size_t key_len)
{
    SetNode current = table->nodes[GetIndex(table, key, key_len)];
    while (current)
    {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}
SetNode Removal(struct set_table *table, char *key, const size_t key_len)
{
    int index = GetIndex(table, key, key_len);
    SetNode current = table->nodes[index];
    SetNode prev;
    while (current->key != key)
    {
        prev->next = current;
        current = current->next;
        if(!current)return NULL;
    }
    if(prev){
        prev->next = current->next;

    }
    table->nodes[index] = current->next;
    current->next = NULL;
    return current;
}

//int main()
//{
//    const int hashmap_size = 10;
//    struct set_table *table = set_table_new(hashmap_size);
//    set_insert(table, "Hello World", hashmap_size);
//    set_insert(table, "Test001", hashmap_size);
//    set_insert(table, "Test002", hashmap_size);
//    set_insert(table, "Last Item of the Linked List", hashmap_size);
//
//    SetNode a = Search(table, "Test001", hashmap_size);
//    printf("%s", a->key);
//    a = Removal(table, "Test001", hashmap_size);
//    printf("%s", a->key);
//
//    return 0;
//}