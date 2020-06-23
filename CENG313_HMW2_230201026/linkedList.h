#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    struct node *link;
};

typedef struct node Node;

Node* createNode(int value); //Create and return a node with the given value
int isEmpty(Node *head); //checks if there is an element in the list or not
void addNode(Node **head, int index, int value); //Add given node to the given index
Node deleteNode(Node **head, int value); //Delete first Node where given value occurrs
int getSize(Node *head); //Return size of the list
void printList(Node *head); //print the values of each node in the list
int getFrequency(Node *head, int value); //Return number of occurrences of a value in nodes