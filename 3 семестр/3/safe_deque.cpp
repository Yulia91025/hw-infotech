#include <iostream>
#include <deque>
#include <mutex>
#include <initializer_list>
#include <thread>
using namespace std;
mutex deque_mutex;
class Safe_deque : public deque<int>
{
	deque<int> Deque;
public:
	Safe_deque(deque<int>& not_safe_deque)
	{
		for (int n : not_safe_deque)
		{
			Deque.push_back(n);
		}
	}
	bool empty() const
	{
		lock_guard<mutex> guard(deque_mutex);
		return Deque.empty();
	}
	size_t size() const
	{
		lock_guard<mutex> guard(deque_mutex);
		return Deque.size();
	}
	size_t max_size() const
	{
		lock_guard<mutex> guard(deque_mutex);
		return Deque.max_size();
	}
	void push_back(const int value)
	{
		lock_guard<mutex> guard(deque_mutex);
		Deque.push_back(value);
	}
	void push_front(const int value)
	{
		lock_guard<mutex> guard(deque_mutex);
		Deque.push_front(value);
	}
	int front()
	{
		lock_guard<mutex> guard(deque_mutex);
		return Deque.front();
	}
	int back()
	{
		lock_guard<mutex> guard(deque_mutex);
		Deque.back();
	}
	int& operator[] (int index)
	{
		lock_guard<mutex> guard(deque_mutex);
		return Deque[index];
	}
	const int& operator[] (int index) const
	{
		lock_guard<mutex> guard(deque_mutex);
		return Deque[index];
	}
};

void work_with_deque(deque<int>& Deque, int n)
{
	Deque.push_back(n);
}

void work_with_safe_deque(Safe_deque &Deque, int n)
{
	Deque.push_back(n);
}

int main()
{
	deque<int> not_safe_deque = {0}; // создаём обычный дек
	Safe_deque safe_deque(not_safe_deque); // создаём потокобезопасный дек
	thread* array_of_threads = new thread[5]; // создаем массив потоков
	int counter = 0;
	for (int i = 0; i < 10; i++)
	{
		if ((i + 1) % 2 == 0)
		{
			array_of_threads[counter] = thread(work_with_deque, ref(not_safe_deque), i); // инициализируем потоки функцией с обычным деком
			counter++;
		}
	}
	for (int i = 0; i < counter; ++i) // присоединяем все потоки 
	{
		array_of_threads[i].join();
	}
	for (int i = 0; i < not_safe_deque.size(); ++i) // выводим обычный дек
		cout << "not safe deque " << not_safe_deque[i] << endl;
	thread* array_of_threads_2 = new thread[5]; // создаем ещё один массив потоков
	counter = 0;
	for (int i = 0; i < 10; i++)
	{
		if ((i + 1) % 2 == 0)
		{
			array_of_threads_2[counter] = thread(work_with_safe_deque, ref(safe_deque), i); // инициализируем потоки функцией с потокобезопасным деком
			counter++;
		}
	}
	for (int i = 0; i < counter; ++i) // присоединяем потоки
	{
		array_of_threads_2[i].join();
	}
	for (int i = 0; i < safe_deque.size(); ++i) // выводим потокобезопасный дек
		cout << "safe deque " << safe_deque[i] << endl;
	return 0;
}