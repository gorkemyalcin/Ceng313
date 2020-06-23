#include<stdio.h>
#include"linkedList.h"

int main(){
   
    Node *newNode = createNode(5);
    Node *head = newNode;

    addNode(&head,1,3);

    printList(head);


}