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

}

TreeNode * minimum(TreeNode * x){
    if(x==NULL) return NULL;
    while(x->left!=NULL) x=x->left;
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

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
    if(tree == NULL || tree->root == NULL) return NULL;
    
    TreeNode * temp = tree->current;
    if(temp->right != NULL){
        tree->current = temp->right;
        TreeNode* arbol = minimum(tree->current);
        
        return arbol->pair;
    } 
   while(temp->parent != NULL && temp->parent->right == temp){
       temp = temp->parent;
   }
    if(temp->parent == NULL) return NULL;
    tree->current = temp->parent;
    return tree->current->pair;
}
