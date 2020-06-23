#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <pthread.h>

#define NUM_OF_THREADS 40 // change to get user input from console 

int task_num = 50;

void* task(void *param);

struct node {
   int data;    
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

struct tsk_node_s {
    int task_num; //starting from 0
    int task_type; // insert:0, delete:1, search:2
    int value;
    struct tsk_node_s* next;
};

struct tsk_node_s array_tasks[200];

int currentTaskId = 0;

pthread_mutex_t awaketasklock;
pthread_cond_t conditionlock;

//display the list
void printList() {
   struct node *ptr = head;
	
   while(ptr != NULL) {
      printf("(%d) ",ptr->data);
      ptr = ptr->next;
   }
	
}

//insert link at the first location
void addFirst(int data) {

   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->data = data;
   link->next = head;
	
   head = link;
}

//delete first item
struct node* deleteFirst() {

    struct node *deletedNode = head;

    head = head->next;
	
    return deletedNode;
}

//is list empty
bool isEmpty() {
   return (head == NULL);
}

//list length
int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given data
struct node* find(int data) {

   struct node* current = head;

   if(isEmpty()) {
      return NULL;
   }

   while(current->data != data) {

      if(current->next == NULL) {
         return NULL;
      }
      else {
         current = current->next;
      }
   }      
   return current;
}
//delete a node with given index
struct node* deleteIndex(int index){

    struct node* current = head;
    struct node* previous = NULL;

    if(length() == 0){
        return NULL;
    }
    else if(length() <= index){
        return NULL;
    }
    else{
        int i = 0;
        while(i < index){
            previous = current;
            current = current->next;
            i++;
        }
        previous->next = current->next;
    }
}
//delete a node with given data
struct node* deleteData(int data) {

    struct node* current = head;
    struct node* previous = NULL;
	
    if(isEmpty()) {
        return NULL;
    }

    while(current->data != data) {

        //not found
        if(current->next == NULL) {
            return NULL;
        } 
        else {
            //continue searching
            previous = current;
            current = current->next;
        }
    }

    //if found is the first element
    if(current == head) {
         head = head->next;
    } 
    //found in elsewhere
    else {
        //discard the elements links
        previous->next = current->next;
    }    
    return current;
}

void sort() {
    
   int i, j, k, tempData;
   struct node *current;
   struct node *next;	
   int size = length();
   k = size ;
	
   for (i = 0 ;i < size-1; i++, k--) {
      current = head;
      next = head->next;
      for (j = 1;j < k; j++) {   
         if ( current->data > next->data ) {
            tempData = current->data;
            current->data = next->data;
            next->data = tempData;
         }	
         current = current->next;
         next = next->next;
      }
   }   
}


int Insert(int value){
    if(find(value)){
        printf("%d can not be inserted\n", value);
    }
    else{
        addFirst(value);
        sort();
        printf("%d is inserted\n", value);
    }
}
int Search(int value){
    if(find(value)){
            printf("%d is found\n", value);
        }
    else{
        printf("%d can not be found\n", value);
    }
}
int Delete(int value){
    if(find(value)){
        deleteData(value);
        sort();
        printf("%d is deleted\n", value);
    }
    else{
        printf("%d can not be found\n", value);
    }
}

int main() {

	pthread_t tid[NUM_OF_THREADS];
	int thread_no[NUM_OF_THREADS];
	int i=0;
	srand(time(NULL));

    //init cond signal
    if(pthread_cond_init(&conditionlock, NULL) != 0){
		printf("ERROR: Cannot initiate condition broadcast\n");
		return -1;
    }

    //init mutex
	if(pthread_mutex_init(&awaketasklock, NULL) != 0)
	{
		printf("ERROR: Cannot initiate mutex\n");
		return -1;
	}

    //create threads
	for(i=0; i<NUM_OF_THREADS; i++)
	{
		thread_no[i] = i;
		pthread_create(&tid[i], NULL, task, &thread_no[i]);
    }

   // printf("enter the amount of tasks");
   // scanf("%d", task_num);

    // create tasks
    for (int i = 0; i < task_num; i++){
        array_tasks[i].task_num = i;
        array_tasks[i].task_type = rand() % 3;
        array_tasks[i].value = rand() % 100;
        pthread_cond_signal(&conditionlock);
    }

    //condition broadcast
    pthread_cond_broadcast(&conditionlock);


	// Join and run threads
	for(i=0; i<NUM_OF_THREADS; i++)
	{
		pthread_join(tid[i], NULL);
	}


	//destroy the pthread tools
	pthread_mutex_destroy(&awaketasklock);
    pthread_cond_destroy(&conditionlock);
	printList();			
	return 0;
}


//task thread
void* task(void *param)
{
    int* thread_no = (int*)param;
	
	//obtain the lock
    pthread_mutex_lock(&awaketasklock);

    pthread_cond_wait(&conditionlock, &awaketasklock);
    if (currentTaskId > task_num){
	printf("231312");
}

    else if (array_tasks[currentTaskId].task_type == 0){
        Insert(array_tasks[currentTaskId].value);
    }
    else if (array_tasks[currentTaskId].task_type == 1){
        Delete(array_tasks[currentTaskId].value);
        }
    else{
        Search(array_tasks[currentTaskId].value);
    }
    printf("%d task id", currentTaskId);
    currentTaskId++;
	//release the lock
	pthread_mutex_unlock(&awaketasklock);

	pthread_exit(NULL);
}
