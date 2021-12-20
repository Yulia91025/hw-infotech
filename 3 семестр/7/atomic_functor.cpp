#include <iostream>
#include <atomic>
#include <thread>
using namespace std;

void f1() 
{
	cout << "f1\n";
}

atomic<bool> operation_done(true);
int counter = 0;

struct Functor
{
	void operator() (void f()) 
	{
		bool flag = 0;
		while (!flag)
		{
			if (operation_done.load())
			{
				operation_done = false;
				cout << "Functor\n";
				cout << counter << endl;
				++counter;
				f();
				operation_done = true;
				flag = true;
			}
			else
			{
				this_thread::sleep_for(chrono::seconds(3));
			}
		}
	}
};


int main()
{
	Functor f;
	thread t[10];
	for (int i = 0; i < 10; ++i)
	{
		t[i] = thread(f, f1);
	}
	for (int i = 0; i < 10; ++i)
	{
		t[i].join();
	}
	return 0;
}