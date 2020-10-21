#include <iostream>
using namespace std;
int f(int* a, int n) {
	int k = 0;
	cin >> n;
	a = new int[n + 1];

	for (int i = 0; i < n + 1; i++)
		a[i] = i;

	for (int p = 2; p < n + 1; p++){
		if (a[p] != 0){
			for (int j = p * p; j < n + 1; j += p) {
				a[j] = 0; 
				k++;
			}
		}
	}

	int *b = new int[k]; int c = 1;
	for (int i = 2; i < n + 1; i++) {
		if (a[i]=0) {
			b[c] = i;
			c++;
		}
	}

	delete(a);

	for (int i = 1; i < k + 1; i++) {
		cout<<b[i]<<" ";
	}
}

int main() {
	int n; 
	cin >> n;
	int *a;
	f(a,n);	
}