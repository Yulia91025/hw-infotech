#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Heap {
	size_t MAX_SIZE = 100;
	T* h;
	int Size;
public:
	Heap() {
		h = new T[MAX_SIZE];
		Size = 0;
	}
	~Heap() {
		delete[] h;
	}
	void push(T n) {
		int i, parent;
		i = Size;
		h[i] = n;
		parent = (i - 1) / 2;
		while (parent >= 0 && i > 0) {
			if (h[i] > h[parent]) {
				T temp = h[i];
				h[i] = h[parent];
				h[parent] = temp;
			}
			i = parent;
			parent = (i - 1) / 2;
		}
		Size++;
	}
	void print() {
		int i = 0;
		int k = 1;
		while (i < Size) {
			while ((i < k) && (i < Size)) {
				std::cout << h[i] << " ";
				i++;
			}
			std::cout << endl;
			k = k * 2 + 1;
		}
		std::cout << endl;
	}
	void print_array() {
		for (int i = 0; i < Size; i++) {
			std::cout << h[i] << " ";
		}
		std::cout << endl << endl;
	}
	T pop() {
		T x;
		x = h[0];
		h[0] = h[Size - 1];
		Size--;
		heapsort(0);
		return x;
	}
	void heapsort(int i) {
		int left, right;
		T temp;
		left = 2 * i + 1;
		right = 2 * i + 2;
		if (left < Size) {
			if (h[i] < h[left]) {
				temp = h[i];
				h[i] = h[left];
				h[left] = temp;
				heapsort(left);
			}
		}
		if (right < Size) {
			if (h[i] < h[right]) {
				temp = h[i];
				h[i] = h[right];
				h[right] = temp;
				heapsort(right);
			}
		}
	}
};

int main() {
	Heap<int> H;
	H.push(13);
	H.push(5);
	H.push(2);
	H.push(3);
	H.push(7);
	H.push(87);
	H.push(4);
	H.push(10);
	H.print();
	std::cout << "max=" << H.pop() << endl;
	std::cout << "max=" << H.pop() << endl;
	H.print_array();
}