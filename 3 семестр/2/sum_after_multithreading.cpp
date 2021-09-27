#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <algorithm>
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

struct sum_block
{
	void operator()(long long first, long long last, long long& result)
	{
		result = sum(first, last, result);
	}
};

long long parallel_sum(long long begin, long long end, long long init)
{
	unsigned long const length = end - begin + 1;
	if (!length) return init;
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
	unsigned long const hardware_threads = thread::hardware_concurrency();
	unsigned long const num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	unsigned long const block_size = length / num_threads;
	vector<long long> results(num_threads);
	vector<thread> threads(num_threads - 1);
	long long block_start = begin;
	for (unsigned long i = 0; i < (num_threads - 1); ++i)
	{
		long long block_end = block_start;
		for (unsigned long i = 0; i < block_size - 1; ++i) // замена для advance 
		{
			++block_end;
		}
		//advance(block_end, block_size); //из-за этой функции у меня возникали довольно странные ошибки, так и не поняла почему
		threads[i] = thread(sum_block(), block_start, block_end, ref(results[i]));
		block_start = block_end + 1;
	}
	sum_block()(block_start, end, results[num_threads - 1]);
	for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
	for (unsigned long i = 0; i < num_threads; ++i) // суммируем все результаты из потоков, чтобы найти общую сумму
	{
		init += results[i];
	}
	return init;
}

int main() {
	Timer t;
	long long n = 1000000000;
	long long res = 0;
	res = parallel_sum(1, n, res);
	cout << res << endl;
	cout << "Time elapsed: " << t.elapsed(); // время примерно 7 секунд
	return 0;
}