#include "Array.h"
#include <iostream>
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