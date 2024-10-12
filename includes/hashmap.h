#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stddef.h>

typedef struct HashNode {
    void *key;
    void *value;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    size_t bucket_count;
    size_t key_size;
    size_t value_size;
    unsigned long (*hash_fn)(void *);
    int (*cmp_fn)(void *, void *);
} HashMap;

void hashmap_init(HashMap *map, size_t bucket_count, size_t key_size, size_t value_size, unsigned long (*hash_fn)(void *), int (*cmp_fn)(void *, void *));
void hashmap_destroy(HashMap *map);
void hashmap_insert(HashMap *map, void *key, void *value);
void *hashmap_search(HashMap *map, void *key);
void hashmap_remove(HashMap *map, void *key);
void hashmap_foreach(HashMap *map, void (*func)(void *, void *));

#endif // HASHMAP_H_
