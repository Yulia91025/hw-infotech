#include <iostream>
void comp(long long a, long long b){
if (a>b) std::cout<<a<<">"<<b;
else if (a<b) std::cout<<a<<"<"<<b;
else std::cout<<a<<"="<<b;
}