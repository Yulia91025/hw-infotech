#include <iostream>
using namespace std;
class AoA {
	size_t m;
	int** A;
	int* data;
public:
	AoA(int* Array_k, size_t m);
	~AoA();
	AoA(const AoA& X);
	int get(size_t i, size_t j);
	void set(size_t i, size_t j, int x);
};

AoA::AoA(int* Array_k, size_t m) :m(m), A(new int*[m]) {
	size_t size=0;
	for (int i = 0; i < m; i++) size += Array_k[i];
	data = new int[size];
	int temp = 0;
	for (int i = 0; i < m; i++) {
		A[i] = data + temp;
		temp += Array_k[i];
	}
}

AoA::~AoA(){
	for (int i = 0; i < m; i++) {
		delete[] A[i];
	}
	delete[] A;
	delete[] data;
}

int AoA::get(size_t i, size_t j) {
	if (i >= m) throw "Out of m";
	if (j >= (size_t)(A[i] - A[i + 1])) throw "Out of k[i]";
	return A[i][j];
}

void AoA::set(size_t i, size_t j, int x) {
	if (i >= m) throw "Out of m";
	if (j >= (size_t)(A[i] - A[i + 1])) throw "Out of k[i]";
	A[i][j]=x;
}

int main(){
	size_t m;
	int x;
	std::cin >> m;
	int*k = new int[m];
	for (int i = 0; i < m; i++) {
		std::cin >> k[i];
	}
	AoA A(k,m);
	for (int i = 0; i < m; i++) {
		std::cout << "array number "<<i<<endl;
		for (int j = 0; j < k[i]; j++) {
			std::cin >> x;
			A.set(i, j, x);
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k[i]; j++) {
			std::cout << A.get(i, j)<<" ";
		}
		std::cout<<endl;
	}
}