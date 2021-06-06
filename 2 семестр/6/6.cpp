#include <iostream>
using namespace std;
template <typename T, typename N>
class Pair {
	T x;
	N y;
public:
	Pair() {
		x = 0;
		y = 0;
	}
	Pair(T a) {
		x = a;
		y = 0;
	}
	Pair(N b) {
		x = 0;
		y = b;
	}
	Pair(T a, N b) {
		x = a;
		y = b;
	}
	Pair(Pair const& A) {
		x = A.x;
		y = A.y;
	}
	~Pair() {}
	Pair& operator =(Pair const& A) {
		x = A.x;
		y = A.y;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, const Pair& A) {
			out << '('<<A.x << ", "<<A.y<<") ";
		return out;
	}
};
int main() {
	char a = 1;
	int x = 3;
	Pair<char, int> A(a, x);
	std::cout << A;
	Pair<double, int> B(3.5);
	std::cout << B;
	Pair<Pair<char,int>, char> C(A,a);
	std::cout << C;
}