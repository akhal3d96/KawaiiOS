#ifndef BST_H
#define BST_H

#ifdef TEST

#include <minunit.h>

#define MALLOC malloc

#else

#define MALLOC kmalloc
#include <mm/kheap.h>

#endif

struct bst_node {
	int key;
	void *data;
	struct bst_node *left_node, *right_node;
};

struct bst {
	struct bst_node *root;
	uint32_t size;

};

struct bst_node *bst_init();
struct bst_node *bst_node_create(int key, void *data);
struct bst_node *bst_search(struct bst_node *root, int key);

void bst_insert(struct bst_node **root, struct bst_node *new_node);

#endif
