#ifndef CHASH_MAP_H
#define CHASH_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASH_SIZE
    #define HASH_SIZE 1000
#endif

typedef struct _entry entry_t;
struct _entry {
    char* key;
    void* value;
    entry_t* next;
};

typedef struct {
    entry_t* entries[HASH_SIZE];
} chash_map_t;

void chash_map_init(chash_map_t* map);

void chash_map_insert(chash_map_t* map, char* key, void* value);

void* chash_map_get(chash_map_t* map, char* key);

void chash_map_remove(chash_map_t* map, char* key);

void chash_map_free(chash_map_t* map);

#endif // CHASH_MAP_H
