#include <iostream>
#include "Array.h"
#include "templates.cpp"
using namespace std;
int main() {
	Array<int> A(10);
	Array<int> X;
	for (size_t i = 0; i < 10; i++)
		A.set(i, i);
	X = A;
	for (size_t i = 0; i < X.size(); i++)
		std::cout << X.get(i) << ' ';
	std::cout << '\n';
	Array<double> B(5);
	for (size_t i = 0; i < 5; i++)
		B.set(i, i + 0.03);
	for (size_t i = 0; i < B.size(); i++)
		std::cout << B.get(i) << ' ';
	std::cout << '\n';
	Array<char> D(10);
	for (size_t i = 0; i < 10; i++)
		D.set(i, i+97);
	for (size_t i = 0; i < 10; i++)
		std::cout << D.get(i) << ' ';
	std::cout << '\n';
	Array<Array<int>> Y(2);
	Y.set(0, A);
	Y.set(1, X);
	for (size_t i = 0; i < 2; i++)
		std::cout << Y.get(i);
}