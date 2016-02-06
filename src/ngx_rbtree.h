#ifndef NGX_RBTREE_H
#define NGX_RBTREE_H
#include "ngx_core.h"

typedef ngx_uint_t ngx_rbtree_key_t;
typedef ngx_int_t ngx_rbtree_key_int_t;

typedef struct ngx_rbtree_node_s ngx_rbtree_node_t;

struct ngx_rbtree_node_s{
    ngx_rbtree_key_t key;
    ngx_rbtree_node_t *left;
    ngx_rbtree_node_t *right;
    ngx_rbtree_node_t *parent;
    u_char color;
    u_char data;
};


typedef void (*ngx_rbtree_insert_pt) (ngx_rbtree_node_t *root,
                                      ngx_rbtree_node_t *node,ngx_rbtree_node_t *sentinel);

typedef struct{
   ngx_rbtree_node_t *root;
   ngx_rbtree_node_t *sentinel;
   ngx_rbtree_insert_pt insert;
}ngx_rbtree_t;

typedef struct{
    ngx_rbtree_node_t node;
    ngx_str_t str;
}ngx_str_node_t;

//some examples of ngx_rbtree_insert_pt
void ngx_rbtree_insert_value(ngx_rbtree_node_t *root,
                             ngx_rbtree_node_t *node,ngx_rbtree_node_t *sentinel);
void ngx_rbtree_insert_timer_value(ngx_rbtree_node_t *root,
                                   ngx_rbtree_node_t *node,ngx_rbtree_node_t *sentinel);
void ngx_str_rbtree_insert_value(ngx_rbtree_node_t *root,
                                 ngx_rbtree_node_t *node,ngx_rbtree_node_t *sentinel);

//ngx_str_node_t lookup method
ngx_str_node_t *ngx_str_rbtree_lookup(ngx_rbtree_t *rbtree,
                                      ngx_str_t *name,u_int32_t hash);

//methods of rbtree node
#define ngx_rbt_red(node)        \
    ((node)->color = 1)
#define ngx_rbt_black(node)    \
    ((node)->color = 0)
#define ngx_rbt_is_red(node)       \
    ((node)->color )
#define ngx_rbt_is_black(node)       \
    (!ngx_rbt_is_red(node))
#define ngx_rbt_copy_color(n1,n2)     \
    ((n1)->color = (n2)->color)
#define ngx_rbtree_sentinel_init(node)    \
    ngx_rbt_black(node)

static ngx_inline ngx_rbtree_node_t * ngx_rbtree_min (ngx_rbtree_node_t *node,
                                    ngx_rbtree_node_t *sentinel){
    do{
        node = node->left;
    }while (node != sentinel);
    return node->parent;
}


//methods of rbtree container

#define ngx_rbtree_init(tree,s,i)                 \
    ngx_rbtree_sentinel_init(s);                     \
    (tree)->root = s;                                        \
    (tree)->sentinel = s;                                 \
    (tree)->insert = l;
void ngx_rbtree_insert(ngx_rbtree_t *tree,ngx_rbtree_node_t *node);
void ngx_rbtree_delete(ngx_rbtree_t *tree,ngx_rbtree_node_t *node);
















#endif // NGX_RBTREE_H

