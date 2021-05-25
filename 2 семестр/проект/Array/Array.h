#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
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
		std::cout << '\n';
		return out;
	}
};
#endif