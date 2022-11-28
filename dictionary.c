#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DictionaryNode struct Dictionary_node *
size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}
struct Dictionary_node
{
    const char *key;
    const char *value;
    size_t key_len;
    DictionaryNode next;

};
struct Dictionary_table
{
    DictionaryNode *nodes;
    size_t hashmap_size;
};

struct Dictionary_table *Dictionary_table_new(const size_t hashmap_size)
{
    struct Dictionary_table *table = malloc(sizeof(struct Dictionary_table));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(DictionaryNode));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}
struct Dictionary_node *Dictionary_insert(struct Dictionary_table *table, const char *key, const char *value, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    struct Dictionary_node *head = table->nodes[index];
    if (!head)
    {
        table->nodes[index] = malloc(sizeof(struct Dictionary_node));
        if (!table->nodes[index])
        {
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->value = value;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;
        return table->nodes[index];
    }
    struct Dictionary_node *new_item = malloc(sizeof(struct Dictionary_node));
    if (!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->value = value;
    new_item->key_len = key_len;
    new_item->next = NULL;
    struct Dictionary_node *tail = head;
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

DictionaryNode SearchWithLoop(struct Dictionary_table *table, char *key)
{
    DictionaryNode current = *table->nodes;
    while (current->next)
    {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}
size_t GetIndex(struct Dictionary_table *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    return hash % table->hashmap_size;
}

DictionaryNode Search(struct Dictionary_table *table, char *key, const size_t key_len)
{
    DictionaryNode current = table->nodes[GetIndex(table, key, key_len)];
    while (current)
    {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return NULL;
}
DictionaryNode Removal(struct Dictionary_table *table, char *key, const size_t key_len)
{
    DictionaryNode current = table->nodes[GetIndex(table, key, key_len)];
    DictionaryNode prev;
    while (current->key != key)
    {
        prev->next = current;
        current = current->next;
        if(!current)return NULL;
    }
    if(prev)
        prev->next = current->next;
    current->next = NULL;
    return current;
}

//int main()
//{
//    const int hashmap_size = 10;
//    struct Dictionary_table *table = Dictionary_table_new(hashmap_size);
//    Dictionary_insert(table,"hello", "Hello World", hashmap_size);
//    Dictionary_insert(table,"1", "Test001", hashmap_size);
//    Dictionary_insert(table,"2", "Test002", hashmap_size);
//    Dictionary_insert(table,"last", "Last Item of the Linked List", hashmap_size);
//
//    DictionaryNode a = Search(table, "1", hashmap_size);
//    printf("%s", a->value);
//
//    return 0;
//}