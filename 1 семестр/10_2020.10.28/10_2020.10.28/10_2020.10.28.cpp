//Реализовать быстрое(бинарное возведение) в целую степень;

#include <iostream>
using namespace std;
int f(int a, int n) {
	if (n == 0) return 1;
	if (n % 2 == 1) return f(a, n - 1) * a;
	else {
		int b = f(a, n / 2);
		return b * b;
	}

}
int main() {
	int a; int n;
	cin >> a >> n;
	cout<<f(a, n);
}
