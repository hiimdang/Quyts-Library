#include <iostream>
#include <string>
using namespace std;
typedef int typeUse;
int convert(typeUse x);
#include "hashtable.h"
int convert(typeUse x) {
	//int sum = 0;
	//for (int i = 0; i < x.length(); i++) {
	//	sum += x[i]*(i+1);
	//}
	//return sum;
	return (int)x;
}
int main() {
	hashTable<typeUse>ht;
	ht.initTable();
	//--
	//ht.push("abc");
	//ht.push("xyz");
	//ht.push("htk");
	//ht.push("aca");
	//ht.push("bcd");
	//ht.push("cde");
	ht.push(3);
	ht.push(13);
	ht.push(24);
	ht.push(30);
	ht.push(31);
	ht.print();
	cout << "\n";
	cout << ht.find(32);
	cout << "\n";
	//ht.remove(24);
	//ht.remove(13);
	//ht.clearBucket(2);
	ht.print();

}