#include "chashmap.h"

/// @brief Daniel J. Bernstein's popular `times 33' hash function
/// @param key is the key that will be hashed
/// @return hashed version of the given key
unsigned long hash(char* key) {
    // Magic Constant 5381:
    // odd number, prime number, deficient number
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) ^ c; // hash * 33 + c
    }

    return hash % HASH_SIZE;
}

void chash_map_init(chash_map_t* map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        map->entries[i] = NULL;
    }
}

void chash_map_insert(chash_map_t* map, char* key, void* value) {
    unsigned long index = hash(key);

    entry_t* entry = map->entries[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            // Key already exists, update the value
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    // Key does not exist, create a new entry
    entry = (entry_t*)malloc(sizeof(entry_t));
    entry->key = key;
    entry->value = value;
    entry->next = map->entries[index];
    map->entries[index] = entry;
}

void* chash_map_get(chash_map_t* map, char* key) {
    unsigned long index = hash(key);

    entry_t* entry = map->entries[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            // Key found, return the value
            return entry->value;
        }
        entry = entry->next;
    }

    // Key not found
    return NULL;
}

void chash_map_remove(chash_map_t* map, char* key) {
    unsigned long index = hash(key);

    entry_t* entry = map->entries[index];
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            free(map->entries[index]);
            map->entries[index] = NULL;
            break;
        }
        entry = entry->next;
    }
}

void chash_map_free(chash_map_t* map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        entry_t* entry = map->entries[i];
        while (entry) {
            entry_t* next = entry->next;
            free(entry);
            entry = next;
        }
    }
}
