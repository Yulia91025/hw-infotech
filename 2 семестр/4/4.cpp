#include <iostream>
#include <cmath>
using namespace std;
class Complex {
    double x, y;
public:
    Complex() {
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
        std::cout << endl << "Re(z)=";
        std::cin >> a;
        try{
            if (a>10000000000000000000)
                throw "Too big number!\n";
            x = a;
        }
        catch (const char* e) {
            std::cerr << e;
        }
        std::cout << endl << "Im(z)=";
        std::cin >> b;
        try {
            if (a > 10000000000000000000)
                throw "Too big number!\n";
            y = b;
        }
        catch (const char* e) {
            std::cerr << e;
        }
        std::cout << endl;
    }
    void out() {
        if (y > 0) {
            if (y != 1) std::cout << x << '+' << y << "*i" << ' ';
            else std::cout << x << '+' << "i" << ' ';
        }
        else if (y < 0) {
            if (y != -1) std::cout << x << y << "*i" << ' ';
            else std::cout << x << '-' << "i" << ' ';
        }
        else std::cout << x << ' ';
        std::cout << std::endl;
    }
    Complex operator + (const Complex& A) {
        return Complex(x + A.x, y + A.y);
    }
    Complex operator - (const Complex& A) {
        return Complex(x - A.x, y - A.y);
    }
    Complex operator * (const Complex& A) {
        return Complex(x * A.x - y * A.y, x * A.y + y * A.x);
    }
    Complex operator / (const Complex& A) {
        try {
            if ((A.x * A.x + A.y * A.y) == 0)
                throw "The divisor is 0!\n";
        }
        catch (const char* e) {
            std::cerr << e;
        }
        return Complex((x * A.x + y * A.y) / (A.x * A.x + A.y * A.y), (y * A.x - x * A.y) / (A.x * A.x + A.y * A.y));
    }
    double abs() {
        return sqrt(x * x + y * y);
    }
    Complex conj() {
        try {
            if (y == 0)
                throw "The number is real!\n";
        }
        catch (const char* e) {
            std::cout << e;
        }
        Complex C(x, -y);
        return C;
    }
    friend void comp(Complex A, Complex B);
};

void comp(Complex A, Complex B) {
    if (A.abs() > B.abs())
    {
        A.out(); std::cout << ">" << ' '; B.out(); std::cout << endl;
    }
    else if (A.abs() < B.abs())
    {
        A.out(); std::cout << "<" << ' '; B.out(); std::cout << endl;
    }
    else { A.out(); std::cout << "=" << ' '; B.out(); std::cout << endl; }
}
int main() {
    Complex A;
    A.in();
    A.out();
    Complex B;
    A / B;
    B.in();
    B.conj();
}
