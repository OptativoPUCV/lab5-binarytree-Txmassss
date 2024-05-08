#include "treemap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode TreeNode;

struct TreeNode {
  Pair *pair;
  TreeNode *left;
  TreeNode *right;
  TreeNode *parent;
};

struct TreeMap {
  TreeNode *root;
  TreeNode *current;
  int (*lower_than)(void *key1, void *key2);
};

int is_equal(TreeMap *tree, void *key1, void *key2) {
  if (tree->lower_than(key1, key2) == 0 && tree->lower_than(key2, key1) == 0)
    return 1;
  else
    return 0;
}

TreeNode *createTreeNode(void *key, void *value) {
  TreeNode *new = (TreeNode *)malloc(sizeof(TreeNode));
  if (new == NULL)
    return NULL;
  new->pair = (Pair *)malloc(sizeof(Pair));
  new->pair->key = key;
  new->pair->value = value;
  new->parent = new->left = new->right = NULL;
  return new;
}

TreeMap *createTreeMap(int (*lower_than)(void *key1, void *key2)) {
  TreeMap *newTreeMap = (TreeMap *)malloc(sizeof(TreeMap));
  if (newTreeMap == NULL) {
    return NULL;
  }

  newTreeMap->root = NULL;
  newTreeMap->current = NULL;
  newTreeMap->lower_than = lower_than;

  return newTreeMap;
}

void insertTreeMap(TreeMap *tree, void *key, void *value) {
  if (tree == NULL || key == NULL || value == NULL) {
      return;
  }

  TreeNode *new_node = createTreeNode(key, value);
  if (new_node == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      return;
  }

  if (tree->root == NULL) {
      tree->root = new_node;
      return;
  }

  TreeNode *current = tree->root;
  TreeNode *parent = NULL;

  while (current != NULL) {
      parent = current;
      int cmp = tree->lower_than(key, current->pair->key);
      if (cmp < 0) {
          current = current->left;
      } else if (cmp > 0) {
          current = current->right;
      } else {
          // Key already exists, update the value and return
          current->pair->value = value;
          free(new_node->pair);
          free(new_node);
          return;
      }
  }

  new_node->parent = parent;
  if (tree->lower_than(key, parent->pair->key) < 0) {
      parent->left = new_node;
  } else {
      parent->right = new_node;
  }
}

TreeNode *minimum(TreeNode *x) { return NULL; }

void removeNode(TreeMap *tree, TreeNode *node) {}

void eraseTreeMap(TreeMap *tree, void *key) {
  if (tree == NULL || tree->root == NULL)
    return;

  if (searchTreeMap(tree, key) == NULL)
    return;
  TreeNode *node = tree->current;
  removeNode(tree, node);
}

Pair *searchTreeMap(TreeMap *tree, void *key){
  if (tree == NULL || key == NULL) {
    return NULL; // Verificación de parámetros inválidos
  }

  TreeNode* current = tree->root;
  while (current != NULL) {
    int cmp = tree->lower_than(key, current->pair->key);
    if (cmp == 0) {
        return current->pair; // Clave encontrada, devolver par
    } else if (cmp < 0) {
        current = current->left; // Ir al hijo izquierdo
    } else {
        current = current->right; // Ir al hijo derecho
    }
  }

  return NULL; // Clave no encontrada
}

Pair *upperBound(TreeMap *tree, void *key) { return NULL; }

Pair *firstTreeMap(TreeMap *tree) { return NULL; }

Pair *nextTreeMap(TreeMap *tree)  { return NULL; }
