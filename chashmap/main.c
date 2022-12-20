#include "chashmap.h"
#include <assert.h>

void test_chash_map() {
    printf("Running tests...\n");

    chash_map_t map;

    chash_map_init(&map);

    assert(chash_map_get(&map, "key1") == NULL);

    chash_map_insert(&map, "key1", "value1");
    chash_map_insert(&map, "key2", "value2");
    chash_map_insert(&map, "key3", "value3");

    assert(strcmp((char*)chash_map_get(&map, "key1"), "value1") == 0);
    assert(strcmp((char*)chash_map_get(&map, "key2"), "value2") == 0);
    assert(strcmp((char*)chash_map_get(&map, "key3"), "value3") == 0);

    chash_map_remove(&map, "key2");

    assert(strcmp((char*)chash_map_get(&map, "key1"), "value1") == 0);
    assert(chash_map_get(&map, "key2") == NULL);
    assert(strcmp((char*)chash_map_get(&map, "key3"), "value3") == 0);

    chash_map_free(&map);

    printf("All tests passed\n");
}

int main(int argc, char* argv[]) {
    test_chash_map();
    return EXIT_SUCCESS;
}