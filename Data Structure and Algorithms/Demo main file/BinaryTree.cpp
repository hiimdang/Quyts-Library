#include <iostream>
#include "bstree.h"
#include <string.h>
using namespace std;

//--type u want in here
typedef string type;
//--
void printMinus() {
	cout << "\n";
	for (int i = 0; i < 50; i++) {
		cout << "-";
	}
	cout << "\n";
}
void menu() {
	cout << "\n1. Add a Node to Binary Tree\n";
	cout << "2. Show tree\n";
	cout << "3. Search Node\n";
	cout << "4. Max Node\n";
	cout << "5. Min Node\n";
	cout << "6. Count greater than X\n";
	cout << "7. Count Node\n";
	cout << "8. Remove X from Tree\n";
	cout << "9. Check height of a Node as a root\n";

	cout << "\n0. Quit\n";
}
void menuCase2() {
	cout << "\t1. NLR\n";
	cout << "\t2. NRL\n";
	cout << "\t3. LNR\n";
	cout << "\t4. RNL\n";
	cout << "\t5. LRN\n";
	cout << "\t6. RLN\n";
	cout << "\tChoose ur traverse option: ";
}
void menuCase7() {
	cout << "\t1. Count Leaf (No Child)\n";
	cout << "\t2. Count Node 1 Child\n";
	cout << "\t3. Count Node 2 Child\n";
}
int main() {
	BSTree<type> t;
	t.init();
	//---
	printMinus();
	menu();
	int option;
	type x; //
	do {
		printMinus();
		cout << "Choose ur option: ";
		cin >> option;
		switch (option) {
			case 1: {
				cout << "Type input for Binary Tree: ";
				cin >> x;
				t.add(t.pRoot,createNodeT(x));
				break;
			}
			case 2: {
				cout << "--\n";
				menuCase2();
				int optionCase2;
				cin >> optionCase2;
				cout << "--\n";
				switch (optionCase2){
					case 1: { //NLR
						t.traverse(NLR);
						break;
					}
					case 2: { //NRL
						t.traverse(NRL);
						break;
					}
					case 3: { //LNR
						t.traverse(LNR);
						break;
					}
					case 4: { //RNL
						t.traverse(RNL);
						break;
					}
					case 5: { //LRN
						t.traverse(LRN);
						break;
					}
					case 6: { //RLN
						t.traverse(RLN);
						break;
					}
				}
				break;
			}
			case 3: {
				cout << "Type input of a Node to search: ";
				cin >> x;
				if (t.search(x)) {
					cout << "Tree had a Node with data '" << x << "'";
				}
				else {
					cout <<"Node with data '" << x << "' not in Tree";
				}
				break;
			}
			case 4: {
				cout << "Max Data of a Node in Tree: '" << t.max()->data << "'";
				break;
			}
			case 5: {
				cout << "Min Data of a Node in Tree: '" << t.min()->data << "'";
				break;
			}
			case 6: {
				type x; int count = 0;
				cout << "Input X: ";
				cin >> x;
				cout << "Number of Node have Data greater than '" << x << "': " << t.countGreaterThanX(t.pRoot, x);
				break;
			}
			case 7: {
				cout << "--\n";
				menuCase7();
				int optionCase7;
				cin >> optionCase7;
				cout << "--\n";
				switch (optionCase7) {
					case 1: {
						cout << "Number of Leaf Node(s): " << t.count(t.pRoot,leaf);
						break;
					}
					case 2: {
						cout << "Number of Node(s) with 1 child: " << t.count(t.pRoot, oneChild);
						break;
					}
					case 3: {
						cout << "Number of Node(s) with 2 child: " << t.count(t.pRoot, twoChild);
						break;
					}
				}
				break;
			}
			case 8: {
				type x;
				cout << "Input data that u want to remove from Tree: ";
				cin >> x;
				int flag = removeX(t.pRoot, x);
				if (flag == -1) {
					cout << "Theres not Node with data '" << x << "' in the Tree!";
				}
				else {
					cout << "Congrats, u just removed the Node with data '" << x << "' from the Tree~";
				}
				break;
			}
			case 9: {
				type x;
				cout << "Input data that u want to check height: ";
				cin >> x;
				cout << "Height of that Node is: "<< heightBSTree<type>(t.search(x));
			}
		}
	} while (option != 0);
	return 0;
}