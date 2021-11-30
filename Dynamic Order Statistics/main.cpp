/*
 * Building the tree requires O(logn) time for each new element => nlogn
 * To maintain the RB tree property we call the auxiliary procedure to recolour nodes apply rotations when necessary
 * These operations require at worst O(logn) time but on average it is being done in constant time.
 *
 * The selection operation is done in O(logn) time and is proportional to the height of the tree
 *
 * The deletion is a bst tree delete function which has a runtime of O(logn)
 *
 * The tree structure is an augmented one because the size of the subtrees is also included in the information of each node
 * This is the information which makes the select operation an efficient one
 *
 * Updating the size information does not increase the time complexity of the functions because the sizes are modified dynamically during
 * the other operations like insert and delete.
 *
 * The tree is a self-balancing one which means the height of the tree is kept under control during the operations, but this aspect requires additional operations
 *
 * RB tree properties: every node is either black or red, the root is black, no adjacent red nodes, every path from a node to any NIL nodes has the same number of black nodes
 *
 * */


#include <bits/stdc++.h>
#include "Profiler.h"
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define DEMO_SIZE 11
#define INDENT 3
#define NR_OF_TESTS 5
using namespace std;

Profiler p("prof");

enum COLOUR {
    Red, Black
};
bool visited[MAX_SIZE];

int insertComparisons, insertAssignments;
int selectComparisons, selectAssignments;
int deleteComparisons, deleteAssignments;

typedef struct node {
    int key;
    enum COLOUR colour;
    struct node *parent, *right, *left;
    int size;
} node;

typedef struct rbTree {
    node *root;
    node *NIL;
} rbTree;


node *newNode(rbTree *tree, int key) {
    node *aux = new node();
    aux->left = tree->NIL;
    aux->right = tree->NIL;
    aux->parent = tree->NIL;
    aux->key = key;
    aux->size = 1;
    aux->colour = Red;
    return aux;
}

rbTree *newTree() {
    auto *tree = new rbTree();
    node *aux = new node();
    aux->left = nullptr;
    aux->right = nullptr;
    aux->parent = nullptr;
    aux->colour = Black;
    aux->key = 0;
    aux->size = 0;
    tree->NIL = aux;
    tree->root = tree->NIL;
    return tree;
}

void leftRotate(rbTree *tree, node *x) {

    node *y = x->right;
    insertAssignments++;
    int aux = y->size;
    y->size = x->size;
    x->size = x->size - aux + y->left->size;
    x->right = y->left;
    insertComparisons++;
    if (y->left != tree->NIL) {
        y->left->parent = x;
        insertAssignments++;
    }
    insertAssignments++;
    y->parent = x->parent;
    insertComparisons++;
    if (x->parent == tree->NIL) {
        tree->root = y;
        insertAssignments++;
    } else if (x == x->parent->left) {
        x->parent->left = y;
        insertAssignments++;
    } else {
        x->parent->right = y;
        insertAssignments++;
    }
    y->left = x;
    x->parent = y;
    insertAssignments++;

}

void rightRotate(rbTree *tree, node *x) {
    node *y = x->left;
    insertAssignments++;
    int aux = y->size;
    y->size = x->size;
    x->size = x->size - aux + y->right->size;
    x->left = y->right;
    insertComparisons++;
    if (y->right != tree->NIL) {
        y->right->parent = x;
        insertAssignments++;
    }

    y->parent = x->parent;
    insertComparisons++;
    if (x->parent == tree->NIL) {
        tree->root = y;
        insertAssignments++;
    } else {
        insertComparisons++;
        if (x == x->parent->right) {
            x->parent->right = y;
            insertAssignments++;
        } else {
            x->parent->left = y;
            insertAssignments++;
        }
    }
    y->right = x;
    insertAssignments++;
    x->parent = y;
}

