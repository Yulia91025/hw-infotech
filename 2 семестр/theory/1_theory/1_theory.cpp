#include <iostream>;
using namespace std;
struct Cycle {
public: int* data;
	  size_t size;
	  Cycle(size_t N) {
		  size = N;
		  data = new int[size];
	  }
	  ~Cycle() {
		  delete[]data;
	  }
	  Cycle(Cycle& A) {
		  size = A.size;
		  data = new int[size];
		  for (int i = 0; i < size; i++) {
			  data[i] = A.data[i];
		  }
	  }
	  Cycle& operator =(const Cycle& A) {
		  if (data) { delete[]data; }
		  size = A.size;
		  data = new int[size];
		  for (int i = 0; i < size; i++) {
			  data[i] = A.data[i];
		  }
		  return*this;
	  }
	  int operator[](int i) {
		  return data[i % size];
	  }
	  void setC(int i, int value) { data[i] = value; }
};

int main() {
	int n, a;
	std::cin >> n;
	Cycle A(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a;
		A.setC(i, a);
	}
	std::cin >> n;
	std::cout<<A[n];
}