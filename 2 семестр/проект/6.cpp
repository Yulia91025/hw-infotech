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
	friend std::ostream& operator<< (std::ostream& out, const Numbers& A)
	{
		out << A.x;
		return out;
	}
};
int main() {
	Numbers five(5), one(1);
	std::cout<< sum(five, one);
}//выводит верный ответ (6)