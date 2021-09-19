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

void bubbleSort(int arrForSort[], const int SIZE)
{
	int buff = 0;
	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = SIZE - 1; j > i; j--)
		{
			if (arrForSort[j] < arrForSort[j - 1])
			{
				buff = arrForSort[j - 1];
				arrForSort[j - 1] = arrForSort[j];
				arrForSort[j] = buff;
			}
		}
	}
}

int main() {
	
	Timer t;
	int n = 1000;
	int* m_1;
	m_1 = new int[n];
	int* m_2;
	m_2 = new int[n];
	for (int i = 0; i < n; i++) // инициализируем первый массив
	{
		m_1[i] = n - i;
	}
	int a = -2;
	for (int i = 0; i < n; i++) // инициализируем второй массив
	{
		m_2[i] = i + n + a;
		a++;
		a = -a;
	}

	thread my_thread(bubbleSort,m_1, n); // создаем поток, сортируем первый массив
	
	bubbleSort(m_2, n); // сортируем второй массив
	
	my_thread.join(); // присоединям поток обратно к основному

	for (int i = 0; i < n; i++) // выводим первый массив
	{
		cout << m_1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < n; i++) // выводим второй массив
	{
		cout << m_2[i] << " ";
	}
	cout << endl;
	cout << "Time elapsed: " << t.elapsed(); // время примерно 0.392
	return 0;
}