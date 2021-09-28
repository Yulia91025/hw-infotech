#include <iostream>
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

long long sum(int m, long long first, long long last, long long& result) // функция для нахождения суммы, где каждое слагаемое взято по модулю m
{
	for (long long i = first; i < last + 1; ++i)
	{
		result += i % m;
	}
	return result;
}

int main() {
	Timer t;
	long long n = 10000000000;
	int m = 7;
	long long res = 0;
	res = sum(m, 1, n, res);
	cout << res << endl;
	cout << "Time elapsed: " << t.elapsed(); // время примерно 140.14 секунд 
	return 0;
}