void insertionFixUp(rbTree *tree, node *z) {
    while (z->parent->colour == Red) {
        insertComparisons++;
        if (z->parent == z->parent->parent->left) {
            node *uncle = z->parent->parent->right;
            insertComparisons++;
            if (uncle->colour == Red) {
                z->parent->colour = Black;
                uncle->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else {
                insertComparisons++;
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->colour = Black;
                z->parent->parent->colour = Red;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            node *uncle = z->parent->parent->left;
            insertComparisons++;
            if (uncle->colour == Red) {
                z->parent->colour = Black;
                uncle->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else {
                insertComparisons++;
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->colour = Black;
                z->parent->parent->colour = Red;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->colour = Black;
}

void insert(rbTree *tree, node *z) {
    node *parent = tree->NIL;
    node *temp = tree->root;
    while (temp != tree->NIL) {
        insertComparisons++;
        parent = temp;
        parent->size++;
        insertComparisons++;
        if (z->key < temp->key){
            temp = temp->left;
            insertAssignments++;
        }
        else{
            temp = temp->right;
            insertAssignments++;
        }
    }
    z->parent = parent;
    insertComparisons++;
    if (parent == tree->NIL) {
        insertAssignments++;
        tree->root = z;
    } else {
        insertComparisons++;
        if (z->key < parent->key){
            parent->left = z;
        }
        else{
            parent->right = z;
            insertAssignments++;
        }
    }
    z->right = tree->NIL;
    z->left = tree->NIL;
    insertionFixUp(tree, z);
}

node *osSelect(node *root, int i) {
    int aux = root->left->size + 1;
    selectComparisons++;
    if (i == aux) {
        return root;
    } else {
        selectComparisons++;
        if (i < aux) {
            return osSelect(root->left, i);
        } else {
            return osSelect(root->right, i - aux);
        }
    }
}

node *minimum(rbTree *tree, node *x) {
    while (x->left != tree->NIL) {
        x = x->left;
    }
    return x;
}

struct node *deleteNode(rbTree *tree, node *root, int key){
    deleteComparisons++;
    if (root == nullptr)
        return root;
    deleteComparisons++;
    if (key < root->key) {
        root->size--;
        root->left = deleteNode(tree, root->left, key);
    }
    else {
        deleteComparisons++;
        if (key > root->key) {
            root->size--;
            root->right = deleteNode(tree, root->right, key);
        } else {
            deleteComparisons++;
            if (root->left == tree->NIL and root->right == tree->NIL)
                return tree->NIL;
            else {
                deleteComparisons++;
                if (root->left == tree->NIL) {
                    struct node *temp = root->right;
                    deleteAssignments++;
                    free(root);
                    return temp;
                } else {
                    deleteComparisons++;
                    if (root->right == tree->NIL) {
                        struct node *temp = root->left;
                        deleteAssignments++;
                        free(root);
                        return temp;
                    }
                }
            }
            struct node *temp = minimum(tree, root->right);

            temp->size = root->size--;
            root->key = temp->key;

            root->right = deleteNode(tree, root->right, temp->key);
        }
    }
    return root;
}

void printSizes(rbTree *tree, node *z) {
    if (z != tree->NIL and z != nullptr) {
        printf("Node %d has a size of: %d\n", z->key, z->size);
        printSizes(tree, z->left);
        printSizes(tree, z->right);
    }
}


rbTree *buildTree(int n) {
    rbTree *tree = newTree();
    for (int i = 1; i <= n; i++) {
        insert(tree, newNode(tree, i));
    }
    return tree;
}

void reset() {
    for (int i = 1; i < MAX_SIZE; i++) {
        visited[i] = false;
    }
    insertComparisons=0;
    insertAssignments=0;

    selectComparisons=0;
    selectAssignments=0;

    deleteComparisons=0;
    deleteAssignments=0;
}

bool checkVisited() {
    for (int i = 1; i < MAX_SIZE; i++) {
        if (!visited[i]) {
            return true;
        }
    }
    return false;
}


int randomNumberInterval(int n) {
    int aux = rand() % n + 1;
    while (visited[aux] and !checkVisited()) {
        aux = rand() % n + 1;
    }
    visited[aux] = true;
    return aux;
}


void print(rbTree *tree, node *root, int height) {
    if (root != tree->NIL) {
        for (int i = 0; i < INDENT * height; i++) {
            printf(" ");
        }
        printf("%d\n", root->key);
        print(tree, root->left, height + 1);
        print(tree, root->right, height + 1);
    }
}

void demo() {
    printf("\n");
    rbTree *tree = buildTree(DEMO_SIZE);
    print(tree, tree->root, 0);
    printf("\n");
    printSizes(tree, tree->root);
    printf("\n");
    for (int i = 0; i < 3; i++) {
        int temp = randomNumberInterval(DEMO_SIZE - i);
        node *aux = osSelect(tree->root, temp);
        printf("%d-th smallest element is: %d\n", temp, aux->key);
        printf("Deleted node: %d\n", aux->key);
        tree->root = deleteNode(tree, tree->root, aux->key);
    }
    printf("\n");
    printSizes(tree, tree->root);
}

void perfo() {

    for (int test = 0; test < NR_OF_TESTS; test++) {
        for (int n = STEP_SIZE; n <= MAX_SIZE; n = n + STEP_SIZE) {
            rbTree *tree = buildTree(n);
            for (int i = 0; i < n; i++) {
                int temp = randomNumberInterval(n - i);
                node *aux = osSelect(tree->root, temp);
                tree->root = deleteNode(tree, tree->root, aux->key);
            }
            p.countOperation("Assignments Insert", n, insertAssignments);
            p.countOperation("Comparisons Insert", n, insertComparisons);

            p.countOperation("Assignments Select", n, selectAssignments);
            p.countOperation("Comparisons Select", n, selectComparisons);

            p.countOperation("Assignments Delete", n, deleteAssignments);
            p.countOperation("Comparisons Delete", n, deleteComparisons);
        }
        reset();
    }
    p.divideValues("Assignments Insert", NR_OF_TESTS);
    p.divideValues("Comparisons Insert", NR_OF_TESTS);

    p.divideValues("Assignments Select", NR_OF_TESTS);
    p.divideValues("Comparisons Select", NR_OF_TESTS);

    p.divideValues("Assignments Delete", NR_OF_TESTS);
    p.divideValues("Comparisons Delete", NR_OF_TESTS);

    p.addSeries("Total Assignments Aux", "Assignments Insert", "Assignments Select");
    p.addSeries("Total Assignments Final","Total Assignments Aux", "Assignments Delete");

    p.addSeries("Total Comparisons Aux", "Comparisons Insert", "Comparisons Select");
    p.addSeries("Total Comparisons Final","Total Comparisons Aux", "Comparisons Delete");

    p.showReport();
}


int main(int argc, char **argv) {
    srand(time(NULL));
    if(strcmp(argv[1], "demo")==0){
        demo();
    }
    else{
        perfo();
    }
    return 0;
}