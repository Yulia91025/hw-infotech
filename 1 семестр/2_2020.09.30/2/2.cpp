#include <iostream>
using namespace std;
int main() {
	int n,k,a=1,b=1;
	cin >> n >> k; 
	for (int i = k+1; i < n + 1; i++) {
		a = a * i/b;
		b = b + 1;
	}
	cout << a << " ";
}