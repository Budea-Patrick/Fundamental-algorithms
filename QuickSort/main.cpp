/*
 * QuickSort analysis
 * The worst case occurs when the partition always when the partition always chooses
 * the max or min element as pivot and the array is sorted. In this case the pivots are chosen in order
 * ex: array - 1 2 3 4 5 6 7 => pivots - 1 2 3... or 7 6 5... resulting in O(n^2) running time
 * This case is avoided by choosing random pivot and the probability of choosing a max or min pivot is low
 *
 * The best case occurs when the chosen pivot is the middle element at each recursion which results in a running time
 * of O(nlogn)
 *
 * The average case has a random characteristic since it is difficult to follow the way the pivots are chosen, but it
 * results in O(nlogn) running time
 *
 * QuickSort is not stable but a stable variant can be implemented
 *
 * With the graphs it is obvious that it is preferred over heapsort most of the time, except in the worst case
 * when quicksort is vastly inferior, but this case can be avoided with relative ease
 *
 * QuickSelect - worst case at most n+1 comp and n swaps => O(n^2)
 * Best case - the searched pivot is the first that is found => O(n) during first partitioning
 * Average case - closely related to probabilities but after computations we get O(n) running time
 *
 * */

#include <cstdio>
#include "Profiler.h"
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_OF_TESTS 5

Profiler p("prof");
int hsCount;


int partition(int v[], int n, int left, int right)
{
    int aux,pivot;
    pivot=v[right];
    ///qscount++;
    p.countOperation("QuickSort",n);
    int i=(left-1);
    for(int j=left;j<right;j++){
        p.countOperation("QuickSort",n);
        if(v[j]<pivot){ // change here to desc
            i++;
            ///qscount=qscount+3;
            p.countOperation("QuickSort",n,3);
            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
        }
    }
    ///qscount++;
    p.countOperation("QuickSort",n,3);
    aux=v[i+1];
    v[i+1]=v[right];
    v[right]=aux;
    return (i+1);
}

int randomPartition(int v[], int n, int left, int right)
{
    int aux;
    int pivot=rand()%(right-left+1);
    aux=v[left+pivot];
    v[left+pivot]=v[right];
    v[right]=aux;
    return partition(v,n,left,right);
}


void quickSort(int v[], int n, int left, int right)
{
    if(left<right){
        int partition_index= partition(v,n,left,right);
        quickSort(v,n,left,partition_index-1);
        quickSort(v,n,partition_index+1,right);
    }
}


int quickSelect(int v[],int n, int left, int right, int k)
{
    if(k>0 and k<=right-left+1){
        int i= randomPartition(v,n,left,right);
        if(i-left==k-1){
            return v[i];
        }
        if(i-left>k-1){
            return quickSelect(v,n,left,i-1,k);
        }
        return quickSelect(v,n,i+1,right,k-i+left-1);
    }
    return -1;
}



void maxHeapify(int v[], int n, int root)
{
    int left=root*2;
    int right=root*2+1;
    int maximum=root;
    hsCount++;
    ///p.countOperation("Bottom-up build",n);

    if(left<=n and v[maximum]<v[left]){
        maximum=left;
        ///hsCount++;
        ///p.countOperation("Bottom-up build",n);
    }
    hsCount++;
    if(right<=n and v[maximum]<v[right]){
        maximum=right;
        ///hsCount++;
       /// p.countOperation("Bottom-up build",n);
    }

    if(maximum!=root){
        int aux=v[root];
        v[root]=v[maximum];
        v[maximum]=aux;
        hsCount=hsCount+3;
       /// p.countOperation("Bottom-up build",n,3);
        maxHeapify(v, n, maximum);
    }
}



void bottomUp(int v[], int n)
{
    for(int i=n/2;i>=1;i--){
        maxHeapify(v,n,i);
    }
}


void heapSort(int v[], int n)
{
    for(int i=n;i>1;i--){
        hsCount=hsCount+3;
        int aux=v[1];
        v[1]=v[i];
        v[i]=aux;
        maxHeapify(v,i-1,1);
    }
}



void print(int v[], int n)
{
    for(int i=0;i<n;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}


void copyArray(int a[], int b[], int n)
{
    for(int i=1;i<=n;i++){
        b[i]=a[i];
    }
}

void profile()
{
    int v[MAX_SIZE],copy[MAX_SIZE];
    for(int i=1;i<=NR_OF_TESTS;i++){
        for(int n=STEP_SIZE;n<=MAX_SIZE;n=n+STEP_SIZE){
            FillRandomArray(v,n);
            copyArray(v,copy,n);
            quickSort(copy,n,0,n-1);
            ///p.countOperation("QuickSort",n,qscount);

            copyArray(v,copy,n);
            bottomUp(copy,n);
            heapSort(copy,n);
            p.countOperation("HeapSort",n,hsCount);
            hsCount=0;
        }
    }
    p.divideValues("QuickSort",NR_OF_TESTS);
    p.divideValues("HeapSort",NR_OF_TESTS);
    p.createGroup("Operations","HeapSort","QuickSort");
    p.showReport();
}

void worstCase()
{
    int v[MAX_SIZE],copy[MAX_SIZE];
    for(int n=STEP_SIZE;n<=MAX_SIZE;n=n+STEP_SIZE){
        FillRandomArray(v,n,1,MAX_SIZE,true,1);
        copyArray(v,copy,n);
        quickSort(copy,n,0,n-1);

        copyArray(v,copy,n);
        bottomUp(copy,n);
        heapSort(copy,n);
        p.countOperation("HeapSort",n,hsCount);
        hsCount=0;
    }
    p.createGroup("Operations","HeapSort","QuickSort");
    p.showReport();
}

void bestCaseQuickSort(int v[], int n, int left, int right)
{
    if(left<right){
        int pivot=(right-left)/2+left; // take pivot in middle
        int aux=v[pivot];
        v[pivot]=v[right];
        v[right]=aux;
        p.countOperation("QuickSort",n,3);
        int k= partition(v,n,left,right);
        bestCaseQuickSort(v,n,left,k-1);
        bestCaseQuickSort(v,n,k+1,right);
    }
}

void bestCase()
{
    int v[MAX_SIZE],copy[MAX_SIZE];
    for(int n=STEP_SIZE;n<=MAX_SIZE;n=n+STEP_SIZE) {
        FillRandomArray(v, n, 1, MAX_SIZE, true, 1);
        copyArray(v,copy,n);
        bestCaseQuickSort(v, n, 0, n - 1);

        copyArray(v,copy,n);
        bottomUp(copy,n);
        heapSort(copy,n);
        p.countOperation("HeapSort",n,hsCount);
        hsCount=0;
    }
    p.createGroup("Operations","HeapSort","QuickSort");
    p.showReport();
}

void demo()
{
    int v[] = {10, 4, 5, 8, 6, 11, 26, 20, 50, 69, 42};
    int n=sizeof(v)/ sizeof(int);
    int i=5;
    printf("Original array: ");
    print(v,n);
    printf("The %d-th smallest element is: %d\n",i, quickSelect(v,n,0,n-1,i));
    printf("Sorted array: ");
    quickSort(v,n,0,n-1);
    print(v,n);
}



int main(int argc, char **argv)
{
    if(strcmp(argv[1],"best")==0){
        bestCase();
    }
    if(strcmp(argv[1],"worst")==0){
        worstCase();
    }
    if(strcmp(argv[1],"demo")==0) {
        demo();
    }
    if(strcmp(argv[1],"profile")==0){
        profile();
    }
    return 0;
}