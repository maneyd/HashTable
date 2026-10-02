#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct {
  char key[100];
  int value;
} Entry;

typedef struct {
  Entry *entries; // dynamic 
  int count;
  int capacity;
} HashTable;

HashTable* init(int capacity);
void insert(HashTable *table, char *key , int value);
int search(HashTable *table, char *key);
void delete(HashTable *table, char *key);
void freeHashTable(HashTable *table);
void display(HashTable *table);

#endif
