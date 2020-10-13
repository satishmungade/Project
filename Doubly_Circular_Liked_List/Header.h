#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
struct Node
{
	struct Node *pPrev; 
    int iData;
	struct Node *pNext;
};
typedef struct Node NODE;
typedef struct Node* PNODE;
typedef struct Node** PPNODE;

void insert_first(PPNODE,PPNODE,int);
void insert_last(PPNODE,PPNODE,int);
void insert_at_position(PPNODE,PPNODE,int,int);
int delete_first(PPNODE,PPNODE);
int delete_last(PPNODE,PPNODE);
int delete_at_position(PPNODE,PPNODE,int);
int count_node(PNODE,PNODE);
int search_all(PNODE,PNODE,int);
int search_first_occurrence(PNODE,PNODE,int);
int search_last_occurrence(PNODE,PNODE,int);
void concat_list(PPNODE,PPNODE,PPNODE,PPNODE);
void concat_at_position(PPNODE,PPNODE,PPNODE ,PPNODE,int);
void reverse_display(PNODE,PNODE);
void reverse(PPNODE,PPNODE);
void display (PNODE,PNODE);