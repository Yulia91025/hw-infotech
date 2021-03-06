#include <iostream>
#include <cstring>
using namespace std;
template <typename T, size_t size>
class Array { // общий родительский шаблон
protected: 
	size_t mySize = size; // меняем спецификатор доступа с private на protected, чтобы возможно было использовать их наследниками 
	T* myData;
public:
	Array();
	Array(Array const& A);
	~Array();
	Array& operator =(const Array& A);
	T& get(size_t i);
	void set(size_t i, T value);
	void print(Array& A);
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
void Array<T, size>::print(Array<T, size>& A){
	for (size_t i = 0; i < size; i++)
		std::cout << A.get(i) << ' ';
	std::cout << endl;
}
template<class T, size_t size>
class myArray: public Array<T,size> { // создаём шаблон-наследник 
public:
	myArray(){}
};
template <size_t size>
class myArray<char, size> : public Array<char, size> // создаём ещё один шаблон-наследник, но уже с частичной специализацией 
{
public:
	virtual void print(myArray& A){
		for (size_t i = 0; i < size; i++)
			std::cout << A.get(i);
		std::cout << endl;
	}
};
int main() {
	myArray<char,14> D;
	char* d = new char[14];
	strcpy_s(d, 14, "Hello, world!");
	for (size_t i = 0; i < 14; i++)
		D.set(i,d[i]);
	D.print(D); 
	myArray<char, 16> B;
	char* b = new char[16];
	strcpy_s(b, 16, "Hello everybody");
	for (size_t i = 0; i < 16; i++)
		B.set(i, b[i]);
	B.print(B); 
	myArray<double, 5> A;
	for (size_t i = 0; i < 5; i++)
		A.set(i, i + 0.03);
	A.print(A);
}                   //программа выведет:
                    //Hello, world!
                    //Hello everybody
                    //0.03 1.03 2.03 3.03 4.03 
