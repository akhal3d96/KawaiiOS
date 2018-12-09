#include <utilis/bst.h>
#include <stddef.h>

struct bst_node *bst_init()
{
	struct bst_node *root =
	    (struct bst_node *)MALLOC(sizeof(struct bst_node));

	return root;
}

struct bst_node *bst_node_create(int key, void *data)
{
	struct bst_node *new_node = bst_init();

	new_node->key = key;
	new_node->data = data;

	new_node->left_node = NULL;
	new_node->right_node = NULL;

	return new_node;
}

struct bst_node *bst_search(struct bst_node *root, int key)
{
	if (root == NULL || root->key == key) {
		return root;
	} else if (root->key > key) {
		return bst_search(root->right_node, key);
	}
	return bst_search(root->left_node, key);
}

void bst_insert(struct bst_node **root, struct bst_node *new_node)
{
	if (*root == NULL) {
		*root = new_node;
		return;
	}

	if (new_node->key >= (*root)->key) {
		bst_insert(&((*root)->right_node), new_node);
	}

	else {
		bst_insert(&((*root)->left_node), new_node);
	}

	return;
}
