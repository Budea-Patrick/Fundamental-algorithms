/* Use command line arguments to select the case of the sorted array
 * average=average case, best=best case, worst=worst case, demo=small array
 * The output when demo is selected will be printed in demo.txt
 *
 * Average Case
 *     In the average case the least assignments are made using SelectionSort which by analyzing the code we can calculate the nr of assignments and we get 3(n-1) assignments => O(n)
 *     The total nr of comparisons is n-1+n-2+n-3+...+2+1=n(n-1)/2 => O(n^2) hence the total nr of operations is n^2/2+5n/2-3 =? On(n^2)
 *
 *     For InsertionSort we need n-1 comparisons and n-1 assignments at most to insert last element. For the second to last n-2 comparisons and n-2 assignments. The total number of operations
 *     is 2*(1+2+...n-2+n-1) => n(n-1) using master theorem. This results in O(n^2) complexity.
 *
 *     Using BubbleSort for each element of the array we require n-1 comparisons and there are n elements => The total number of comparisons is O(n^2). The nr of swaps is also of O(n^2).
 *
 *     So, using the profiler to chart the graphs we conclude that in the average case BubbleSort has the most number of operations, while the other are comparable.
 *
 *
 *  Worst Case
 *     The worst case is for all 3 sorting algorithms when th array is sorted in descending order. In this case each element of the array is compared to all the other ones.
 *     Still SelectionSort has the least number of assignments (O(n)) while all 3 algorithms have roughly the same number of comparisons. Essentially the chart shows that SelectionSort is
 *     efficient but all 3 algorithms have O(n^2) complexity in the worst case.
 *
 *  Best Case
 *      The worst case is for all 3 sorting algorithms when th array is already sorted. This time BubbleSort and SelectionSort have O(1) time complexity regarding the nr of assignments,
 *      both being 0 since no new assignment is needed. InsertionSort has O(n) nr of assignments since we always assign aux=v[i] in the for loop. The nr of comparisons are also different
 *      InsertionSort has linear complexity when it comes to InsertionSort O(n) while the others have quadratic complexities O(n^2).
 *
 *  Stability
 *      BubbleSort and InsertionSort are considered stable, while SelectionSort is not stable, although stable variants do exist.
 *
 *
 *  Conclusion
 *      Using the analysis we can conclude that BubbleSort is not preferable most of the times. InsertionSort is fairly quick in certain cases ex when the array is almost sorted on small
 *      collections. SelectionSort is also preferred on small sets. Of course if stability is a must then InsertionSort is a good choice.
 *
 * */



#include <cstdio>
#include <cstring>
#include "Profiler.h"
#define MAX_SIZE 10000
#define STEP_SIZE 100


Profiler p("prof");


void copyVector(int v[], int copy[], int n)
{
    for(int i=0;i<n;i++){
        copy[i]=v[i];
    }
}


void BubbleSort(int v[], int n)
{
    Operation opComp = p.createOperation("Bubble Sort Comparisons", n);
    Operation opAttr = p.createOperation("Bubble Sort Assignments", n);
    int aux;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            opComp.count();
            if(v[i]>v[j]){
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
                opAttr.count(3);
            }
        }
    }
}

void InsertionSort(int v[], int n)
{
    Operation opComp = p.createOperation("Insertion Sort Comparisons", n);
    Operation opAttr = p.createOperation("Insertion Sort Assignments", n);
    int aux;
    for(int i=1;i<n;i++){
        opAttr.count();
        aux=v[i];
        int j=i-1;
        while(j>=0 and v[j]>aux){
            opComp.count();
            v[j+1]=v[j];
            opAttr.count();
            j--;
        }
        if(j!=0){
            opComp.count();
        }
        v[j+1]=aux;
        opAttr.count();
    }
}

void SelectionSort(int v[], int n)
{
    Operation opComp = p.createOperation("Selection Sort Comparisons", n);
    Operation opAttr = p.createOperation("Selection Sort Assignments", n);
    int index;
    for(int i=0;i<n-1;i++){
        index=i;
        for(int j=i+1;j<n;j++){
            opComp.count();
            if(v[j]<v[index]){
                index=j;
            }
        }
        if(i!=index){
            int aux=v[i];
            v[i]=v[index];
            v[index]=aux;
            opAttr.count(3);
        }
    }
}


void print(FILE *out, int v[], int n)
{
    for(int i=0;i<n;i++){
        fprintf(out, "%d ", v[i]);
    }
    fprintf(out, "\n");
}


/*void cases(FILE *best, FILE *worst, FILE *average)
{
    int v[MAX_SIZE];
    for (int n = 100; n <= 10000; n = n + STEP_SIZE) {// best

        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        print(best, v, n);
        BubbleSort(v, n);
        print(best, v, n);
        fprintf(best, "\n");
        p.showReport();

        //p.reset();

        for (int i = n - 1; i >= 0; i--) { // worst
            v[n - i - 1] = i;
        }
        print(worst, v, n);
        BubbleSort(v, n);
        print(worst, v, n);
        fprintf(worst, "\n");
        p.showReport();
        //p.reset();

        if(counter<=5){
            FillRandomArray(v, n);
            print(average, v, n);
            BubbleSort(v, n);
            print(average, v, n);
            fprintf(average, "\n");
            counter++;
            p.showReport();
            //p.reset();
        }
    }
        //p.reset();
    }
}*/


