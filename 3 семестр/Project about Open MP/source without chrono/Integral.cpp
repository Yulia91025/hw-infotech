#include <iostream>
#include <math.h>
#include <cmath>
#include <clocale>
using namespace std;
typedef double(*pointFunc)(double); // pointFunc - тип для указателей на функции, принимающие и возвращающие значения типа double
double f(double x) // функция, от которой хотим вычислить интеграл
{
    return (10 - x);
}
double simpson_integral(pointFunc f, double a, double b, int n) // интеграл Симпсона (приближаем значения параболами)
{
    const double h = (b - a) / n;
    double k1 = 0, k2 = 0;
    for (int i = 1; i < n; i += 2) 
    {
        k1 += f(a + i * h);
        k2 += f(a + (i + 1) * h);
    }
    return h / 3 * (f(a) + 4 * k1 + 2 * k2);
}
int main()
{
    setlocale(LC_ALL, "Russian");
    double a, b, eps;
    double s1, s;
    int n = 1; //начальное число шагов
    cout << "Введите левую границу интегрирования a = ";
    cin >> a;
    cout << "\nВведите правую границу интегрирования b = ";
    cin >> b;
    cout << "\nВведите требуемую точность eps = ";
    cin >> eps;
    s1 = simpson_integral(f, a, b, n); //первое приближение для интеграла
    do 
    {
        s = s1;     //второе приближение
        n = 2 * n;  //увеличение числа шагов в два раза,
                    //т.е. уменьшение значения шага в два раза
        s1 = simpson_integral(f, a, b, n);
    } while (fabs(s1 - s) > eps);  //сравнение приближений с заданной точностью
    cout << "\nИнтеграл = " << s1 << endl;
    return 0;
}