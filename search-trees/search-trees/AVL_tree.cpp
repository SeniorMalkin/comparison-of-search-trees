#include "AVL_tree.h"



AVL_tree::AVL_tree()
{
	root = NULL;
}


AVL_tree::~AVL_tree()
{
	if (root)
		tree_delete(root);
}

Node* AVL_tree::insert_node(Node *n, int key, int value)
{
	if (n == NULL)
	{
		n = new Node(key, value);
		return rebalance(n);
	}
	if (n->key > key)
	{
		n->left = insert_node(n->left, key, value);
		return rebalance(n);
	}
	else
	{
		n->right = insert_node(n->right, key, value);
		return rebalance(n);
	}

}

Node * AVL_tree::search(Node *n, int key)
{
	if (n == NULL)
		return NULL;
	if (n->key == key)
		return n;
	else if (n->key < key)
		n = search(n->right, key);
	else if ((n->key > key))
		n = search(n->left, key);
	else
		return n;
}

Node* AVL_tree::turn_left(Node* n)
{
	Node* p = n->right;
	n->right = p->left;
	p->left = n;
	reheight(n);
	reheight(p);
	return p;
}

Node* AVL_tree::turn_right(Node* n)
{
	Node* p = n->left;
	n->left = p->right;
	p->right = n;
	reheight(n);
	reheight(p);
	return p;
}

Node* AVL_tree::rebalance(Node* n)
{
	if (n == NULL) return 0;
	reheight(n);
	if (balance(n) == 2)
	{
		if (balance(n->right) < 0)
			n->right = turn_right(n->right);
		return turn_left(n);
	}
	if (balance(n) == -2)
	{
		if (balance(n->left) > 0)
			n->left = turn_left(n->left);
		return turn_right(n);
	}
	return n;
}

Node* AVL_tree::remove_min(Node* n, Node* iter)
{
	if (iter->left)
		iter->left = remove_min(n, iter->left);
	else
	{

		Node* r = iter->right;
		n->key = iter->key;
		n->value = iter->value;
		delete iter;
		iter = r;
	}
	return rebalance(iter);
}

Node* AVL_tree::remove(Node* n, int key)
{
	if (n == NULL) return 0;
	if (key < n->key)
		n->left = remove(n->left, key);
	else if (n->key < key)
		n->right = remove(n->right, key);
	else
	{
		Node *l = n->left, *r = n->right;
		if (l == NULL && r == NULL)
		{
			delete n;
			return 0;
		}
		if (r == NULL)
			return l;
		n->right = remove_min(n, r);
	}
	return rebalance(n);
}

void AVL_tree::tree_delete(Node * n)
{
	if (n->left)
		tree_delete(n->left);
	if (n->right)
		tree_delete(n->right);
	delete n;
}