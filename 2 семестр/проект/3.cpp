#include <iostream>
using namespace std;
template <typename T>
const T& sum(const T& a, const T& b) {
	return a + b;
}
int main() {
	int a = 5, b = 3;
	std::cout << sum(a, b) << ' ';
	double x = 5.5, y = 3.5;
	std::cout << sum(x, y) << ' ';
}