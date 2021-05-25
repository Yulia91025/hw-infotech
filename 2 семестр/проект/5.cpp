#include <iostream>
using namespace std;
template <typename T>
T sum(T a, T b) {
	return a + b;
}
class Numbers {
	int x;
public:
	Numbers(int i) :x(i) {};
	friend int operator +(const Numbers& A, const Numbers& B) {
		return (A.x + B.x);
	}

};
int main() {
	Numbers five(5), one(1);
	sum(five, one);
}