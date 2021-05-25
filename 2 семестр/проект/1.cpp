#include <iostream>
using namespace std;
int sum(int a, int b) {
	return a + b;
}
int main() {
	int a = 5,b=3;
	std::cout << sum(a, b)<<' ';
	double x = 5.5, y = 3.5;
	std::cout << sum(x,y)<<' '; 
} //оба раза программа выведет 8, хотя во втором случае ответ 9