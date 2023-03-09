#pragma once
using namespace std;
//NOTE: convert is a func in main file lul
const int hashGroups = 11;
template <class T>
struct HashNode {
	T data;
	HashNode<T>* pNext;
};
template <class T>
HashNode<T>* createHashNode(T x) {
	HashNode<T>* p = new HashNode<T>;
	p->data = x;
	p->pNext = NULL;
	return p;
}
template <class T>
struct hashTable {
	HashNode<T>* table[hashGroups];
	//--
	void initTable();
	bool isTableEmpty();
	bool isBucketEmpty(int key);
	void push(T);
	bool remove(T);
	void clearBucket(int index);
	bool find(T);
	void print();
	T popBucket(int index);
};
//--
template <class T>
int hashFunc(T x) {
	return convert(x) % hashGroups;
}
//--
template <class T>
void hashTable<T>::initTable() {
	for (int i = 0; i < hashGroups; i++) {
		table[i] = NULL;
	}
}
template <class T>
bool hashTable<T>::isTableEmpty() {
	int sum = 0;
	for (int i = 0; i < hashGroups; i++) {
		if (table[i] != NULL) sum += 1;
	}
	if (sum > 0) return 1;
	return 0;
}
template <class T>
bool hashTable<T>::isBucketEmpty(int index) {
	if (table[index] == NULL) return 1;
	return 0;
}
template <class T>
void hashTable<T>::push(T x) {
	HashNode<T>* p = createHashNode(x);
	if (p == NULL) return;
	int index = hashFunc(x);
	//--
	if (isBucketEmpty(index)) {
		table[index] = p;
	}
	else {
		p->pNext = table[index];
		table[index] = p;
	}
}
template <class T>
void show(HashNode<T>* x) {
	cout << x->data << " ";
}
template <class T>
void hashTable<T>::print() {
	for (int i = 0; i < hashGroups; i++) {
		if (!isBucketEmpty(i)) {
			cout << i<<": ";
			HashNode<T>* curr = table[i];
			while (curr) {
				show(curr);
				curr = curr->pNext;
			}
			cout << "\n";
		}
	}
}
template <class T>
T hashTable<T>::popBucket(int index) {
	if (isBucketEmpty(index)) return false;
	HashNode<T>* curr = table[index];
	table[index] = curr->pNext;
	curr->pNext = NULL;
	T data = curr->data;
	delete curr;
	return data;
}
template <class T>
bool hashTable<T>::remove(T x) {
	int index = hashFunc(x);
	HashNode<T>* curr = table[index];
	if (curr->data == x) { //if The data of pointer curr is x -> just pop that Node out of the bucket
		popBucket(index);
		return true;
	}
	//--
	while (curr != NULL) {
		if (curr->pNext!=NULL) {
			HashNode<T>* currNext = curr->pNext;
			if (currNext->data == x) { //delete node after node
				curr->pNext = currNext->pNext;
				currNext->pNext = NULL;
				delete currNext;
				return true;
			}
		}
		curr = curr->pNext;
	}
	if (curr == NULL) return false;
}
template <class T>
void hashTable<T>::clearBucket(int index) {
	while (!isBucketEmpty(index)) {
		popBucket(index);
	}
}
template <class T>
bool hashTable<T>::find(T x) {
	int index = hashFunc(x);
	HashNode<T>* curr = table[index];
	while (curr != NULL) {
		if (curr->data == x) return true;
		curr = curr->pNext;
	}
	return false;
}