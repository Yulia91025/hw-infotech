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

};
int main() {
	Numbers five(5), one(1);
	sum(five, one);
}//VS выдаёт следующую ошибку: error C2676: бинарный "+": "T" не определяет этот оператор или преобразование к типу приемлемо к встроенному оператору
