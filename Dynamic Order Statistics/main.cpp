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

int insertComps, insertAss;
int selectComps, selectAss;
int deleteComps, deleteAss;

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
    ///insertAss++;
    int aux = y->size;
    y->size = x->size;
    x->size = x->size - aux + y->left->size;
    x->right = y->left;
    ///insertComps++;
    if (y->left != tree->NIL) {
        y->left->parent = x;
        ///insertAss++;
    }
    ///insertAss++;
    y->parent = x->parent;
    ///insertComps++;
    if (x->parent == tree->NIL) {
        tree->root = y;
        ///insertAss++;
    } else if (x == x->parent->left) {
        x->parent->left = y;
        ///insertAss++;
    } else {
        x->parent->right = y;
        ///insertAss++;
    }
    y->left = x;
    x->parent = y;
    ///insertAss++;

}

void rightRotate(rbTree *tree, node *x) {
    node *y = x->left;
    ///insertAss++;
    int aux = y->size;
    y->size = x->size;
    x->size = x->size - aux + y->right->size;
    x->left = y->right;
    ///insertComps++;
    if (y->right != tree->NIL) {
        y->right->parent = x;
        ///insertAss++;
    }

    y->parent = x->parent;
    ///insertComps++;
    if (x->parent == tree->NIL) {
        tree->root = y;
        ///insertAss++;
    } else {
        ///insertComps++;
        if (x == x->parent->right) {
            x->parent->right = y;
            ///insertAss++;
        } else {
            x->parent->left = y;
            ///insertAss++;
        }
    }
    y->right = x;
    ///insertAss++;
    x->parent = y;
}

void insertionFixUp(rbTree *tree, node *z) {
    while (z->parent->colour == Red) {
        ///insertComps++;
        if (z->parent == z->parent->parent->left) {
            node *uncle = z->parent->parent->right;
            ///insertComps++;
            if (uncle->colour == Red) {
                z->parent->colour = Black;
                uncle->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else {
                ///insertComps++;
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
            ///insertComps++;
            if (uncle->colour == Red) {
                z->parent->colour = Black;
                uncle->colour = Black;
                z->parent->parent->colour = Red;
                z = z->parent->parent;
            } else {
                ///insertComps++;
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
        insertComps++;
        parent = temp;
        parent->size++;
        insertComps++;
        if (z->key < temp->key){
            temp = temp->left;
            insertAss++;
        }
        else{
            temp = temp->right;
            insertAss++;
        }
    }
    z->parent = parent;
    insertComps++;
    if (parent == tree->NIL) {
        insertAss++;
        tree->root = z;
    } else {
        insertComps++;
        if (z->key < parent->key){
            parent->left = z;
        }
        else{
            parent->right = z;
            insertAss++;
        }
    }
    z->right = tree->NIL;
    z->left = tree->NIL;
    insertionFixUp(tree, z);
}

node *osSelect(node *root, int i) {
    int aux = root->left->size + 1;
    selectComps++;
    if (i == aux) {
        return root;
    } else {
        selectComps++;
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

struct node *deleteNode(rbTree *tree, node *root, int key) {
    // base case
    deleteComps++;
    if (root == nullptr)
        return root;

    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    deleteComps++;
    if (key < root->key) {
        root->size--;
        root->left = deleteNode(tree, root->left, key);
    }

        // If the key to be deleted is
        // greater than the root's
        // key, then it lies in right subtree
    else {
        deleteComps++;
        if (key > root->key) {
            root->size--;
            root->right = deleteNode(tree, root->right, key);
        } else {
            // node has no child
            deleteComps++;
            if (root->left == tree->NIL and root->right == tree->NIL)
                return tree->NIL;

                // node with only one child or no child
            else {
                deleteComps++;
                if (root->left == tree->NIL) {
                    struct node *temp = root->right;
                    deleteAss++;
                    free(root);
                    return temp;
                } else {
                    deleteComps++;
                    if (root->right == tree->NIL) {
                        struct node *temp = root->left;
                        deleteAss++;
                        free(root);
                        return temp;
                    }
                }
            }
            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            struct node *temp = minimum(tree, root->right);

            // Copy the inorder successor's content to this node
            temp->size = root->size--;
            root->key = temp->key;

            // Delete the inorder successor
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
    insertComps=0;
    insertAss=0;

    selectComps=0;
    selectAss=0;

    deleteComps=0;
    deleteAss=0;
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
            p.countOperation("Assignments Insert", n, insertAss);
            p.countOperation("Comparisons Insert", n, insertComps);

            p.countOperation("Assignments Select", n, selectAss);
            p.countOperation("Comparisons Select", n, selectComps);

            p.countOperation("Assignments Delete", n, deleteAss);
            p.countOperation("Comparisons Delete", n, deleteComps);
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