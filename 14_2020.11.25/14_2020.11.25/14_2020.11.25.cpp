//Выбрать все простые элементы из массива натуральных чисел не превосходящих k : A = [a1, ..., aN]
#include <iostream>
using namespace std;

int bi(int a, int mass[], int n)
{
	int l, r, m;
	l= 0;
	r = n;
	while (l <= r)
	{
		m = (l + r) / 2;
		if (a < mass[m])
			r = m - 1;
		else if (a > mass[m])
			l = m + 1;
		else
			return m;
	}
	return -1;
}

void f(int* x, int d, int n) {
	int* a = new int[n + 1];

	for (int i = 0; i < n + 1; i++)
		a[i] = i;

	for (int p = 2; p < n + 1; p++) {
		if (a[p] != 0) {
			for (int j = p * p; j < n + 1; j += p) {
				a[j] = 0;
			}
		}
	}

	int k = 0;
	for (int i = 2; i < n + 1; i++)
		if (a[i] != 0) k++;

	int * b = new int[k]; int c = 1;
	for (int i = 2; i < n + 1; i++) {
		if (a[i] != 0) {
			b[c] = i;
			c++;
		}
	}

	delete(a);

	for (int i = 1; i < d + 1; i++) {
		if (((x[i] % 2 )!= 0) || (x[i] == 2)) {
			if (bi(x[i], b, k) != -1) cout << x[i] << " ";
		}
	}
}


	int main() {
	int k=0, n; 
	cin >> n;
	int* a = new int[n];
	for (int i = 1; i < n + 1; i++) {
		cin >> a[i];
	}
	for (int i = 1; i < n + 1; i++) {
		if (k<a[i]) k=a[i];
	}
	f(a,n,k);
}