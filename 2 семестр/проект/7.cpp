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
int main() {
	Array<int> A(10); //вызвали нетривиальный конструктор для значений типа int 
	Array<int> X; //вызвали тривиальный конструктор для значений типа int 
	for (size_t i = 0; i < 10; i++)
		A.set(i, i);
	X = A; //присвоили значения массива A массиву X
	for (size_t i = 0; i < X.size(); i++)
		std::cout << X.get(i) << ' ';
	std::cout << endl;
	Array<double> B(5); //вызвали тривиальный конструктор для значений типа double
	for (size_t i = 0; i < 5; i++)
		B.set(i, i + 0.03);
	for (size_t i = 0; i < B.size(); i++)
		std::cout << B.get(i) << ' ';
	std::cout << endl;
	Array<char> D(10); //вызвали тривиальный конструктор для значений типа char
	for (size_t i = 0; i < 10; i++)
		D.set(i, i+97);
	for (size_t i = 0; i < 10; i++)
		std::cout << D.get(i) << ' ';
}                     //программа выведет: 
                      //0 1 2 3 4 5 6 7 8 9
                      //0.03 1.03 2.03 3.03 4.03
                      //a b c d e f g h i j