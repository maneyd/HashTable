#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "hashtable.h"

HashTable* init(int capacity){
  HashTable *table = malloc(sizeof(HashTable)); // size of HashTable struct 
  table->entries = malloc(sizeof(Entry) * capacity); 
  table->count = 0; 
  table->capacity = capacity;

  for(int i = 0 ; i < capacity ; i++){
    table->entries[i].key[0] = '\0';
  }

  return table;
}

int hash(char *key, int capacity){
  unsigned long h = 5381;
    int c;
    
    while((c = *key++)) {
        h = ((h << 5) + h) + c;
    }
 

    return h % capacity;
}

void insert(HashTable *table, char *key, int value){
	int index = hash(key , table->capacity);
  int tombstone_index = -1;

  while(1) {
    if (table->entries[index].key[0] != '\0' && table->entries[index].key[0] != '\1') {
      if (strcmp(table->entries[index].key, key) == 0) {
        table->entries[index].value = value;
        return;
      }
    }
    else if (table->entries[index].key[0] == '\1') {
      if (tombstone_index == -1) {
        tombstone_index = index;
      }
    }
    else if (table->entries[index].key[0] == '\0') {
      int target_index = (tombstone_index != -1) ? tombstone_index : index;

      strcpy(table->entries[target_index].key, key);
      table->entries[target_index].value = value;
      table->count++;
      return;
    }

    index = (index + 1) % table->capacity;
  }
}

int search(HashTable* table, char *key){
 int index = hash(key , table->capacity);

  while(1) {

	if(table->entries[index].key[0] == '\0' ){
    return -1;
	}
  else if(strcmp(table->entries[index].key , key) == 0 && table->entries[index].key[0] != '\1'){
    return table->entries[index].value;
	}
  else{
		index = (index + 1) % table->capacity; 
	}
  
  }
 
}

void delete(HashTable *table, char *key){
 int index = hash(key , table->capacity);
  
 while(1){
  if(table->entries[index].key[0] == '\0'){
    break;
  }
  else if(strcmp(table->entries[index].key, key) == 0 && table->entries[index].key[0] != '\1'){
    table->entries[index].key[0] = '\1';
    table->count--;
    break;
  }
  else{
    index = (index + 1) % table->capacity; 
  }
 }
}

void freeHashTable(HashTable *table){
  free(table->entries);
  free(table);
}

void display(HashTable *table) {
    printf("\n--- Hash Table State (Count: %d, Capacity: %d) ---\n", table->count, table->capacity);
    for (int i = 0; i < table->capacity; i++) {
        if (table->entries[i].key[0] == '\0') {
            printf("[%d]: EMPTY\n", i);
        } else if (table->entries[i].key[0] == '\1') {
            printf("[%d]: <TOMBSTONE>\n", i);
        } else {
            printf("[%d]: Key = \"%s\", Value = %d\n", i, table->entries[i].key, table->entries[i].value);
        }
    }
    printf("---------------------------------------------------\n\n");
}
