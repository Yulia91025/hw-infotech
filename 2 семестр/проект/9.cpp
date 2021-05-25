#include <iostream>
using namespace std;
template <typename T>
class Array {
	size_t mySize;
	T* myData;
public:
	Array();
	Array(size_t size);
	Array(Array const& A);
	~Array();
	Array& operator =(Array const& A);
	T& get(size_t i);
	void set(size_t i, T value);
	size_t size() const;
	friend std::ostream& operator<<(std::ostream& out, const Array& A) {
		for (size_t i = 0; i < A.mySize; i++)
			out << A.myData[i] << ' ';
		std::cout << endl;
		return out;
	}
};
template<typename T>
Array<T>::Array() {
	mySize = 0;
	myData = nullptr;
}
template<typename T>
Array<T>::Array(size_t size) :mySize(size), myData(new T[size]) {}
template<typename T>
Array<T>::Array(Array const& A) : mySize(A.mySize), myData(new T[A.mySize]) {
	for (size_t i = 0; i < mySize; i++)
		myData[i] = A.myData[i];
}
template<typename T>
Array<T>::~Array() {
	delete[] myData;
}
template<typename T>
Array<T>& Array<T>::operator =(const Array<T>& A) {
	if (myData) delete[] myData;
	mySize = A.mySize;
	myData = new T[mySize];
	for (size_t i = 0; i < mySize; i++)
		myData[i] = A.myData[i];
	return *this;
}
template<typename T>
T& Array<T>::get(size_t i) {
	return myData[i];
}
template<typename T>
void Array<T>::set(size_t i, T value) {
	if ((i >= 0) && (i < mySize))
		myData[i] = value;
}
template<typename T>
size_t Array<T>::size()const {
	return mySize;
}
template <>
double& Array<double>::get(size_t i){
	double x = 2 * myData[i];
	return x;
}
int main() {
	Array<int> A(10);
	Array<int> X;
	for (size_t i = 0; i < 10; i++)
		A.set(i, i);
	X = A;
	for (size_t i = 0; i < X.size(); i++)
		std::cout << X.get(i) << ' ';
	std::cout << endl;
	Array<double> B(5);
	for (size_t i = 0; i < 5; i++)
		B.set(i, i + 0.03);
	for (size_t i = 0; i < B.size(); i++)
		std::cout << B.get(i) << ' ';
	std::cout << endl;
	Array<char> D(10);
	for (size_t i = 0; i < 10; i++)
		D.set(i, i + 97);
	for (size_t i = 0; i < 10; i++)
		std::cout << D.get(i) << ' ';
	std::cout << endl;
	Array<Array<int>> Y(2);
	Y.set(0, A);
	Y.set(1, X);
	for (size_t i = 0; i < 2; i++)
		std::cout << Y.get(i);
}                     //программа выведет: 
					  //0 1 2 3 4 5 6 7 8 9
					  //0.06 2.06 4.06 6.06 8.06 (вместо 0.03 1.03 2.03 3.03 4.03) 
					  //a b c d e f g h i j
					  //0 1 2 3 4 5 6 7 8 9
					  //0 1 2 3 4 5 6 7 8 9