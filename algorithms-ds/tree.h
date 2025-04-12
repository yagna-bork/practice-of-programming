#ifndef GUARD_TREE_H
#define GUARD_TREE_H

template <class T>
struct TreeNode {
	T val;
	TreeNode *left; // lesser or equal
	TreeNode *right; // greater
};

/* returns the new tree after insertion */
template <class T>
TreeNode<T> *insert(TreeNode<T> *root, const T& val) 
{
	if (root == nullptr)
		return new TreeNode<T>{ val, nullptr, 
								nullptr };

	TreeNode<T> *prev = nullptr;
	TreeNode<T> *curr = root;
	while (curr != nullptr) {
		prev = curr;
		if (curr->val == val)
			return root; // ignore duplicates
		if (curr->val > val)
			curr = curr->left;
		else
			curr = curr->right;
	}

	TreeNode<T> *node = 
		new TreeNode<T>{ val, nullptr, nullptr };
	if (prev->val > val)
		prev->left = node;
	else
		prev->right = node;
	return root;
}

template <class T>
TreeNode<T> *lookup(TreeNode<T> *root, const T& val)
{
	if (root == nullptr)
		return root;
	else if (root->val == val)
		return root;
	else if (root->val > val)
		return lookup(root->left, val);
	else
		return lookup(root->right, val);
}

template <class T>
void applyinorder(TreeNode<T>* root, void (*f)(const T&))
{
	if (root == nullptr)
		return;
	applyinorder(root->left, f);	
	f(root->val);
	applyinorder(root->right, f);	
}

/* cool idea but couldn't get templates to work
template <class T>
void treesort(T v[], int n)
{
	if (n <= 1)
		return; // Already sorted

	int i;
	TreeNode<T> *root = nullptr;
	for (i = 0; i != n; i++)
		insert(root, v[i]);	

	i = 0;
	applyinorder(root, [i, v](const T& val) mutable { 
		v[i++] = val; 
	});
}
*/
#endif
