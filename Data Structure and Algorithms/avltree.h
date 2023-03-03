#pragma once
using namespace std;
//#define LH -1
//#define EH 0
//#define RH 1

template <class T>
struct AVLNode {
	T data;
	int balFactor;
	AVLNode<T>* pLeft;
	AVLNode<T>* pRight;
};
template <class T>
AVLNode<T>* createAVLNode(T x) {
	AVLNode<T>* p = new AVLNode<T>;
	p->data = x;
	p->balFactor = 0;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}
template <class T>
struct AVLTree{
	AVLNode<T>* pRoot;
	//--
	void init();
	bool addNode(AVLNode<T>*&, T);
	void print();
};
template <class T>
void AVLTree<T>::init() {
	pRoot = NULL;
}
template <class T>
int heightAVLTree(AVLNode<T>* root) {
	if (root == NULL) return 0;
	int left = heightAVLTree(root->pLeft);
	int right = heightAVLTree(root->pRight);
	return 1 + (left > right ? left : right);
}
template <class T>
int getBalFactor(AVLNode<T>* root) {
	return(heightAVLTree(root->pRight) - heightAVLTree(root->pLeft));
}
template <class T>
void rotateLeft(AVLNode<T>*& root) {
	AVLNode<T>* Right = root->pRight;
	root->pRight = Right->pLeft;
	Right->pLeft = root;
	root->balFactor = getBalFactor(root);
	Right->balFactor = getBalFactor(Right);
	root = Right;
}
template <class T>
void rotateRight(AVLNode<T>*& root) {
	AVLNode<T>* Left = root->pLeft;
	root->pLeft = Left->pRight;
	Left->pRight = root;
	root->balFactor = getBalFactor(root);
	Left->balFactor = getBalFactor(Left);
	root = Left;
}
template <class T>
void LL(AVLNode<T>*& root) {
	rotateRight(root);
}
template <class T>
void LR(AVLNode<T>*& root) {
	rotateLeft(root->pLeft);
	rotateRight(root);
}
template <class T>
void RR(AVLNode<T>*& root) {
	rotateLeft(root);
}
template <class T>
void RL(AVLNode<T>*& root) {
	rotateRight(root->pRight);
	rotateLeft(root);
}
template <class T>
void show(AVLNode<T>* root) {
	cout << root->data << " ";
}
template <class T>
void NLR(AVLNode<T>* root) {
	if (root == NULL) return;
	show(root);
	NLR(root->pLeft);
	NLR(root->pRight);
}
template <class T>
void AVLTree<T>::print() {
	NLR(pRoot);
}
template <class T>
void balanceLeft(AVLNode<T>*& root, T x) {
	if (getBalFactor(root) == -2) { //LH
		if (getBalFactor(root->pLeft) <= 0) { //LL LB
			LL(root);
		}
		else { //LR
			LR(root);
		}
	}
}
template <class T>
void balanceRight(AVLNode<T>*& root, T x) {
	if (getBalFactor(root) == 2) {//RH
		if (getBalFactor(root->pRight) >= 0) {//RR RB
			RR(root);
		}
		else {//RL
			RL(root);
		}
	}
}
template <class T>
bool AVLTree<T>::addNode(AVLNode<T>*& root, T x) {
	if (root == NULL) {
		root = createAVLNode(x);
		return true;
	}
	bool flag = false;
	if (x < root->data) { //x < data -> go to left
		flag = addNode(root->pLeft, x);
		balanceLeft(root, x);
	}
	else if (x > root->data) { //x > data -> go to right
		flag = addNode(root->pRight, x);
		balanceRight(root, x);
	}
	root->balFactor = getBalFactor(root);
	return flag;
}
template <class T>
void findReplaceNode(AVLNode<T>*& p, AVLNode<T>*& q) {
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
bool removeX(AVLNode<T> *& root, T x) {
	if (root == NULL) {
		return false;
	}
	bool flag;
	if (x < root->data) {//x < data -> go to left
		flag = removeX(root->pLeft, x);
		balanceLeft(root, x);
	}
	else if (x > root->data) {//x > data -> go to right
		flag = removeX(root->pRight, x);
		balanceRight(root, x);
	}
	else {
		AVLNode<T>* p = root; //p point to the Node that u want to delete
		if (root->pLeft == NULL) {
			root = root->pRight;
		}
		else if (root->pRight == NULL) {
			root = root->pLeft;
		}
		else {
			findReplaceNode(p, p->pRight); //find and replace the smallest Node that greater than p;
		}
		delete p;
		flag = true;
	}
		root->balFactor = getBalFactor(root); //update balFactor
		if (root->balFactor >= 2 || root->balFactor <= -2) { //if |balFactor| >= 2 -> balance
			balanceLeft(root, x);
			balanceRight(root, x);
		}
		return flag;
}
