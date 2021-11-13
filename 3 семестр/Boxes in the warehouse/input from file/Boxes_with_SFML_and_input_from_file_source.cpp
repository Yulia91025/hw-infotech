#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Parallelepiped // класс для параллелепипедов 
{
public:
	int a, b, c;
	Parallelepiped(int x, int y, int z) :a(x), b(y), c(z) {}
	Parallelepiped()
	{
		a = 0;
		b = 0;
		c = 0;
	}
	~Parallelepiped() {}

};

class Warehouse : public Parallelepiped // класс для склада
{
public:
	int*** array;
	Warehouse(int x, int y, int z)
	{
		this->a = x;
		this->b = y;
		this->c = z;
		array = new int** [a];
		for (int i = 0; i < a; ++i)
		{
			array[i] = new int* [b];
			for (int j = 0; j < b; ++j)
			{
				array[i][j] = new int[c];
			}
		}
		for (int i = 0; i < a; ++i)
		{
			for (int j = 0; j < b; ++j)
			{
				for (int k = 0; k < c; ++k)
				{
					array[i][j][k] = 0;
				}
			}
		}
	}
	~Warehouse()
	{
		for (int i = 0; i < a; ++i)
		{
			for (int j = 0; j < b; ++j)
			{
				delete[] array[i][j];
			}
		}
		for (int i = 0; i < a; ++i)
		{
			delete[] array[i];
		}
		delete[] array;
	}
	void clear_array()
	{
		for (int i = 0; i < a; ++i)
		{
			for (int j = 0; j < b; ++j)
			{
				for (int k = 0; k < c; ++k)
				{
					array[i][j][k] = 0;
				}
			}
		}
	}
	void print()
	{
		cout << "X Y" << endl; // выводим "слои" по оси апликат
		for (int i = 0; i < c; ++i)
		{
			cout << "Z = " << i + 1 << endl;
			for (int j = 0; j < a; ++j)
			{
				for (int k = 0; k < b; ++k)
				{
					cout << array[j][k][i] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}

		cout << "Y Z" << endl; // выводим "слои" по оси абсцисс
		for (int i = 0; i < a; ++i)
		{
			cout << "X = " << i + 1 << endl;
			for (int k = c - 1; k > -1; --k)
			{
				for (int j = 0; j < b; ++j)
				{
					cout << array[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << "X Z" << endl; // выводим "слои" по оси ординат
		for (int i = 0; i < b; ++i)
		{
			cout << "Y = " << i + 1 << endl;
			for (int k = c - 1; k > -1; --k)
			{
				for (int j = a - 1; j > -1; --j)
				{
					cout << array[j][i][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	void print_w()
	{
		int coeff = 150;
		if (a > 6 || b > 6 || c > 6)
		{
			if (a > b)
			{
				if (a > c) coeff = 1000 / a;
				else  coeff = 1000 / c;
			}
			else
			{
				if (b > c) coeff = 1000 / b;
				else  coeff = 1000 / c;
			}
		}
		RenderWindow window_z(VideoMode(b * coeff, a * coeff), "Warehouse X Y"); //выводим слои по Z
		RectangleShape* Rectangles_z = new RectangleShape[a * b];
		int k = 0;
		while (window_z.isOpen())
		{
			Event event;
			while (window_z.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window_z.close();
				if (event.type == Event::MouseButtonPressed)
				{
					if (k < c - 1) ++k;
					else window_z.close();
				}
			}
			window_z.clear();
			int counter = 0;
			for (int i = 0; i < a; ++i)
			{
				for (int j = 0; j < b; ++j)
				{
					if (array[i][j][k] != 0)
					{
						Rectangles_z[counter].setSize(Vector2f(coeff, coeff));
						int R, G, B;
						R = array[i][j][k] * 2210 % 255;
						G = array[i][j][k] * 1500 % 255;
						B = array[i][j][k] * 400 % 255;
						Color color(R, G, B);
						Rectangles_z[counter].setFillColor(color);
						Rectangles_z[counter].setPosition(j * coeff, i * coeff);
					}
					else
					{
						Rectangles_z[counter].setSize(Vector2f(0, 0));
					}
					++counter;
				}
			}
			for (int n = 0; n < a * b; ++n)
			{
				window_z.draw(Rectangles_z[n]);
			}
			window_z.display();
		}

		RenderWindow window_x(VideoMode(b * coeff, c * coeff), "Warehouse Y Z"); //выводим слои по X
		RectangleShape* Rectangles_x = new RectangleShape[c * b];
		int i = 0;
		while (window_x.isOpen())
		{
			Event event;
			while (window_x.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window_x.close();
				if (event.type == Event::MouseButtonPressed)
				{
					if (i < a - 1) ++i;
					else window_x.close();
				}
			}
			window_x.clear();
			int counter = 0;
			for (int k = 0; k < c; ++k)
			{
				for (int j = 0; j < b; ++j)
				{
					if (array[i][j][k] != 0)
					{
						Rectangles_x[counter].setSize(Vector2f(coeff, coeff));
						int R, G, B;
						R = array[i][j][k] * 2210 % 255;
						G = array[i][j][k] * 1500 % 255;
						B = array[i][j][k] * 400 % 255;
						Color color(R, G, B);
						Rectangles_x[counter].setFillColor(color);
						Rectangles_x[counter].setPosition(j * coeff, (c - k - 1) * coeff);
					}
					else
					{
						Rectangles_x[counter].setSize(Vector2f(0, 0));
					}
					++counter;
				}
			}
			for (int n = 0; n < c * b; ++n)
			{
				window_x.draw(Rectangles_x[n]);
			}
			window_x.display();
		}

		RenderWindow window_y(VideoMode(a * coeff, c * coeff), "Warehouse X Z"); //выводим слои по Y
		RectangleShape* Rectangles_y = new RectangleShape[c * a];
		int j = 0;
		while (window_y.isOpen())
		{
			Event event;
			while (window_y.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window_y.close();
				if (event.type == Event::MouseButtonPressed)
				{
					if (j < b - 1) ++j;
					else window_y.close();
				}
			}
			window_y.clear();
			int counter = 0;
			for (int k = 0; k < c; ++k)
			{
				for (int i = 0; i < a; ++i)
				{
					if (array[i][j][k] != 0)
					{
						Rectangles_y[counter].setSize(Vector2f(coeff, coeff));
						int R, G, B;
						R = array[i][j][k] * 2210 % 255;
						G = array[i][j][k] * 1500 % 255;
						B = array[i][j][k] * 400 % 255;
						Color color(R, G, B);
						Rectangles_y[counter].setFillColor(color);
						Rectangles_y[counter].setPosition((a - i - 1) * coeff, (c - k - 1) * coeff);
					}
					else
					{
						Rectangles_y[counter].setSize(Vector2f(0, 0));
					}
					++counter;
				}
			}
			for (int n = 0; n < c * a; ++n)
			{
				window_y.draw(Rectangles_y[n]);
			}
			window_y.display();
		}
	}
	bool is_boxes_can_fit(vector<Parallelepiped> Boxes, int num_of_boxes) // метод для проверки, не превосходят ли размеры ящиков размеров склада
	{
		int volume_of_all_boxes = 0;
		for (int i = 0; i < num_of_boxes; ++i)
		{
			if ((Boxes[i].a > a) || (Boxes[i].b > b) || (Boxes[i].c > c)) return false;
			volume_of_all_boxes += Boxes[i].a * Boxes[i].b * Boxes[i].c;
		}
		if (volume_of_all_boxes > a * b * c) return false;
		return true;
	}
	bool is_volume_free(int x, int y, int z, Parallelepiped Box) // метод проверки, свободно ли нужное под ящик пространство начиная от точки (x, y, z)
	{
		int volume = Box.a * Box.b * Box.c;
		int counter = 0;
		for (int i = x; (i < Box.a + x) && (i < a); ++i)
		{
			for (int j = y; (j < Box.b + y) && (j < b); ++j)
			{
				for (int k = z; (k < Box.c + z) && (k < c); ++k)
				{
					if (array[i][j][k] == 0) ++counter;
				}
			}
		}
		return counter == volume;
	}
	void place_one_box(int x, int y, int z, Parallelepiped Box, int this_box_number) // размещаем одну коробку от заданной точки
	{
		for (int i = x; i < Box.a + x; ++i)
		{
			for (int j = y; j < Box.b + y; ++j)
			{
				for (int k = z; k < Box.c + z; ++k)
				{
					array[i][j][k] = this_box_number + 1;
				}
			}
		}
	}
	bool place_this_box(Parallelepiped Box, int curr_num) // пытаемся разместить одну конкретную заданную коробку
	{
		for (int k = 0; k < c - 1; ++k)
		{
			for (int j = 0; j < b - 1; ++j)
			{
				for (int i = 0; i < a - 1; ++i)
				{
					if (array[i + 1][j][k] == 0) // если есть свободное место рядом, проверяем, поместится ли коробка от этой точки 
					{
						if (is_volume_free(i + 1, j, k, Box))
						{
							place_one_box(i + 1, j, k, Box, curr_num); // размещаем коробку, если она поместилась 
							return true;
						}
					}
					if (array[i][j + 1][k] == 0) // если есть свободное место рядом, проверяем, поместится ли коробка от этой точки 
					{
						if (is_volume_free(i, j + 1, k, Box))
						{
							place_one_box(i, j + 1, k, Box, curr_num); // размещаем коробку, если она поместилась 
							return true;
						}
					}
					if (array[i][j][k + 1] == 0) // если есть свободное место рядом, проверяем, поместится ли коробка от этой точки 
					{
						if (is_volume_free(i, j, k + 1, Box))
						{
							place_one_box(i, j, k + 1, Box, curr_num); // размещаем коробку, если она поместилась 
							return true;
						}
					}
				}
			}
		}
		for (int k = 0; k < c; ++k) // некоторые точки остались не рассмотрены - проверяем и их
		{
			if (array[a - 1][b - 1][k] == 0) // если есть свободное место рядом, проверяем, поместится ли коробка от этой точки 
			{
				if (is_volume_free(a - 1, b - 1, k, Box))
				{
					place_one_box(a - 1, b - 1, k, Box, curr_num); // размещаем коробку, если она поместилась 
					return true;
				}
			}
		}
		for (int i = 0; i < a - 1; ++i)
		{
			if (array[i][b - 1][c - 1] == 0) // если есть свободное место рядом, проверяем, поместится ли коробка от этой точки 
			{
				if (is_volume_free(i, b - 1, c - 1, Box))
				{
					place_one_box(i, b - 1, c - 1, Box, curr_num); // размещаем коробку, если она поместилась 
					return true;
				}
			}
		}
		for (int j = 0; j < b - 1; ++j)
		{
			if (array[a - 1][j][c - 1] == 0) // если есть свободное место рядом, проверяем, поместится ли коробка от этой точки 
			{
				if (is_volume_free(a - 1, j, c - 1, Box))
				{
					place_one_box(a - 1, j, c - 1, Box, curr_num); // размещаем коробку, если она поместилась 
					return true;
				}
			}
		}
		return false; // возвращаем 0, если не получилось разместить коробку  
	}
	bool is_larger(Parallelepiped Box_1, Parallelepiped Box_2, int side) //показывает, больше ли первая коробка второй по введённой стороне
	{
		bool res = 0;
		switch (side)
		{
		case 1:
			if (Box_1.a > Box_2.a) res = 1;
			break;
		case 2:
			if (Box_1.b > Box_2.b) res = 1;
			break;
		case 3:
			if (Box_1.c > Box_2.c) res = 1;
			break;
		default:
			cout << "Invalid number of side";
			break;
		}
		return res;
	}
	int* box_numbers_in_ascending_order(vector<Parallelepiped> Boxes, int num_of_boxes, int side) // возвращает указатель на массив с номерами коробок по убыванию нужной стороны 
	{
		int* arr_of_num = new int[num_of_boxes];
		for (int i = 0; i < num_of_boxes; ++i)
		{
			arr_of_num[i] = i;
		}
		for (int i = 0; i + 1 < num_of_boxes; ++i) {
			for (int j = 0; j + 1 < num_of_boxes - i; ++j) {
				if (is_larger(Boxes[arr_of_num[j + 1]], Boxes[arr_of_num[j]], side)) {
					swap(arr_of_num[j], arr_of_num[j + 1]);
				}
			}
		}
		return arr_of_num;
	}
	void place_boxes(vector<Parallelepiped> Boxes, int num_of_boxes) // метод размещения ящиков на складе 
	{
		if (is_boxes_can_fit(Boxes, num_of_boxes))
		{
			int side = 1; //1 - длина, 2 - ширина, 3 - высота 
			while (side < 4)
			{
				int* order_of_boxes;
				order_of_boxes = box_numbers_in_ascending_order(Boxes, num_of_boxes, side); // сортируем коробки по убыванию по стороне (side) 
				place_one_box(0, 0, 0, Boxes[order_of_boxes[0]], order_of_boxes[0]); // размещаем самую большую коробку
				int i = 1;
				bool flag = 1; // флаг, показывающий, что всё идёт хорошо и коробки размещаются 
				while (i < num_of_boxes && flag)
				{
					flag = place_this_box(Boxes[order_of_boxes[i]], order_of_boxes[i]); // если коробка разместиться, то флаг останется 1, а если нет, то обратиться в 0 
					++i;
				}
				if (!flag) // если хотя бы одна коробка не была размещена, то пытаемся разместить коробки в другом порядке 
				{
					clear_array();
					++side;
				}
				else break;
			}
			if (side == 4)
			{
				cout << "Boxes cannot be fit in warehouse!";
			}
			else
			{
				print();
				print_w();
			}
		}
		else cout << "One or more boxes are larger than the warehouse, or their volume larger than volume of the warehouse!\nBoxes cannot be fit in warehouse!"; // выводим уведомление о том, что ящики не помещаются на склад, если хотя бы у одного из них хоть одна величина больше, чем у склада
	}
};

int main()
{
	string filename; // имя файла
	cout << "Enter filename:" << endl;
	cin >> filename; // считываем имя файла
	ifstream file(filename);

	// Если мы не можем открыть файл для чтения его содержимого, то выводим сообщение об ошибке
	if (!file)
	{
		cerr << "This file could not be opened for reading!" << endl;
		char c;
		cout << "Please enter any symbol to complete program" << endl;
		cin >> c; // чтобы программа не закрывалась сразу после вывода ошибки
		return -1;
	}
	int x, y, z;
	file >> x >> y >> z; // считываем размеры склада
	Warehouse my_warehouse(x, y, z); // создаём склад 
	int num_of_boxes;
	file >> num_of_boxes; // считываем количество коробок
	if (num_of_boxes < 1)
	{
		cout << "No boxes";
		return 0;
	}
	vector<Parallelepiped> Boxes(num_of_boxes); // создаём вектор ящиков
	for (int i = 0; i < num_of_boxes; ++i) // записываем размеры ящиков
	{
		file >> Boxes[i].a >> Boxes[i].b >> Boxes[i].c;
	}
	my_warehouse.place_boxes(Boxes, num_of_boxes);
	file.close();
	return 0;
}