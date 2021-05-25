#include <iostream>
#include <cstring>
using namespace std;
template <typename T, size_t size>
class Array {
	size_t mySize = size;
	T* myData;
public:
	Array();
	Array(Array const& A);
	~Array();
	Array& operator =(const Array& A);
	T& get(size_t i);
	void set(size_t i, T value);
};
template <typename T, size_t size>
Array<T, size>::Array() {
	myData = new T[size];
}
template <typename T, size_t size>
Array<T, size>::Array(Array const& A) : mySize(A.mySize), myData(new T[A.mySize]) {
	for (size_t i = 0; i < mySize; i++)
		myData[i] = A.myData[i];
}
template <typename T, size_t size>
Array<T, size>::~Array() {
	delete[] myData;
}
template <typename T, size_t size>
Array<T, size>& Array<T, size>::operator =(const Array<T, size>& A) {
	if (myData) delete[] myData;
	mySize = A.mySize;
	myData = new T[mySize];
	for (size_t i = 0; i < mySize; i++)
		myData[i] = A.myData[i];
	return *this;
}
template <typename T, size_t size>
T& Array<T, size>::get(size_t i) {
	return myData[i];
}
template <typename T, size_t size>
void Array<T, size>::set(size_t i, T value) {
	if ((i >= 0) && (i < mySize))
		myData[i] = value;
}
template <typename T, size_t size>
void print(Array<T, size>& A){
	for (size_t i = 0; i < size; i++)
		std::cout << A.get(i) << ' ';
	std::cout << endl;
}
int main() {
	Array<char,14> D;
	char* d = new char[14];
	strcpy_s(d, 14, "Hello, world!"); // подключаем в начале библиотеку cstring для использования преобразования строки в массив типа char 
	for (size_t i = 0; i < 14; i++)
		D.set(i,d[i]);
	print(D);
}                   //программа выведет:
                    //H e l l o ,   w o r l d !