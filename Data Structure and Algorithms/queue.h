using namespace std;

template <class T>
struct NODEQ {
	T data;
	NODEQ<T>* pNext;
};
template <class T>
NODEQ<T>* CreateNodeQ(T x) {
	NODEQ<T>* p = new NODEQ<T>;
	p->data = x;
	p->pNext = NULL;
	return p;
}
template <class T>
struct Queue {
	NODEQ<T>* pHead;
	NODEQ<T>* pTail;

	bool isEmpty();
	void init();
	void push(T);
	NODEQ<T>* pop();
	NODEQ<T>* top();
};
template <class T>
bool Queue<T>::isEmpty() { // true -> empty
	return (pHead==NULL);
}
template <class T>
void Queue<T>::init(){
	pHead = NULL;
	pTail = NULL;
}
template <class T>
void Queue<T>::push(T x) {
	NODEQ<T>* p = CreateNodeQ(x); 
	if (p == NULL) return;
	if (pHead == NULL) {
		pHead = pTail = p;
	}
	else {
		pTail->pNext = p;
		pTail = p;
	}
}
template <class T>
NODEQ<T>* Queue<T>::top() {
	return pHead;
}
template <class T>
NODEQ<T>* Queue<T>::pop() {
	NODEQ<T>* p = pHead;
	pHead = p->pNext;
	p->pNext = NULL;
	return p;
}