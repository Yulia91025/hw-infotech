#include <iostream>
#include <cmath>
using namespace std;

class Complex {
    double x, y;
public:
    Complex(){
        x = 0;
        y = 0;
    }
    Complex(double a) {
        x = a;
        y = 0;
    }
    Complex(double a, double b) {
        x = a;
        y = b;
    }
    ~Complex() {}
    void in() {
        double a, b;
        std::cout <<endl<< "Re(z)=";
        std::cin >> a;
        std::cout <<endl<< "Im(z)=";
        std::cin >> b;
        x = a;
        y = b;
        std::cout << endl;
    }
    void out() {
        if (y > 0) {if(y!=1) std::cout << x << '+' << y << "*i" <<' '; 
                   else std::cout << x << '+' << "i" << ' ';}
        else if (y < 0) {if (y!=-1) std::cout << x << y << "*i" << ' ';
                         else std::cout << x << '-' << "i" << ' ';}
        else std::cout << x <<' ';
    }
    Complex operator + (const Complex& A){
        return Complex(x + A.x, y+A.y);
    }
    Complex operator - (const Complex& A){
        return Complex(x - A.x, y - A.y);
    }
    Complex operator * (const Complex& A){
        return Complex(x*A.x-y*A.y, x*A.y + y*A.x);
    }
    Complex operator / (const Complex& A){
        return Complex((x * A.x + y * A.y)/(A.x*A.x+A.y*A.y), (  y * A.x- x * A.y)/ (A.x * A.x + A.y * A.y));
    }
    double abs() {
        return sqrt(x*x+y*y);
    }
    Complex conj() {
        Complex C(x, -y);
        return C;
    }
    friend void comp(Complex A, Complex B);
};

void comp(Complex A, Complex B) {
    if (A.abs() > B.abs()) 
            { A.out(); std::cout << ">"<<' '; B.out(); std::cout << endl;}
             else if (A.abs() < B.abs()) 
                     { A.out(); std::cout << "<"<<' '; B.out(); std::cout << endl;}
                     else { A.out(); std::cout << "="<<' '; B.out(); std::cout << endl;}
}

int main(){
    Complex A(0,0),C(0,0),B(0,0);
    A.in();
    A.out();
    B.in();
    B.out();
    C.in();
    C.out();
    std::cout << endl;
    std::cout << A.abs()<<endl;
    A.conj().out();
    std::cout << endl;
    A = B + C;
    A.out();
    std::cout << endl;
    A= B-A;
    A.out();
    std::cout << endl;
    B = B * C;
    B.out();
    std::cout << endl;
    B = B / C;
    B.out();
    std::cout << endl;
    comp(A, B);
}