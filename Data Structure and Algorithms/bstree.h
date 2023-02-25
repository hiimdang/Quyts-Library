#pragma once
using namespace std;
//#ifndef __FUNCTION_IN_STRUCT_H_
//#define __FUNCTION_IN_STRUCT_H_
template <class T>
struct NODET {
	T data;
	NODET<T>* pLeft;
	NODET<T>* pRight;
};
template <class T>
NODET<T>* createNodeT(T x) {
	NODET<T>* p = new NODET<T>;
	p->data = x;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}
template <class T>
struct BSTree {
	NODET<T>* pRoot;

	//---
	void init();
	bool isEmpty();
	void add(NODET<T>*&,NODET<T>*);
	void remove(); 
	void traverse(void (*type)(NODET<T>*)); 
	NODET<T>* search(T);
	NODET<T>* max();
	NODET<T>* min();
	int countGreaterThanX(NODET<T>*, T);
	int count(NODET<T>*,int (*typeCount)(NODET<T>*));
};
//#endif
template <class T>
void BSTree<T>::init() {
	pRoot = NULL;
}
template <class T>
bool BSTree<T>::isEmpty() { //true -> empty
	return (pRoot == NULL);
}

template <class T>
void BSTree<T>::add(NODET<T>*& root,NODET<T>* p) {
	if (p == NULL) {
		cout << "Add failed, ur input is NULL";
		return;
	}
	if (root == NULL) {
		root = p;
		cout << "Congrats, you just added a node with data '" << p->data << "' to the Binary Tree~";
	}
	else {
		if (p->data == root->data) {
			cout << "Add failed, Binary Tree already had a Node with data '" << p->data << "'";
			return;
		}
		if (p->data > root->data) add(root->pRight, p);
		if (p->data < root->data) add(root->pLeft, p);
		}
}
//template<class T>
//NODET<T>* BSTree<T>::search(T x){
//	NODET<T>* root = pRoot;
//	s1:if (root == NULL) return NULL; // not in Tree
//	if (root->data!= x){
//		if (x > root->data) {
//			root = root->pRight;
//			goto s1;
//		}
//		if (x < root->data) {
//			root = root->pLeft;
//			goto s1;
//		}
//	}
//	return root; // root == x
//}

//top of this func is another search function but im not really like use goto to create a loop
template<class T>
NODET<T>* BSTree<T>::search(T x){
	NODET<T>* root = pRoot;
	if (root == NULL) goto markSearch; //skip while and goto line 98
	while(root != NULL){
		if (root->data == x) return root;
		if (root->data != x) {
			if (x > root->data) {
				root = root->pRight;
				continue; //skip this loop time to not check the if below this if
			}
			if (x < root->data) {
				root = root->pLeft;
			}
		}
	}
	markSearch: return NULL; 
}
// show func
template <class T>
void show(NODET<T>* p) {
	cout << p->data << " ";
}
//---
//All func traverse
template <class T>
void LNR(NODET<T>* root) {
	if (root == NULL) return;
	LNR(root->pLeft);
	show(root);
	LNR(root->pRight);
}
template <class T>
void RNL(NODET<T>* root) {
	if (root == NULL) return;
	RNL(root->pRight);
	show(root);
	RNL(root->pLeft);
}
template <class T>
void NLR(NODET<T>* root) {
	if (root == NULL) return;
	show(root);
	NLR(root->pLeft);
	NLR(root->pRight);
}
template <class T>
void NRL(NODET<T>* root) {
	if (root == NULL) return;
	show(root);
	NRL(root->pRight);
	NRL(root->pLeft);
}
template <class T>
void LRN(NODET<T>* root) {
	if (root == NULL) return;
	LRN(root->pLeft);
	LRN(root->pRight);
	show(root);
}
template <class T>
void RLN(NODET<T>* root) {
	if (root == NULL) return;
	RLN(root->pRight);
	RLN(root->pLeft);
	show(root);
}
// end all func traverse
template <class T>
void BSTree<T>::traverse(void (*type)(NODET<T>*)) {
	type(pRoot); //use pRoot of BSTree as the first root to call func traverse 
}
template <class T>
NODET<T>* BSTree<T>::max() {
	NODET<T>* root = pRoot;
	while(root->pRight!=NULL){
		root = root->pRight;
	}
	return root;
}
template <class T>
NODET<T>* BSTree<T>::min() {
	NODET<T>* root = pRoot;
	while (root->pLeft != NULL) {
		root = root->pLeft;
	}
	return root;
}
template <class T>
int BSTree<T>::countGreaterThanX(NODET<T>* root, T x) {
	if (root == NULL) return 0;
	int count = countGreaterThanX(root->pLeft, x) + countGreaterThanX(root->pRight, x);
	if (root->data > x) return count + 1;
	return count;
}
//count funcs
template <class T>
int twoChild(NODET<T>* root) {
	if (root == NULL) return 0;
	int count = twoChild(root->pLeft) + twoChild(root->pRight);
	return (root->pRight != NULL && root->pLeft != NULL) ? count + 1 : count;
}
template <class T>
int oneChild(NODET<T>* root) {
	if (root == NULL) return 0;
	int count = oneChild(root->pLeft) + oneChild(root->pRight);
	return ((root->pRight == NULL && root->pLeft != NULL) || (root->pRight != NULL && root->pLeft == NULL)) ? count + 1 : count;
}
template<class T>
int leaf(NODET<T>* root) {
	if (root == NULL) return 0;
	int count = leaf(root->pLeft) + leaf(root->pRight);
	return (root->pLeft == NULL && root->pRight == NULL) ? count + 1 : count;
}
template <class T>
int BSTree<T>::count(NODET<T>* root, int (*typeCount)(NODET<T>*)) { //only for Leaf(Zero),One,Two Child
	return typeCount(pRoot);
}