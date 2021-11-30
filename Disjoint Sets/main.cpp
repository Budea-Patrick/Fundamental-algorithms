#include <bits/stdc++.h>
#include "Profiler.h"
#define TEST_SIZE 15
#define NR_OF_TESTS 5
#define N 10
#define STEP_SIZE 100
#define MAX_COST 1000
#define MAX_SIZE 10000
using namespace std;

Profiler p("prof");

int graph[MAX_SIZE][MAX_SIZE];
int comparisons, assignments;

struct node{
    int key;
    int rank;
    struct node *parent;
}*vertexArray[MAX_SIZE];

struct edge{
    struct node *source, *destination;
    int cost;
}edgeArray[4*MAX_SIZE];

struct node *newNode(int key)
{
    auto *aux=new node();
    aux->key=key;
    aux->parent=NULL;
    return aux;
}

void makeSet(struct node *x){
    x->parent=x;
    x->rank=0;
    assignments++;
}

void link(struct node *x, struct node *y){
    if(x->rank>y->rank){
        y->parent=x;
    }else{
        x->parent=y;
    }
    assignments++;
    if(x->rank==y->rank){
        y->rank=y->rank+1;
    }
    comparisons=comparisons+2;
}

struct node *findSet(struct node *x)
{
    if(x!=x->parent){
        x->parent= findSet(x->parent);
    }
    comparisons++;
    return x->parent;
}


void setUnion(struct node *x, struct node *y){
    link(findSet(x), findSet(y));
    assignments++;
}

void demoUnion()
{
    struct node *testArray[TEST_SIZE];
    for(int i=0;i<TEST_SIZE;i++){
        testArray[i]= newNode(i);
        makeSet(testArray[i]);
    }
    setUnion(testArray[0],testArray[1]);
    setUnion(testArray[2],testArray[10]);
    setUnion(testArray[4],testArray[2]);
    setUnion(testArray[3],testArray[9]);
    setUnion(testArray[3],testArray[8]);
    setUnion(testArray[3],testArray[11]);
    setUnion(testArray[14],testArray[1]);

    printf("Node %d is part of set represented by: %d\n",testArray[0]->key, findSet(testArray[0])->key);
    printf("Node %d is part of set represented by: %d\n",testArray[2]->key, findSet(testArray[2])->key);
    printf("Node %d is part of set represented by: %d\n",testArray[14]->key, findSet(testArray[14])->key);
    printf("Node %d is part of set represented by: %d\n",testArray[12]->key, findSet(testArray[12])->key);
    setUnion(testArray[0],testArray[3]);
    setUnion(testArray[4],testArray[14]);
    setUnion(testArray[3],testArray[12]);
    printf("Node %d is part of set represented by: %d\n",testArray[3]->key, findSet(testArray[3])->key);
    printf("Node %d is part of set represented by: %d\n",testArray[12]->key, findSet(testArray[12])->key);
    printf("Node %d is part of set represented by: %d\n",testArray[14]->key, findSet(testArray[14])->key);

}

void printGraph()
{
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void buildGraph(int size)
{
    for(int i=0;i<size;i++){
        vertexArray[i]= newNode(i);
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            graph[i][j]=-1;
        }
    }
    for(int i=0;i<size*4;i++){
        int source=rand()%size;
        int destination=rand()%size;
        while(graph[source][destination]!=-1 or graph[destination][source]!=-1 or source==destination){
            source=rand()%size;
            destination=rand()%size;
        }
        edgeArray[i].source=vertexArray[source];
        edgeArray[i].destination=vertexArray[destination];
        edgeArray[i].cost=rand()%MAX_COST+1;
        graph[source][destination]=graph[destination][source]=edgeArray[i].cost;
    }
    /*
    printGraph();
    printf("\n");*/
}

void sortEdges(int size)
{
    for(int i=0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(edgeArray[i].cost>edgeArray[j].cost){
                swap(edgeArray[i],edgeArray[j]);
            }
        }
    }
}

vector<edge> kruskal(int size)
{
    vector<edge>edges;
    for(int i=0;i<size;i++){
        makeSet(vertexArray[i]);
    }
    sortEdges(size*4);
    for(int i=0;i<size*4;i++){
        comparisons=comparisons+2;
        if(findSet(edgeArray[i].source)!=findSet(edgeArray[i].destination) and edgeArray[i].cost!=0){
            assignments++;
            edges.push_back(edgeArray[i]);
            setUnion(edgeArray[i].source,edgeArray[i].destination);
        }
    }
    return edges;
}

void kruskalPrint(int size)
{
    vector<edge>edges=kruskal(size);
    printf("The MST is:\n");
    for(int i=0;i<edges.size();i++){
        printf("%d - %d with the cost of %d\n",edges[i].source->key, edges[i].destination->key,edges[i].cost);
    }
}

void demoKruskal()
{
    buildGraph(N);
    kruskal(N);
    kruskalPrint(N);
}

void reset()
{
    for(int i=0;i<4*MAX_SIZE;i++){
        edgeArray[i].cost=0;
        edgeArray[i].destination=nullptr;
        edgeArray[i].source=nullptr;
    }
    comparisons=assignments=0;
}

void perfo()
{
    for(int i=0;i<NR_OF_TESTS;i++){
        for(int n=STEP_SIZE;n<MAX_SIZE;n=n+STEP_SIZE){
            buildGraph(n);
            kruskal(n);
            p.countOperation("Comparisons",n,comparisons);
            p.countOperation("Assignments",n,assignments);
            reset();
        }
        p.addSeries("Total", "Comparisons", "Assignments");
    }
    p.divideValues("Total",NR_OF_TESTS);
    p.showReport();
}

int main(int argc, char **argv)
{
    srand(rand()^ time(NULL));
    if(strcmp(argv[1],"union_demo")==0){
        demoUnion();
    }
    if(strcmp(argv[1],"kruskal_demo")==0){
        demoKruskal();
    }
    if(strcmp(argv[1],"perfo")==0){
        perfo();
    }
    return 0;
}