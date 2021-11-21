/*
 * Comment countOps to graph the 2 algorithms with heap sort
 *
 * nr of leaves in full binary tree = (n+1)/2
 *
 * Bottom-up approach: maxHeapify has constant complexity O(1) but with the recursive calls we can say that it is being called
 * a mximum nr of logn=h => O(h). Building bottom up calls n/2 times which means the complexity becomes O(nlogn). There are not many nodes at height h so after
 * a few more calculations we get linear complexity O(n) since there are n/2^(h+1).
 *
 * HeapSort calls bottom up build (O(n)) and maxHeapify a number of n-1 times O(lg) => O(n+nlogn)=> O(nlogn)
 *
 * Top-down approach: each element can be bubbled up from the current bottom all the way to the top. When we want to insert a new element
 * the heap has a height of log(n-1) => with the nr of swaps we get a runtime of O(nlogn) in the worst case which happens
 * if the elements are inserted in asc order
 *
 * Comparison: top-down bubles up elements => sum of length of paths from each node to the root => O(nlogn)
 * bottom-up => length of the paths from each node to the leaves => O(n). Small heaps => more efficient regardless of input
 *
 * This conclusion can be seen in the attached graphs
 *
 *
 * Not Stable -> the first largest element is put to the end of the list, the second largest to the second last
 * ex: 1.1 1.2 -> 1.1 is picked first and put to the end and then 1.2 => 1.2 1.1 but also sorted
 *
*/

#include <cstdio>
#include <cstring>
#include "Profiler.h"

#define STEP_SIZE 100
#define MAX_SIZE 10000
#define NR_OF_TESTS 5
#define TEST_SIZE 15

Profiler p("prof");

int count;

void maxHeapify(int v[], int n, int root)
{
    int left=root*2;
    int right=root*2+1;
    int maximum=root;
    count++;
    p.countOperation("Bottom-up build",n);

    if(left<=n and v[maximum]<v[left]){
        maximum=left;
        count++;
        p.countOperation("Bottom-up build",n);
    }
    if(right<=n and v[maximum]<v[right]){
        maximum=right;
        count++;
        p.countOperation("Bottom-up build",n);
    }
    if(maximum!=root){
        int aux=v[root];
        v[root]=v[maximum];
        v[maximum]=aux;
        count=count+3;
        p.countOperation("Bottom-up build",n,3);
        maxHeapify(v, n, maximum);
    }
}


void push(int v[], int n, int heap_size)
{
    if(n==1){
        return;
    }
    p.countOperation("Top-down build",heap_size);
    if(v[n]>v[n/2]){
        int aux=v[n];
        v[n]=v[n/2];
        v[n/2]=aux;
        p.countOperation("Top-down build",heap_size,3);
        count=count+3;
        push(v,n/2,heap_size);
    }
    count++;
}

void topDown(int v[], int n)
{
    for(int i=1;i<=n;i++){
        ///p.countOperation("Top-down build",n);
        count++;
        push(v,i,n);
    }
}


void heapSort(int v[], int n)
{
    for(int i=n;i>1;i--){
        count=count+3;
        int aux=v[1];
        v[1]=v[i];
        v[i]=aux;
        maxHeapify(v,i-1,1);
    }
}

void bottomUp(int v[], int n)
{
    for(int i=n/2;i>=1;i--){
        maxHeapify(v,n,i);
    }
}


void print(int v[], int n)
{
    for(int i=1;i<=n;i++){
        printf("%d ",v[i]);
    }
    printf("\n\n");
}


void topDownDemo()
{
    int v[16];

    FillRandomArray(v,TEST_SIZE);
    printf("Array: ");
    print(v,10);

    printf("Heap: ");
    topDown(v,10);
    print(v,10);

    printf("Sorted array: ");
    heapSort(v,10);
    print(v,10);

}

void bottomUpDemo()
{
    int v[16];

    FillRandomArray(v,TEST_SIZE);
    printf("Array: ");
    print(v,10);

    printf("Heap: ");
    bottomUp(v,10);
    print(v,10);

    printf("Sorted array: ");
    heapSort(v,10);
    print(v,10);
}



void copyArray(int a[], int b[], int n)
{
    for(int i=1;i<=n;i++){
        b[i]=a[i];
    }
}

void profile()
{
    int v[MAX_SIZE];
    int copy[MAX_SIZE];
    for(int i=1; i<=NR_OF_TESTS; i++)
    {
        for(int n=STEP_SIZE;n<=MAX_SIZE;n=n+STEP_SIZE)
        {
            FillRandomArray(v,n);
            copyArray(v,copy,n);
            topDown(copy,n);
            ///heapSort(copy,n);
            ///p.countOperation("Top-down build with HS",n,count);
            count=0;

            copyArray(v,copy,n);
            bottomUp(copy,n);
            ///heapSort(copy,n);
            ///p.countOperation("Bottom-up build with HS",n,count);
            count=0;
        }
    }
    ///p.divideValues("Top-down build with HS",NR_OF_TESTS);
    ///p.divideValues("Bottom-up build with HS",NR_OF_TESTS);
    p.divideValues("Bottom-up build",NR_OF_TESTS);
    p.divideValues("Top-down build",NR_OF_TESTS);
    ///p.createGroup("Operations", "Top-down build with HS","Bottom-up build with HS");
    p.createGroup("Operations", "Top-down build","Bottom-up build");
    p.showReport();
}

int main(int argc, char **argv)
{
    /*
    int v[1000]={10, 5, 3, 2, 4 };
    int n=5;
    insertNode(v,n,15);
    print2(v,n);*/

    if(strcmp(argv[1],"bottom")==0){
        bottomUpDemo();
    }
    if(strcmp(argv[1],"top")==0){
        topDownDemo();
    }
    if(strcmp(argv[1],"profile")==0){
        profile();
    }
    return 0;
}