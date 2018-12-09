/* https://stackoverflow.com/a/26541331 */
typedef int make_iso_compilers_happy;

#ifdef TEST
#include <utilis/bst.h>
#include <stdbool.h>

struct data {
	int size;
	bool allocated;
};

MU_TEST(nodes_order_check)
{
	struct bst_node *root = bst_node_create(2, (void *)22);

	struct bst_node *right_node = bst_node_create(3, (void *)33);
	struct bst_node *left_node = bst_node_create(1, (void *)11);

	struct bst_node *right_right_node = bst_node_create(5, (void *)55);

	bst_insert(&root, right_node);
	bst_insert(&root, left_node);

	bst_insert(&root, right_right_node);

	mu_check(root->right_node->key > root->left_node->key);

	mu_check(root->right_node->right_node->key > right_node->key);
}

MU_TEST(attached_data_retrieval_check)
{
	struct data mydata = { 64, true };

	struct bst_node *root = bst_node_create(2, (void *)&mydata);

}

MU_TEST_SUITE(bst_test_suite)
{
	MU_RUN_TEST(nodes_order_check);
	MU_RUN_TEST(attached_data_retrieval_check);
}

int main()
{
	MU_RUN_SUITE(bst_test_suite);
	MU_REPORT();

	return minunit_status;
}
#endif
