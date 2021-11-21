/*
 * Time complexity nlogk
 *
 * The push and pop operations will be applied to all n nodes of the lists
 * The push and pop operations in a min-heap require log k time
 * => O(nlogk) runtime
 *
 * Create min-heap implemented as a priority queue with all the first elements of the linked lists
 * Remove top element (current min) add it to the result list
 * If an element exists next to the popped element in the previous step push into min-heap
 * Do this as long as the queue is not empty
 *
 * */

#include <cstdio>
#include <bits/stdc++.h>
#include "Profiler.h"

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_OF_TEST 5

Profiler p("prof");

int ass;
int comps;


using namespace std;

struct node{
    int key;
    struct node *next;
};


int arrSize;



struct node* newNode(int key)
{
    auto *new_node=new node();
    new_node->key=key;
    new_node->next=NULL;
    return new_node;
}


struct node *top(struct node*arr[])
{
    return arr[arrSize-1];
}

bool isEmpty()
{
    return arrSize==0;
}

void push(struct node*arr[], struct node *node)
{
    comps++;
    if(arrSize==0){
        ass++;
        arr[arrSize++]=node;
    }else{
        int i;
        for(i=arrSize-1;i>=0;i--){
            comps++;
            if(node->key>arr[i]->key){
                ass++;
                arr[i+1]=arr[i];
            }
            else{
                break;
            }
        }
        ass++;
        arr[i+1]=node;
        arrSize++;
    }
}

void pop()
{
    arrSize--;
}



struct node *merge(struct node *v[], int k)
{
    struct node *queue[MAX_SIZE]={NULL};
    for(int i=0;i<k;i++){
        comps++;
        if(v[i]!=NULL){
            push(queue,v[i]);
        }
    }
    if(isEmpty()){
        return NULL;
    }
    struct node *aux= newNode(0);
    ass++;
    struct node *last=aux;
    while(!isEmpty()){
        struct node *traverse=top(queue);
        pop();
        last->next=traverse;
        last=last->next;
        ass=ass+3;
        comps++;
        if(traverse->next!=NULL){
            push(queue, traverse->next);
        }
    }
    return aux->next;
}


void addAtEnd(struct node **head, int newKey)
{
    struct node *new_node=new node();
    struct node *aux=*head;
    new_node->key=newKey;
    new_node->next=NULL;
    if(*head==NULL){
        *head=new_node;
        return;
    }
    while(aux->next!=NULL){
        aux=aux->next;
    }
    aux->next=new_node;
    return;
}



void print(struct node *node)
{
    while(node!=NULL){
        printf("%d ",node->key);
        node=node->next;
    }
    printf("\n");
}


struct node *arrayToList(int v[], int n)
{
    struct node *root=NULL;
    for(int i=0;i<n;i++){
        addAtEnd(&root,v[i]);
    }
    return root;
}

void demo(int k, int n)
{

    int size=n/k;
    int v[size];
    int maxes[size];
    int remainder=n%k;
    struct node *list[5]={NULL};
    for(int i=0;i<k;i++){
        FillRandomArray(v,size,0,10000,true,1);
        list[i]= arrayToList(v,size);
        maxes[i]=v[size-1];
    }
    for(int i=0;i<remainder;i++){
        int aux=rand()%(INT_MAX-maxes[i]+1)+maxes[i];
        addAtEnd(&list[i],aux);
    }
    for(int i=0;i<k;i++){
        printf("Array nr %d: ",i+1);
        print(list[i]);
    }
    struct node *result=merge(list,k);
    printf("Merged array: ");
    print(result);
}


