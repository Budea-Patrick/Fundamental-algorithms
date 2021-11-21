#include <bits/stdc++.h>
#define MAX_SIZE 9
#define INDENT 5
using namespace std;

int parents[]={2,7,5,2,7,7,-1,5,2};
struct mNode* nodes[MAX_SIZE];
int children[MAX_SIZE];

struct mNode{
    int key{};
    int childNumber{};
    vector<struct mNode*> children;
};

struct biNode{
    int key;
    struct biNode *left, *right;
};

struct mNode* newNode(int key)
{
    auto* aux=new (struct mNode);
    aux->key=key;
    aux->childNumber=0;
    return aux;
}
// This function has a runtime of O(n) because I traverse the parent array exactly once and make all the links after
// I allocate the space in the memory for the nodes.
struct mNode* toMultiway(int n)
{
    struct mNode*root;

    for(int i=0;i<n;i++){
        nodes[i]= newNode(i+1);
    }
    for(int i=0;i<n;i++){
        if(parents[i]!=-1){
            int aux=parents[i]-1;
            struct mNode* temp=nodes[i];
            nodes[aux]->children.push_back(temp);
            nodes[aux]->childNumber++;
        }
        else{
            root=nodes[i];
        }
    }
    return root;
}
// This function has a runtime of O(n) because during the recursive calls each node is visited once
// First deal with the children and then with the siblings
struct biNode* toBinary(struct biNode *root, int index, int parent)
{
    root=new(struct biNode);
    root->key=nodes[index-1]->key;
    if(parent!=-1){ // if it is not the root, increase the children of the parent
        children[parent-1]++;
    }
    if(nodes[index-1]->childNumber==0){ // if there are no children link null to the left
        root->left=nullptr;
    }
    else{
        root->left=toBinary(root,nodes[index-1]->children[0]->key, index); // call function on the child
    }
    if(parent==-1){ // if it is root, it has no siblings so null on the right
        root->right=nullptr;
    }
    else{
        if(nodes[parent-1]->childNumber>children[parent-1]){ // if there are still sibling which have not been dealt with
            int sibling=children[parent-1];
            root->right=toBinary(root,nodes[parent - 1]->children[sibling]->key, parent); // call function on the siblings
        }
        else{
            root->right = nullptr; // no more siblings so put null on the right
        }
    }
    return root;

}

void print(struct biNode *root, int height)
{
    if(root!=nullptr)
    {
        for(int i=0;i<INDENT*height;i++){
            printf(" ");
        }
        printf("%d\n",root->key);
        print(root->left,height+1);
        print(root->right,height);
    }
}

int main()
{
    struct mNode* root;
    root=toMultiway(MAX_SIZE);
    struct biNode* root2=nullptr;
    root2=toBinary(root2, root->key, parents[root->key-1]);
    print(root2, 0);
    return 0;
}