#include <iostream>
using namespace std;
int f(int *m, int n) {
	int k = 0;
	cin >> n;
	m = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> m[i];
	}

	for (int i = 0; i < n; i++) {
		if (m[i] % 2 == 0) k++;
	}
	int *temp = new int[n - k]; int t = 0;

	for (int i = 0; i < n; i++) {
		if (m[i] % 2 != 0)
		{
			temp[t] = m[i];
			t++;
		}
	}
	delete(m);
	for (int i = 0; i < n - k; i++) {
		cout << temp[i] << " ";
	}
}
int main()
{
	int *m;
	int n;
	cin >> n;
	f(m, n);
}