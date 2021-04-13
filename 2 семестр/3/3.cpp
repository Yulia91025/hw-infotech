#include <iostream>;
#include "Aclass.h"
using namespace std;


int main() {
	int x,y,t,z;
	std::cin >> x >> y >> t >> z;
	A example(x,y,t,z);
	std::cout<<example.get_a()<<" "<< example.get_b() << " "<<example.get_c() << " "<<example.get_d() << "\n";
	std::cin >> x >> y >> t >> z;
	example.put_a(x);
	example.put_b(y);
	example.put_c(t);
	example.put_d(z);
	std::cout << example.get_a() << " " << example.get_b() << " " << example.get_c() << " " << example.get_d() << "\n";
}
