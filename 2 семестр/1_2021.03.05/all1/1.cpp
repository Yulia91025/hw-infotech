#include <iostream>
#include "1.h"
using namespace std;
int main() {
	int n;
	std::cout << "Enter the number of elements of the array\n";
	std::cin >> n;
	int* a = new int[n];
	std::cout << "Enter an array\n";
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}

	int v;
	std::cout << "Select sorting method:\n"<<"choice=1\n" << "bubble=2\n" << "shaker=3\n" << "insertion=4\n";
	cin >> v;
	switch (v) {
	case 1:
		ch(a,n);
		break;
	case 2:
		b(a,n);
		break;
	case 3:
		sh(a,n);
		break;
	case 4:
		in(a,n);
		break;
	default:
		std::cout << "Unknown";
		break;
	}
	return 0;
}