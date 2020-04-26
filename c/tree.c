#include <c/tree.h>
#include <string.h>
#include <stdlib.h>

static int find_root(int* tree, const int size)
{
	for(int i = 0; i < size; i++)
		if(i == tree[i])
			return i;
	return -1;
}

bool is_isomorphic_tree(int* tree_1, int* tree_2, const int size)
{
	int prev, cur, next, root = find_root(tree_2, size);
	int *tree;
	if(root < 0)
		return false;
	tree = (int*)malloc(size * sizeof(int));
	if(!tree)
		return false;
	memcpy(tree, tree_1, size * sizeof(int));
	prev = root;
	cur = root;
	next = tree[cur];
	while(tree[cur] != cur) {
		tree[cur] = prev;
		prev = cur;
		cur = next;
		next = tree[next];
	}
	tree[cur] = prev;

	if(!memcmp(tree, tree_2, size * sizeof(int))) {
		free(tree);
		return true;
	}
	free(tree);
	return false;
}