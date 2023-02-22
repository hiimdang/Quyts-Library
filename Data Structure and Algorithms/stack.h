using namespace std;

template <class T>
struct NODES {
	T data;
	NODES<T>* pNext;
};
template <class T>
NODES<T>* CreateNodeS(T x) {
	NODES<T>* p = new NODES<T>;
	p->data = x;
	p->pNext = NULL;
	return p;
}
template <class T>
struct Stack {
	NODES<T>* pTop;

	void init();
	void push(T);
	bool isEmpty();
	NODES<T>* pop();
	NODES<T>* top();
};
template <class T>
bool Stack<T>::isEmpty() { // true -> empty
	return (pTop == NULL);
}
template <class T>
void Stack<T>::init() {
	pTop = NULL;
}
template <class T>
void Stack<T>::push(T x) {
	NODES<T>* p = CreateNodeS(x);
	if (p == NULL) return;
	if (pTop == NULL) {
		pTop = p;
	}
	else {
		p->pNext = pTop;
		pTop = p;
	}
}
template <class T>
NODES<T>* Stack<T>::top() {
	return pTop;
}
template <class T>
NODES<T>* Stack<T>::pop() {
	NODES<T>* p = pTop;
	pTop = p->pNext;
	p->pNext = NULL;
	return p;
}