void worstCase()
{
    int v[MAX_SIZE];
    int copy[MAX_SIZE];
    for (int n = 100; n <= 10000; n = n + STEP_SIZE) {
        for (int i = n - 1; i >= 0; i--) { // worst
            v[n - i - 1] = i;
        }
        copyVector(v, copy, n);
        BubbleSort(copy, n);
        p.addSeries("Total Operations BubbleSort", "Bubble Sort Assignments", "Bubble Sort Comparisons");

        copyVector(v, copy, n);
        InsertionSort(copy, n);
        p.addSeries("Total Operations InsertionSort", "Insertion Sort Assignments", "Insertion Sort Comparisons");

        copyVector(v, copy, n);
        SelectionSort(copy, n);
        p.addSeries("Total Operations SelectionSort", "Selection Sort Assignments", "Selection Sort Comparisons");
    }

    p.createGroup("Assignments","Bubble Sort Assignments", "Insertion Sort Assignments", "Selection Sort Assignments");
    p.createGroup("Comparisons","Bubble Sort Comparisons", "Insertion Sort Comparisons", "Selection Sort Comparisons");
    p.createGroup("Total Operations","Total Operations BubbleSort", "Total Operations InsertionSort", "Total Operations SelectionSort");
    p.showReport();
}

void bestCase()
{
    int v[MAX_SIZE];
    int copy[MAX_SIZE];
    for (int n = 100; n <= 10000; n = n + STEP_SIZE){
        for (int i = 0; i < n; i++) {
            v[i] = i;
        }
        copyVector(v,copy,n);
        BubbleSort(copy, n);
        p.addSeries("Total Operations BubbleSort", "Bubble Sort Assignments", "Bubble Sort Comparisons");

        copyVector(v,copy,n);
        InsertionSort(copy,n);
        p.addSeries("Total Operations InsertionSort", "Insertion Sort Assignments", "Insertion Sort Comparisons");

        copyVector(v,copy,n);
        SelectionSort(copy,n);
        p.addSeries("Total Operations SelectionSort", "Selection Sort Assignments", "Selection Sort Comparisons");

    }
    p.createGroup("Assignments","Bubble Sort Assignments", "Insertion Sort Assignments", "Selection Sort Assignments");
    p.createGroup("Comparisons","Bubble Sort Comparisons", "Insertion Sort Comparisons", "Selection Sort Comparisons");
    p.createGroup("Total Operations","Total Operations BubbleSort", "Total Operations InsertionSort", "Total Operations SelectionSort");
    p.showReport();
}

/*void averageCaseSmallerSize()
{
    int v[MAX_SIZE];
    int counter = 0;
    int copy[MAX_SIZE];
    for(int i=0;i<5;i++){

    }
    for (int n = 100; n <= 10000; n = n + STEP_SIZE){
        if(counter<=5){
            FillRandomArray(v, n);
            copyVector(v,copy,n);
            BubbleSort(copy, n);
            p.addSeries("Total Operations BubbleSort", "Bubble Sort Assignments", "Bubble Sort Comparisons");

            copyVector(v,copy,n);
            InsertionSort(copy,n);
            p.addSeries("Total Operations InsertionSort", "Insertion Sort Assignments", "Insertion Sort Comparisons");

            copyVector(v,copy,n);
            SelectionSort(copy,n);
            p.addSeries("Total Operations SelectionSort", "Selection Sort Assignments", "Selection Sort Comparisons");


            p.createGroup("Assignments","Bubble Sort Assignments", "Insertion Sort Assignments", "Selection Sort Assignments");
            p.createGroup("Comparisons","Bubble Sort Comparisons", "Insertion Sort Comparisons", "Selection Sort Comparisons");
            p.createGroup("Total Operations","Total Operations BubbleSort", "Total Operations InsertionSort", "Total Operations SelectionSort");

            counter++;
            p.showReport();
            //p.reset();
        }
    }
}*/


void averageCase()
{
    int v[MAX_SIZE];
    int copy[MAX_SIZE];
    for(int i=0;i<5;i++){
        for (int n = 100; n <= 10000; n = n + STEP_SIZE) {
            FillRandomArray(v, n,0, 1000);
            copyVector(v, copy, n);
            BubbleSort(copy, n);
            p.addSeries("Total Operations BubbleSort", "Bubble Sort Assignments", "Bubble Sort Comparisons");

            copyVector(v, copy, n);
            InsertionSort(copy, n);
            p.addSeries("Total Operations InsertionSort", "Insertion Sort Assignments", "Insertion Sort Comparisons");

            copyVector(v, copy, n);
            SelectionSort(copy, n);
            p.addSeries("Total Operations SelectionSort", "Selection Sort Assignments", "Selection Sort Comparisons");
            //p.reset();
        }

    }
    p.divideValues("Total Operations BubbleSort",5);
    p.divideValues("Total Operations InsertionSort",5);
    p.divideValues("Total Operations SelectionSort",5);

    p.createGroup("Assignments", "Bubble Sort Assignments", "Insertion Sort Assignments",
                  "Selection Sort Assignments");
    p.createGroup("Comparisons", "Bubble Sort Comparisons", "Insertion Sort Comparisons",
                  "Selection Sort Comparisons");
    p.createGroup("Total Operations", "Total Operations BubbleSort", "Total Operations InsertionSort",
                  "Total Operations SelectionSort");
    p.showReport();
}


void demo(FILE *out)
{
    int v[]={1, 5, 8, 9, 6, 7, 3, 4, 2, 0};
    int n=sizeof(v)/sizeof(v[0]);
    ///BubbleSort(v,n);
    ///InsertionSort(v,n);
    SelectionSort(v,n);
    print(out,v,n);
}


int main(int argc, char **argv)  // use command arguments to select which case is computed
{
    FILE *ex=fopen("demo.txt","w");

    if(strcmp(argv[1],"best")==0){
        bestCase();
    }
    if(strcmp(argv[1],"worst")==0){
        worstCase();
    }
    if(strcmp(argv[1],"average")==0){
        averageCase();
    }
    if(strcmp(argv[1],"demo")==0){
        demo(ex);
    }

    fclose(ex);

    return 0;
}
