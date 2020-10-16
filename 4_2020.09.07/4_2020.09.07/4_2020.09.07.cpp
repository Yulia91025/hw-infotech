#include <iostream>
using namespace std;
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}
struct Rational {
	int m;
	unsigned int n;
	// конструктор копий
	Rational(int x, unsigned int y) {
		m = x / gcd(x, y);
		n = y / gcd(x, y);
		cout << m <<" "<< n<<" ";
	}
	Rational multiply(Rational x, Rational y) {
		return Rational(x.m*y.m, x.n*y.n);
	}

	//оператор присваивания
	Rational&operator*=(Rational&x) {
		m *= x.m;
		n *= x.n;
		return*this;
		m /= gcd(m, n);
		n /= gcd(m, n);
		return*this;
	}
	
	//деструктор
	~Rational() {
		cout << "Rational is destroyed" << endl;
	}

};
	
int main() {
	int x; unsigned int y;
	cin >> x >> y;
	Rational(x, y);
	Rational multiply(x, y);
	Rational&operator*=(Rational x, Rational &y);
}