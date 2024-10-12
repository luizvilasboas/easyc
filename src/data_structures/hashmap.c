#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../includes/data_structures/hashmap.h"

static HashNode *create_node(size_t key_size, size_t value_size, void *key, void *value) {
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    assert(new_node != NULL);

    new_node->key = malloc(key_size);
    new_node->value = malloc(value_size);
    assert(new_node->key != NULL && new_node->value != NULL);

    memcpy(new_node->key, key, key_size);
    memcpy(new_node->value, value, value_size);
    new_node->next = NULL;

    return new_node;
}

void hashmap_init(HashMap *map, size_t bucket_count, size_t key_size, size_t value_size, unsigned long (*hash_fn)(void *), int (*cmp_fn)(void *, void *)) {
    map->buckets = (HashNode **)calloc(bucket_count, sizeof(HashNode *));
    assert(map->buckets != NULL);

    map->bucket_count = bucket_count;
    map->key_size = key_size;
    map->value_size = value_size;
    map->hash_fn = hash_fn;
    map->cmp_fn = cmp_fn;
}

void hashmap_destroy(HashMap *map) {
    for (size_t i = 0; i < map->bucket_count; i++) {
        HashNode *node = map->buckets[i];

        while (node != NULL) {
            HashNode *tmp = node;
            node = node->next;

            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }

    free(map->buckets);
}

void hashmap_insert(HashMap *map, void *key, void *value) {
    unsigned long hash_value = map->hash_fn(key) % map->bucket_count;

    HashNode *current = map->buckets[hash_value];
    while (current != NULL) {
        if (map->cmp_fn(current->key, key) == 0) {
            memcpy(current->value, value, map->value_size);
            return;
        }

        current = current->next;
    }

    HashNode *new_node = create_node(map->key_size, map->value_size, key, value);
    new_node->next = map->buckets[hash_value];
    map->buckets[hash_value] = new_node;
}

void *hashmap_search(HashMap *map, void *key) {
    unsigned long hash_value = map->hash_fn(key) % map->bucket_count;

    HashNode *current = map->buckets[hash_value];
    while (current != NULL) {
        if (map->cmp_fn(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void hashmap_remove(HashMap *map, void *key) {
    unsigned long hash_value = map->hash_fn(key) % map->bucket_count;

    HashNode *current = map->buckets[hash_value];
    HashNode *prev = NULL;
    while (current != NULL) {
        if (map->cmp_fn(current->key, key) == 0) {
            if (prev == NULL) {
                map->buckets[hash_value] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void hashmap_foreach(HashMap *map, void (*func)(void *, void *)) {
    for (size_t i = 0; i < map->bucket_count; i++) {
        HashNode *current = map->buckets[i];

        while (current != NULL) {
            func(current->key, current->value);
            current = current->next;
        }
    }
}
