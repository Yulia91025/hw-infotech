#include <iostream>
#include <chrono>
#include <thread>
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

void work_with_array(int arr[], const int n)
{
	for (int i = 0; i < n; i++) // инициализируем массив
	{
		arr[i] = n - i;
	}

	int buff = 0; // сортировка пузырьком
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				buff = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = buff;
			}
		}
	}
}

void print(int arr[], const int n)
{
	for (int i = 0; i < n; i++) // выводим массив
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	Timer t;
	int n = 100000;
	int num_of_arr = 20;
	int** array_of_arrays = new int* [num_of_arr];
	thread* array_of_threads = new thread[num_of_arr];
	for (int i = 0; i < num_of_arr; i++) // делаем массив массивов 
	{
		array_of_arrays[i] = new int[n];
	}

	for (int i = 0; i < num_of_arr; i++) // иницализируем потоки, сортируем массивы
	{
		array_of_threads[i] = thread(work_with_array, array_of_arrays[i], n);
	}

	for (int i = 0; i < num_of_arr; i++) // присоединяем потоки, выводим массивы
	{
		array_of_threads[i].join();
		print(array_of_arrays[i], n);
	}
	cout << "Time elapsed: " << t.elapsed(); // время примерно 477.852
	return 0;
}