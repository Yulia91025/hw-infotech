#include <iostream>
#include <future>
#include <set>
#include <queue>
#include <thread>
using namespace std;

struct data_packet
{
	static int id;
	int* data;
	int* payload;
	promise<int*> promise;
	data_packet(){}
	data_packet(int n)
	{
		data = new int[n];
		payload = new int[n - 2];
		data[0] = 0;
		data[n - 1] = 0;
		for (int i = 0; i < n - 2; ++i)
		{
			data[i + 1] = id;
			payload[i] = id;
		}
		++id;
		for (int i = 0; i < n; ++i)
		{
			cout << data[i] << " ";
		}
	}
	data_packet(const data_packet& packet)
	{
		data = new int[sizeof(packet.data)];
		payload = new int[sizeof(packet.payload)];
		data[0] = 0;
		data[sizeof(packet.data) - 1] = 0;
		for (int i = 0; i < sizeof(packet.data) - 2; ++i)
		{
			data[i + 1] = packet.data[i + 1];
			payload[i] = packet.payload[i];
		}
		for (int i = 0; i < sizeof(packet.data); ++i)
		{
			cout << data[i] << " ";
		}
	}
};

int data_packet::id = 1;

struct outgoing_packet: data_packet
{
	outgoing_packet(){}
	outgoing_packet(const outgoing_packet& packet)
	{
		data = new int[sizeof(packet.data)];
		payload = new int[sizeof(packet.payload)];
		data[0] = 0;
		data[sizeof(packet.data) - 1] = 0;
		for (int i = 0; i < sizeof(packet.data) - 2; ++i)
		{
			data[i + 1] = packet.data[i + 1];
			payload[i] = packet.payload[i];
		}
		for (int i = 0; i < sizeof(packet.data); ++i)
		{
			cout << data[i] << " ";
		}
	}
	outgoing_packet& operator=(data_packet& packet)
	{
		data = new int[sizeof(packet.data)];
		payload = new int[sizeof(packet.payload)];
		data[0] = 0;
		data[sizeof(packet.data) - 1] = 0;
		for (int i = 0; i < sizeof(packet.data) - 2; ++i)
		{
			data[i + 1] = packet.data[i + 1];
			payload[i] = packet.payload[i];
		}
		for (int i = 0; i < sizeof(packet.data); ++i)
		{
			cout << data[i] << " ";
		}
		return *this;
	}
};

queue<data_packet> data_queue;

struct connection
{
	bool flag; //флаг, показывающий, есть ли входящие данные 
	connection(bool f):flag(f){}

	bool has_incoming_data() const // возвращает есть ли входящие данные 
	{
		return flag;
	}
	bool has_outgoing_data() const // возвращает есть ли исходящие данные 
	{
		return !data_queue.empty();
	}
	data_packet incoming() const
	{
		cout << "Enter number for incoming data:" << endl;
		int num;
		cin >> num;
		data_packet data(num);
		data_queue.push(data);
		return data;
	}
	/*promise<int*>& get_promise(int id) const
	{
	}*/
	outgoing_packet& top_of_outgoing_queue() const
	{
		outgoing_packet temp;
		temp = data_queue.front();
		data_queue.pop();
		return temp;
	}
	void send(int* payload) const
	{
		for (int i = 0; i < sizeof(payload); ++i)
		{
			cout << payload[i] << " ";
		}
		cout << endl;
	}
};


typedef set<connection> connection_set;
typedef set<connection>::iterator connection_iterator;

bool done(connection_set connections)
{
	cout << "Connection set still working?\n";
	bool ans;
	cin >> ans;
	return !ans;
}

void process_connections(connection_set& connections)
{
	while (!done(connections))
	{
		for (auto connection = connections.begin(), end = connections.end(); connection != end; ++connection)
		{
			if (connection->has_incoming_data())
			{
				data_packet data = connection->incoming();
				promise<int*>& p = data.promise;
				p.set_value(data.payload);
			}
			if (connection->has_outgoing_data())
			{
				outgoing_packet data = connection->top_of_outgoing_queue();
				connection->send(data.payload);
				//data.promise.set_value(true);
			}
		}
	}
}

int main()
{
	connection conn1(1);
	connection conn2(0);
	connection_set MySet;
	MySet.insert(conn1);
	MySet.insert(conn2);
	thread mythread = thread(process_connections, MySet);
	return 0;
};