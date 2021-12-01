#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

string filename = "result.log"; // имя файла, в который выводим результаты 
const int MY_SIZE = 1000; // размер массива
int* my_array = new int[MY_SIZE]; // массив
int iterator_for_array = 0; // итератор для масссива
int chunk_size = MY_SIZE / 10; // определяем размер кусочка данных
int counter = 0; // счётчик показывает, сколько элементов массива обработано
int num_of_prep = 1; // количество потоков подготовщиков 
int num_of_proc = 1; // количество потоков обработчиков
mutex mut_for_cout; // мьютекс для вывода кусочков 

class Timer // класс для измерения времени работы программы
{
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;
	chrono::time_point<clock_t> m_beg;
public:
	Timer() : m_beg(clock_t::now()){}
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

void array_initialization() // инициализация массива
{
	for (int i = 0; i < MY_SIZE; ++i)
	{
		my_array[i] = i;
	}
}
struct data_chunk // структура для кусочка данных
{
	int* data;
	int size = 0;
	data_chunk(int* some_data, int i, int j) // копирует элементы массива с i-ого по (j - 1)-й
	{
		size = j - i;
		data = new int[size];
		int num = i;
		for (int n = 0; n < size; ++n)
		{
			data[n] = some_data[num];
			++num;
		}
	}
	data_chunk(const data_chunk &chunk)
	{
		size = chunk.size;
		data = new int[size];
		for (int i = 0; i < chunk.size; ++i)
		{
			data[i] = chunk.data[i];
		}
	}
};
bool more_data_to_prepare() // функция, проверяющая остались ли ещё данные  
{
	return (iterator_for_array < MY_SIZE);
}
data_chunk prepare_data() // функция подготовки данных 
{
	data_chunk chunk(my_array, iterator_for_array, iterator_for_array + chunk_size);
	iterator_for_array += chunk_size;
	return chunk;
}
void process(data_chunk &data) // функция обработки данных
{
	for (int i = 0; i < chunk_size; ++i)
	{
		data.data[i] *= 100;
	}
	mut_for_cout.lock();
	ofstream fout(filename, ofstream::app);
	fout << data.data[0] << endl;       // будем выводить только первый элемент кусочка данных, чтобы понимать, 
	for (int i = 0; i < data.size; ++i) // в каком порядке массив выводиться, но не захламлять вывод тысячей элементов 
	{
		++counter;
	}
	fout << endl;
	fout.close();
	mut_for_cout.unlock();
}
bool is_last_chunk() // возвращает, последний ли это кусочек данных
{
	if (counter > MY_SIZE - chunk_size)
		return true;
	else return false;
}

mutex mut; // мьютекс
queue<data_chunk> data_queue; // очередь данных
condition_variable cond_var; // условная переменная

void data_preparation_thread() // функция, подготавливающая данные к распараллеливанию 
{
	while (more_data_to_prepare()) // цикл работает пока ещё есть данные, которые надо обработать
	{
		data_chunk const data = prepare_data(); // запихиваем в переменную первый кусок данных 
		lock_guard<mutex> lk(mut); 
		data_queue.push(data);
		cond_var.notify_one();
	}
}

void data_processing_thread() // функция, распределяющая обработку по потокам 
{
	while (true)
	{
		unique_lock<mutex> lk(mut);
		cond_var.wait(lk, [] {return !data_queue.empty(); });
		data_chunk data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		process(data);
		if (is_last_chunk())
		break;
	}
}

int main()
{
	ofstream fout(filename, ofstream::app);
	fout << "Array Size: " << MY_SIZE << endl;
	fout << "Number of Prepare Threads: " << num_of_prep << endl;
	fout << "Number of Process Threads: " << num_of_proc << endl;
	fout << "Result:" << endl;
	array_initialization();
	Timer t; // начинаем считать время обработки массива
	thread* preparation_thread = new thread[num_of_prep];
	thread* processing_thread = new thread[num_of_proc];
	for (int i = 0; i < num_of_prep; i++)
	{
		preparation_thread[i] = thread(data_preparation_thread);
	}
	for (int i = 0; i < num_of_proc; i++)
	{
		processing_thread[i] = thread(data_processing_thread);
	}

	for (int i = 0; i < num_of_prep; i++)
	{
		preparation_thread[i].join();
	}
	for (int i = 0; i < num_of_proc; i++)
	{
		processing_thread[i].join();
	}
	fout << "Time elapsed: " << t.elapsed() << endl ;
	fout << "-------------------------------------------------------------" << endl << endl;
	return 0;
}