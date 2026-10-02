#include<stdio.h>
#include<string.h>

#define table_size 10

//object
typedef struct{
	char key[100];
	int value;
}object;

//array of object

typedef struct{
	object array[10];
	int size;
}HashTable; 


//hash function
int hash(char *string,int size){

	unsigned long hash = 5381; 
	int c;

  while((c = *string++)) {
    hash = ((hash << 5) + hash) + c;  // hash*33 + c
  }	

	return hash % size;
}

//search -> key -> T/F 
void search(char *key , HashTable *table){
	int index = hash(key , table->size);

  while(1) {

	if(table->array[index].key[0] == '\0'){
		printf("\n no element found");
    break;
	}
  else if(strcmp(table->array[index].key , key) == 0){
			printf("\n key matched!!");
			printf("\n value = %d",table->array[index].value);
      break;
	}else{
		index = (index + 1) % table->size; 
	  }
  }
}

int insert(HashTable *table, char *key , int value){
	int index = hash(key , table->size);

	while(1){
	  if(table->array[index].key[0] == '\0'){
	    printf("\ninserting at index : %d\n",index);
	    strcpy(table->array[index].key,key);
	    table->array[index].value = value;
	    break;
	  }else{
	    index = (index + 1) % table->size;
	  }
  }
}


int main(){
	
	HashTable table;
	table.size = table_size;

	for(int i = 0; i < 10; i++) table.array[i].key[0] = '\0';

	printf("\n--- Inserting ab ---");	
	insert(&table, "ba", 10);
	
	printf("\n--- Inserting ba ---");	
	insert(&table, "ab", 20);
	
	printf("\n--- Searching ab ---");	
	search("ab", &table);
	
	printf("\n--- Searching ba ---");	
	search("ba", &table);

  return 1;
}
