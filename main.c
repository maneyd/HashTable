#include <stdio.h>
#include "hashtable.h"

int main() {
    HashTable *table = init(5);

    printf("1. Initial state after inserting key1, key2, key3:");
    insert(table, "key1", 100);
    insert(table, "key2", 200);
    insert(table, "key3", 300);
    display(table);

    printf("2. State after deleting 'key1':");
    delete(table, "key1");
    display(table);

    printf("3. State after inserting 'key4' (reusing tombstone):");
    insert(table, "key4", 400);
    display(table);

    return 0;
}
