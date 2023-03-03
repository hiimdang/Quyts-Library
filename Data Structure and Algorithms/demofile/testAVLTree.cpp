#include <iostream>
#include "avltree.h"
using namespace std;
void printMinus() {
	cout << "\n";
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << "\n";
}
void menu() {
	cout << "\n1. Add a Node to AVL Tree\n";
	cout << "2. Show tree\n";
	cout << "3. Remove X\n";
	/*cout << "4. Max Node\n";
	cout << "5. Min Node\n";
	cout << "6. Count greater than X\n";
	cout << "7. Count Node\n";
	cout << "8. Remove X from Tree\n";
	cout << "9. Check height of a Node as a root\n";*/

	cout << "\n0. Quit\n";
}
//--
typedef int typeUse;
//--
int main() {
	AVLTree<typeUse> t;
	t.init();
	//--
	int option;
	printMinus();
	menu();
	typeUse x;
	do {
		printMinus();
		cout << "Choose ur option: ";
		cin >> option;
		switch (option) {
			case 1: {
				cout << "Type input for AVLTree: ";
				cin >> x;
				bool flag = t.addNode(t.pRoot, x);
				if (flag == 0) {
					cout << "Add failed! Tree already had a Node with data '" << x << "' ";
				}
				else {
					cout << "Congrats, u just added a Node with data '" << x << "'~";
				}
				break;
			}
			case 2: {
				t.print();
				break;
			}
			case 3: {
				cout << "Type the data of a Node that u want to from AVLTree: ";
				cin >> x;
				bool flag = removeX(t.pRoot, x);
				if (flag == false) {
					cout << "The Node with data '" << x << "' not in Tree";
				}
				else {
					cout << "Congrats, u just removed the Node with data '" << x << "' from the Tree~";
				}
				break;
			}
		}
	} while (option != 0);
	
	return 0;
}