#include <iostream>;
using namespace std;
void swap(int &x, int &y) {
	int temp = x;
	x = y;
	y = temp;
}
int main() {
	int n; int *m;
	cin >> n;
	m= new int[n];
	for (int i = 0; i < n; i++) {
		cin >> m[i];
	}
    for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (m[j] > m[j + 1]) {
				swap(m[j],m[j + 1]);
				}
			}
	}
	for (int i = 0; i <n; i++) {
		cout<< m[i]<<" ";
	}
}