#include <iostream>
#include <math.h>
#include <clocale>
#include "omp.h"
#include <chrono>
using namespace std;
class Timer // класс для измерения времени работы программы
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};
typedef double(*pointFunc)(double); // pointFunc - тип для указателей на функции, принимающие и возвращающие значения типа double
double f(double x) // функция, от которой хотим вычислить интеграл
{
    return (10 - x);
}
double simpson_integral(pointFunc f, double a, double b, int n)
{
    const double h = (b - a) / n; // величина шага
    double k1 = 0, k2 = 0;
#pragma omp parallel for reduction(+:k1,k2)
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
    Timer t;
    s1 = simpson_integral(f, a, b, n); //первое приближение для интеграла
    do
    {
        s = s1;     //второе приближение
        n = 2 * n;  //увеличение числа шагов в два раза,
                    //т.е. уменьшение размера шага в два раза
        s1 = simpson_integral(f, a, b, n);
    } while (fabs(s1 - s) > eps);  //сравнение приближений с заданной точностью
    cout << "\nИнтеграл = " << s1 << endl;
    cout << "Время вычисления интеграла: " << t.elapsed() << endl;
    cout << "Введите любой символ, для завершения работы программы...";
	char symbol;
    cin >> symbol;
    return 0;
}