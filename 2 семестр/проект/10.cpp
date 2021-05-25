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

template<>
class Array<bool> {
	size_t mySize;
	char* myData;
public:
	Array() { //тривиальный конструктор не изменится 
		mySize = 0;
		myData = nullptr;
	}
	Array(size_t size) :mySize(size), myData(new char[(size + 7) / 8]) {}
	Array(Array const& A) : mySize(A.mySize), myData(new char[(mySize + 7) / 8]) {
		for (size_t i = 0; i < (mySize + 7) / 8; i++)
			myData[i] = A.myData[i];
	}
	~Array() { //деструктор не изменится 
		delete[] myData;
	}
	Array<bool>& operator =(Array<bool> const& A) {
		if (myData) delete[] myData;
		mySize = A.mySize;
		myData = new char[(mySize + 7) / 8];
		for (size_t i = 0; i < (mySize + 7) / 8; i++)
			myData[i] = A.myData[i];
		return *this;
	}
	bool get(size_t i) {
		char temp = myData[i / 8];
		return (temp >> (i % 8)) % 2; // >> - битовый сдвиг т.е. 10011011 >> 1 = 01001101
	}
	void set(size_t i, bool value) {
		if ((i >= 0) && (i < mySize)) {
			if ((myData[i/8] >> (i % 8)) % 2 == value) return; // проверяем, не имеет ли этот бит уже нужное нам значение 
			unsigned char mask = 1 << (i % 8); // создаём маску с единицей на нужном нам месте, т.е. если i=3, mask=00001000
			if (value) myData[i/8] |= mask; // если нам необходимо значение true, то проводим логическое сложение маски и элемента массива myData 
			    else myData[i/8] &= ~mask; // если нам необходимо false, проводим логическое умножение с отрицанием маски (т.е. 11110111 для примера маски представленного выше)
		}
	}
	size_t size() const { //не изменится
		return mySize;
	}
};
int main() {
	Array<bool> C(10);
	for (size_t i = 0; i < 10; i++)
		C.set(i, i%2==1);
	for (size_t i = 0; i < 10; i++)
		std::cout << C.get(i) << ' ';
}                     //программа выведет: 
                      //0 1 0 1 0 1 0 1 0 1