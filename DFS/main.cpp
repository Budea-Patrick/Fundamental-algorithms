/*
 * DFS - O(V+E)
 * can be used to determine the components - Tarjan O(V+E)
 * can also be used for topological sorting of an acyclic graph O(V+E)
 *
 * */


#include <bits/stdc++.h>
#include "Profiler.h"
#define MAX_SIZE 10000
using namespace std;

Profiler p("prof");

enum color{WHITE, GRAY, BLACK};

struct node{
    list<struct node*> adjacency;
    int key;
    int index;
    color color;
    int lowLink;
    bool onStack;
};

vector<node> graph;
stack<node> stackTarjan;
list<node> topologicalSort;
int index, nrOfComponents;
bool cycles;
int globalTime;
int operations;

struct node *newNode(int key)
{
    struct node *node=new struct node();
    node->key=key;
    return node;
}

void addEdge(struct node *source, struct node* destination)
{
    graph[source->key].adjacency.push_back(destination);
}

void createGraph(int size)
{
    for(int i=0;i<size;i++){
        graph.push_back(*newNode(i));
    }
}

void dfsVisit(struct node *node)
{
    globalTime++;
    node->color=GRAY;
    operations++;
    printf("%d ",node->key);
    for(auto i=node->adjacency.begin();i!=node->adjacency.end();i++){
        if((*i)->color==GRAY){
            cycles=true;
        }
        operations++;
        if((*i)->color==WHITE){
            dfsVisit(*i);
        }
    }
    operations++;
    node->color=BLACK;
    globalTime++;
    topologicalSort.push_front(*node);
}

void dfs()
{
    for(int i=0;i<graph.size();i++){
        operations++;
        graph[i].color=WHITE;
    }
    globalTime=0;
    for(int i=0;i<graph.size();i++){
        operations++;
        if(graph[i].color==WHITE){
            printf("\n");
            dfsVisit(&graph[i]);
        }
    }
}

void strongConnect(struct node *node)
{
    node->index=node->lowLink=index;
    index++;
    stackTarjan.push(*node);
    node->onStack=true;
    for(auto i=node->adjacency.begin();i!=node->adjacency.end();++i){
        if((*i)->index==-1){
            strongConnect(*i);
            node->lowLink=min(node->lowLink,(*i)->lowLink);
        }else{
            if((*i)->onStack){
                node->lowLink=min(node->lowLink,(*i)->index);
            }
        }
    }
    struct node *aux;
    if(node->lowLink==node->index){
        nrOfComponents++;
        while(!stackTarjan.empty()){
            aux=&stackTarjan.top();
            printf("%d ",aux->key);
            stackTarjan.pop();
            aux->onStack=false;
        }
    }
}

void tarjan()
{
    for(int i=0;i<graph.size();i++){
        graph[i].index=graph[i].lowLink=-1;
        graph[i].onStack=false;
    }
    for(int i=0;i<graph.size();i++){
        if(graph[i].index==-1){
            stackTarjan=stack<node>();
            strongConnect(&graph[i]);
            printf("\n");
        }
    }
}

void printList()
{
    for(auto i=topologicalSort.begin();i!=topologicalSort.end();i++){
        printf("%d ", (*i).key);
    }
}

bool checkIfAdjacent(struct node *source, struct node *destination)
{
    for(auto i=source->adjacency.begin();i!=source->adjacency.end();i++){
        if((*i)==destination){
            return true;
        }
    }
    return false;
}

void demo()
{
    createGraph(6);

    addEdge(&graph[0],&graph[1]);
    addEdge(&graph[0],&graph[3]);
    addEdge(&graph[1],&graph[2]);
    addEdge(&graph[2],&graph[3]);
    addEdge(&graph[3],&graph[1]);
    addEdge(&graph[4],&graph[3]);
    addEdge(&graph[4],&graph[5]);
    addEdge(&graph[5],&graph[5]);
    printf("DFS algorithm:");
    dfs();
    printf("\nTarjan algorithm:\n");
    tarjan();
    /*
    if(!cycles){
        printf("\nTarjan algorithm:\n");
        tarjan();
    }else{
        printf("\nGraph has cycles\n");
        return;
    }
    printf("\nTopological sort:\n");
    printList();
    printf("\n");*/
}

void reset()
{
    for(auto i=graph.begin();i!=graph.end();i++){
        i->adjacency=list<struct node*>();
    }
    graph=vector<node>();
    operations=0;
}


void perf()
{
    int v=100;
    for(int n=1000;n<=5000;n=n+100){
        createGraph(v);
        for(int i=0;i<n;i++){
            int source=rand()%v;
            int destination=rand()%v;
            while(checkIfAdjacent(&graph[source], &graph[destination])){
                source=rand()%v;
                destination=rand()%v;
            }
            addEdge(&graph[source],&graph[destination]);
        }
        dfs();
        p.countOperation("DFS Operations fixed V",n,operations);
        printf("\n");
        reset();
    }
    int e=9000;
    for(int n=100;n<=200;n=n+10){
        createGraph(n);
        for(int i=0;i<e;i++){
            int source=rand()%n;
            int destination=rand()%n;
            while(checkIfAdjacent(&graph[source], &graph[destination])){
                source=rand()%v;
                destination=rand()%v;
            }
            addEdge(&graph[source],&graph[destination]);
        }
        dfs();
        p.countOperation("DFS Operations fixed E",n,operations);
        printf("\n");
        reset();
    }
    p.showReport();
}


int main()
{
    srand(rand()^ time(NULL));
    demo();
    //perf();
    return 0;
}
