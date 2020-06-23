#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
   int data;
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//display the list
void printList() {
   struct node *ptr = head;
	
   while(ptr != NULL) {
      printf("(%d) ",ptr->data);
      ptr = ptr->next;
   }
	
}

//insert link at the first location
void insertFirst(int data) {

   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->data = data;
   link->next = head;
	
   head = link;
}

//delete first item
struct node* deleteFirst() {

   //save reference to first link
   struct node *tempLink = head;
	
   //mark next to first link as first 
   head = head->next;
	
   //return the deleted link
   return tempLink;
}

//is list empty
bool isEmpty() {
   return head == NULL;
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

//delete a link with given key
struct node* delete(int data) {

   struct node* current = head;
   struct node* previous = NULL;
	
   if(head == NULL) {
      return NULL;
   }

   while(current->data != data) {

      if(current->next == NULL) {
         return NULL;
      } 
      else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } 
   else {
      //bypass the current link
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
	
   for ( i = 0 ; i < size - 1 ; i++, k-- ) {
      current = head;
      next = head->next;
		
      for ( j = 1 ; j < k ; j++ ) {   

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

void main() {
   insertFirst(10);
   insertFirst(20);
   insertFirst(30);
   insertFirst(41);
   insertFirst(50);
   insertFirst(66); 

   printf("Original List: "); 
	
   //print list
   printList();

   while(!isEmpty()) {            
      struct node *temp = deleteFirst();
      printf("\nDeleted value:");
      printf("(%d)",temp->data);
   }  
	
   printf("\nList after deleting all items: ");
   printList();
   insertFirst(1);
   insertFirst(2);
   insertFirst(3);
   insertFirst(4);
   insertFirst(5);
   insertFirst(6);
   
   printf("\nRestored List: ");
   printList();
   printf("\n");  

   struct node *foundLink = find(4);
	
   if(foundLink != NULL) {
      printf("Element found: ");
      printf("(%d)",foundLink->data);
      printf("\n");  
   } else {
      printf("Element not found.");
   }

   delete(4);
   printf("List after deleting an item: ");
   printList();
   printf("\n");
   foundLink = find(4);
	
   if(foundLink != NULL) {
      printf("Element found: ");
      printf("(%d)",foundLink->data);
      printf("\n");
   } else {
      printf("Element not found.");
   }
	
   printf("\n");
   sort();
	
   printf("List after sorting the data: ");
   printList();
	
   reverse(&head);
   printf("\nList after reversing the data: ");
   printList();
}