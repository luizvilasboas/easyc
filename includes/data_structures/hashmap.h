#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stddef.h>
#include <stdbool.h>

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
    size_t size;
    unsigned long (*hash_fn)(void *);
    int (*cmp_fn)(void *, void *);
} HashMap;

void hashmap_init(HashMap *map, size_t bucket_count, size_t key_size, size_t value_size, unsigned long (*hash_fn)(void *), int (*cmp_fn)(void *, void *));
void hashmap_destroy(HashMap *map);
bool hashmap_insert(HashMap *map, void *key, void *data);
bool hashmap_remove(HashMap *map, void *key);
bool hashmap_update(HashMap *map, void *key, void *new_data);
void *hashmap_get(HashMap *map, void *key);
int hashmap_size(HashMap *map);

#endif // HASHMAP_H_
