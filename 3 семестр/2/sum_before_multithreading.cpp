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

long long sum(long long first, long long last, long long& result) // функция для нахождения суммы 
{
	for (long long i = first; i < last + 1; ++i)
	{
		result += i;
	}
	return result;
}

int main() {
	Timer t;
	long long n = 1000000000;
	long long res = 0;
	res = sum(1, n, res);
	cout << res << endl;
	cout << "Time elapsed: " << t.elapsed(); // время примерно 4 секунды
	return 0;
}