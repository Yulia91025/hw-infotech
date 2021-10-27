#include <iostream>
#include <future>
#include <string>
#include <windows.h>
using namespace std;
bool flag = true;
bool сan_go_to_university(int n) // вычисляет проходит ли человек с номером n по рейтинговым спискам 
{
	Sleep(10000);
	flag = false;
	if ((rand() % 100 + 200) > 260)
		return true;
	else return false;
}
bool consent_to_enrollment() // проверка согласия на зачисление
{
	cout << "Is enrollment consent attached?" << endl << "(Yes/No)" << endl;
	string answer;
	while (true)
	{
		cin >> answer;
		if (answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("YES") == 0)
		{
			return true;
		}
		else if (answer.compare("no") == 0 || answer.compare("No") == 0 || answer.compare("NO") == 0)
		{
			return false;
		}
		else
		{
			cout << "Invalid answer, please try again." << endl;
		}
	}
}
int main()
{
	int number;
	cout << "Enter the enrollee's number:" << endl;
	cin >> number;
	future<bool> is_enrollee_pass = async(сan_go_to_university, number); // вычисляет пройдёт ли абитуриент в университет
	while (true)
	{
		bool consent = consent_to_enrollment(); // проверяет, есть ли согласие на зачисление 
		if (consent)
		{
			if (is_enrollee_pass.get())
			{
				cout << "Enrollee with number " << number << " is admitted to the university." << endl;
				return 0;
			}
			else
			{
				cout << "Enrollee with number " << number << " does not have enough points for admission." << endl;
				return 0;
			}
		}
		else
		{
			if (flag)
			{
				cout << "Enrollee did not give consent yet." << endl << endl;
			}
			else
			{
				cout << "Time is up.";
				return 0;
			}
		}
	}
	return 0;
};