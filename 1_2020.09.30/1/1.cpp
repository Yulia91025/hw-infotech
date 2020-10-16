#include <iostream>
using namespace std;
int main() {
	int n, s = 0, a = 0;
	cin>>n;
	for (int i = 0; i < n; i++) {
		cin>>a;
		s = s + a * a*a;
	}

	s = s / n;
	cout<<s;
}