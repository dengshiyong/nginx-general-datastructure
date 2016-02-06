#include "ngx_core.h"

static ngx_inline  void ngx_rbtree_left_rotate(ngx_rbtree_node_t **root,ngx_rbtree_node_t *sentinel,
                                               ngx_rbtree_node_t *node);
static ngx_inline  void ngx_rbtree_right_rotate(ngx_rbtree_node_t **root,ngx_rbtree_node_t *sentinel,
                                                ngx_rbtree_node_t *node);
static ngx_inline void ngx_rbtree_left_rotate(ngx_rbtree_node_t **root,ngx_rbtree_node_t *sentinel,
                                              ngx_rbtree_node_t *node){
    ngx_rbtree_node_t *temp;
    temp = node->right;
    node->right = temp->left;

    if(temp->left != sentinel){
        temp->left->parent = node;
    }

    temp->parent = node->parent;

    if(node == *root){
        *root = temp;
    }
    else if(node == node->parent->left) {
        node->parent->left = temp;
    }
    else{
        node->parent->right = temp;
    }
    node->parent = temp;
    temp->left = node;
}

static ngx_inline void ngx_rbtree_right_rotate(ngx_rbtree_node_t **root,ngx_rbtree_node_t *sentinel,
                                               ngx_rbtree_node_t *node){
    ngx_rbtree_node_t *temp;
    temp = node->left;
    node->left = temp->right;

    if(temp->right != sentinel){
        temp->right->parent = node;
    }

    temp->parent = node->parent;

    if (node == *root){
        *root = temp;
    }
    else if(node == node->parent->left){
        node->parent->left = temp;
    }
    else{
        node->parent->right = temp;
    }
    temp->right = node;
    node->parent = temp;
}





















