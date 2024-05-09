#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}

TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));
    if (map == NULL) return NULL;
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {

    Pair * par = (Pair*) malloc(sizeof(Pair));
    par->key = key;
    par->value = value;

    TreeNode* nodo = createTreeNode(key, value);
    if (tree->root == NULL){

        tree->root = nodo;
        tree->current = nodo;
    }else{
        TreeNode* temp = tree->root;
        while(1){
            if(tree->lower_than(nodo->pair->key, temp->pair->key)){
                if(temp->left == NULL){
                    temp->left = nodo;
                    nodo->parent = temp;
                    break;
                }else{
                    temp = temp->left;
                }
            }else if(tree->lower_than(temp->pair->key, nodo->pair->key)){
                if(temp->right == NULL){
                    temp->right = nodo;
                    nodo->parent = temp;
                    break;
                }else{
                    temp = temp->right;
                }
            }else{
                free(temp->pair->value);
                temp->pair->value = nodo->pair->value;
                free(nodo);
                break;
            }
        }
        tree->current = nodo;
    }
}

TreeNode * minimum(TreeNode * x){
    if(x==NULL) return NULL;
    while(x->left!=NULL) x=x->left;
    return x;
}

void removeNode(TreeMap * tree, TreeNode* node) {
    if(tree == NULL || node == NULL) return;
    TreeNode* current = tree->root;
    TreeNode* parent = NULL;
    int compare;

    while(current != NULL){
        compare = tree->lower_than(node->pair->key, current->pair->key);
        if(compare < 0){
            parent = current;
            current = current->left;
        } else if(compare > 0){
            parent = current;
            current = current->right;
        } else {
            if(current->left == NULL && current->right == NULL){
                if(parent == NULL){
                    tree->root = NULL;
                } else if(parent->left == current){
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
                free(current);
            } else if(current->left == NULL){
                if(parent == NULL){
                    tree->root = current->right;
                } else if(parent->left == current){
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }
                free(current);
            } else if(current->right == NULL){
                if(parent == NULL){
                    tree->root = current->left;
                } else if(parent->left == current){
                    parent->left = current->left;
                } else {
                    parent->right = current->left;
                }
                free(current);
            } else {
                TreeNode* successor = minimum(current->right);
                current->pair->key = successor->pair->key;
                current->pair->value = successor->pair->value;
                removeNode(tree, successor);
            }
            break;
        }
    }
    return;
}


void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;
    
    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {

    TreeNode* temp = tree->root;
    while(temp != NULL){
        if(is_equal(tree,temp->pair->key,key)){
            tree->current = temp;
            return temp->pair;
        }
        if(tree->lower_than(key,temp->pair->key)) temp = temp->left;
        else temp = temp->right;
    }    

    return NULL;  
}

Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {

    TreeNode* temp = tree->root;
    if(temp==NULL) return NULL;
    while(temp->left!=NULL) temp=temp->left;
    tree->current = temp;
    return temp->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if(tree == NULL) return NULL;
    TreeNode* temp = tree->current;

    if(temp->right != NULL){
        temp = temp->right;
        while(temp->left != NULL) temp = temp->left;
    tree->current = temp;
    return temp->pair;
    }

    while(temp->parent != NULL && temp->parent->right == temp){
        temp = temp->parent;
    }
    if(temp->parent == NULL) return NULL;

    tree->current = temp->parent;
    return tree->current->pair;
    
}
