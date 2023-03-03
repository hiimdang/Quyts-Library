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
	bool add(NODET<T>*&,NODET<T>*);
	void traverse(void (*type)(NODET<T>*)); 
	NODET<T>* search(T);
	NODET<T>* max();
	NODET<T>* min();
	int countGreaterThanX(NODET<T>*, T);
	int count(NODET<T>*,int (*typeCount)(NODET<T>*));
	int heightBSTree(NODET<T>*);
	int getBalFactor(NODET<T>*);
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
bool BSTree<T>::add(NODET<T>*& root,NODET<T>* p) {
	if (p == NULL) {
		return false;
	}
	bool flag = false;
	if (root == NULL) {
		root = p;
		return true;
	}
	else {
			if (p->data > root->data) flag = add(root->pRight, p);
			if (p->data < root->data) flag = add(root->pLeft, p);
		}
	return flag;
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
	if (root == NULL) goto markSearch; //skip while and goto line 99
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
	if (root == NULL) return;
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
	if (root->pLeft == NULL && root->pRight == NULL) return 1;
	return leaf(root->pLeft) + leaf(root->pRight); 
}
template <class T>
int BSTree<T>::count(NODET<T>* root, int (*typeCount)(NODET<T>*)) { //only for Leaf(Zero),One,Two Child
	return typeCount(pRoot);
}
template <class T>
void findReplaceNode(NODET<T>*& p, NODET<T>*& q) {
	if (q->pLeft != NULL) {
		findReplaceNode(p, q->pLeft);
	}
	else { //q is the Node that u want to replace data with p
		p->data = q->data; //set data of Node that p point to same as the data of Node that node q point to
		p = q; //set p point to Node that Node q point to
		q = q->pRight; //set the pLeft of the old q is q->pRight
					   //example: before 5(old q): left to 3, right to NULL; 3(p): right to 4(q), left to NULL
					   //after: 5(old q): left to 4, right to NULL; 3(p) -> delete it then
	}				   //btw, if pRight of the q in q=q->pRight line is NULL -> q=NULL => old q->pLeft = NULL aka delete a leaf
}
template <class T>
int removeX(NODET<T>*& root, T X) {
	if (root == NULL) return -1;
	if (X < root->data) {
		return removeX(root->pLeft, X);
	}
	if (root->data < X) {
		return removeX(root->pRight, X);
	}
	NODET<T>* p = root; //p point to the Node that u want to delete
	if (root->pLeft == NULL) {
		root = root->pRight;
	}
	else if (root->pRight == NULL) {
		root = root->pLeft;
	}
	else { 
		findReplaceNode(p, root->pRight); //find the smallest Node that greater than Node p
	}
	delete p;
	return 1;
}
template <class T>
int BSTree<T>::heightBSTree(NODET<T>* root) {
	if (root == NULL) return 0;
	int left = heightBSTree(root->pLeft);
	int right = heightBSTree(root->pRight);
	return 1 + (left > right ? left : right);
}
template <class T>
int BSTree<T>::getBalFactor(NODET<T>* root) {
	return (heightBSTree(root->pRight) - heightBSTree(root->pLeft));
}