void perfo1()
{
    int k=5;
    int v[MAX_SIZE];
    for(int test=0;test<NR_OF_TEST;test++){
        for(int n=STEP_SIZE;n<=MAX_SIZE;n=n+STEP_SIZE){
            int maxes[MAX_SIZE];
            int remainder=n%k;
            struct node *list[MAX_SIZE]={NULL};
            for(int i=0;i<k;i++){
                FillRandomArray(v,n/k,0,10000,true,1);
                list[i]= arrayToList(v,n/k);
                maxes[i]=v[n/k-1];
            }
            for(int i=0;i<remainder;i++){
                int aux=rand()%(INT_MAX-maxes[i]+1)+maxes[i];
                addAtEnd(&list[i],aux);
            }
            merge(list,k);
            p.countOperation("Assignments1",n, ass);
            p.countOperation("Comparisons1",n, comps);
            ass=0;
            comps=0;
        }
    }
    p.divideValues("Assignments1",NR_OF_TEST);
    p.divideValues("Comparisons1",NR_OF_TEST);
    p.addSeries("Operations1","Assignments1","Comparisons1");

    k=10;
    for(int test=0;test<NR_OF_TEST;test++){
        for(int n=STEP_SIZE;n<=MAX_SIZE;n=n+STEP_SIZE){
            int maxes[MAX_SIZE];
            int remainder=n%k;
            struct node *list[MAX_SIZE]={NULL};
            for(int i=0;i<k;i++){
                FillRandomArray(v,n/k,0,10000,true,1);
                list[i]= arrayToList(v,n/k);
            }
            for(int i=0;i<remainder;i++){
                int aux=rand()%(INT_MAX-maxes[i]+1)+maxes[i];
                addAtEnd(&list[i],aux);
            }
            merge(list,k);
            p.countOperation("Assignments2",n, ass);
            p.countOperation("Comparisons2",n, comps);
            ass=0;
            comps=0;
        }
    }
    p.divideValues("Assignments2",NR_OF_TEST);
    p.divideValues("Comparisons2",NR_OF_TEST);
    p.addSeries("Operations2","Assignments2","Comparisons2");

    k=100;
    for(int test=0;test<NR_OF_TEST;test++){
        for(int n=STEP_SIZE;n<=MAX_SIZE;n=n+STEP_SIZE){
            int maxes[MAX_SIZE];
            int remainder=n%k;
            struct node *list[MAX_SIZE]={NULL};
            for(int i=0;i<k;i++){
                FillRandomArray(v,n/k,0,10000,true,1);
                list[i]= arrayToList(v,n/k);
            }
            for(int i=0;i<remainder;i++){
                int aux=rand()%(INT_MAX-maxes[i]+1)+maxes[i];
                addAtEnd(&list[i],aux);
            }
            merge(list,k);
            p.countOperation("Assignments3",n, ass);
            p.countOperation("Comparisons3",n, comps);
            ass=0;
            comps=0;
        }
    }
    p.divideValues("Assignments3",NR_OF_TEST);
    p.divideValues("Comparisons3",NR_OF_TEST);
    p.addSeries("Operations3","Assignments3","Comparisons3");

    p.createGroup("Total","Operations1","Operations2","Operations3");
    p.showReport();
}


void perfo2()
{
    int v[MAX_SIZE];

    int n=10000;
    for(int test=0;test<NR_OF_TEST;test++){
        for(int k=10;k<=500;k=k+10){
            struct node *list[MAX_SIZE]={NULL};
            for(int i=0;i<k;i++){
                FillRandomArray(v,n/k,0,10000,true,1);
                list[i]= arrayToList(v,n/k);
            }
            merge(list,k);
            p.countOperation("Assignments",k,ass);
            p.countOperation("Comparisons",k,comps);
            ass=0;
            comps=0;
        }
    }
    p.divideValues("Assignments",NR_OF_TEST);
    p.divideValues("Comparisons",NR_OF_TEST);
    p.addSeries("Operations", "Assignments", "Comparisons");
    p.showReport();
}



int main(int argc, char **argv)
{

    if(strcmp(argv[1],"demo")==0){
        demo(4,19);
        return 0;
    }
    if(strcmp(argv[1],"perfo1")==0){
        perfo1();
        return 0;
    }
    if(strcmp(argv[1],"perfo2")==0){
        perfo2();
        return 0;
    }
}