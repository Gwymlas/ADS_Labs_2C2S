#include <conio.h>
#include <iostream>
#include <locale.h>
#include <math.h>
#include "Polyline.h"

int GetKey()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
}

int Menu_1()
{
	std::cout << "\nЗапустить программу - Enter\nВыход - Esc" << std::endl;
	while (true)
	{
		int key = GetKey();
		if ((key == 27) || (key == 13)) return key;
	}
}

int Menu_2()
{
	std::cout << "\nДобавить точку в начало - 1\nДобавить точку в конец - 2\nПросмотр вершины по индексу - 3\nПросмотр ломанной - 4\nВыход - Esc" << std::endl;
	while (true)
	{
		int key = GetKey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 27)) return key;
	}
}

int Menu_3()
{
	std::cout << "\nПроверка на равенство линий - 1\nПроверка на неравенство линий - 2\nВычислить длину - 3\nВыход - Esc" << std::endl;
	while (true)
	{
		int key = GetKey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 27)) return key;
	}
}



int main() {
	Polyline test(3);
	for (size_t i = 0; i < 3; ++i)
	{

		test[i].x = i;
		test[i].y = i;
	}

	Polyline test1(1);
	test1 = test;
	std::cout << "test1: " << test1 << std::endl;

	std::cout << "test: " << test << std::endl;
	std::cout << "lenght test: " << test.Length() << std::endl;
	try
	{
		//test[35];
		std::cout << "test[2] x:" << test[2].x << std::endl;
	}
	catch (const char* err)
	{
		std::cerr << err << std::endl;
	}

	Polyline test2(2);
	for (size_t i = 0; i < 2; ++i)
	{

		test2[i].x = (double)i + 10;
		test2[i].y = (double)i + 10;
	}

	std::cout << "test2: " << test2 << std::endl;
	std::cout << "lenght test2: " << test2.Length() << std::endl;

	Polyline test3 = test + test2;

	std::cout << "test3: " << test3 << std::endl;
	std::cout << "operator == (test2 == test3): " << (test2 == test3) << std::endl;
	std::cout << "operator != (test2 != test3): " << (test2 != test3) << std::endl;

	/*Point p;
	p.x = 21;
	p.y = 23;*/


	/*try
	{
		test3.AddToBegin(p);
		test3.AddToEnd(p);
	}
	catch (const char* err)
	{
		std::cout << err << std::endl;
	}

	std::cout << "test3: " << test3 << std::endl;*/

	setlocale(LC_ALL, "Russian");

	while (true)
	{
		system("cls");
		int m1 = Menu_1();
		if (m1 == 13)
		{
			Polyline line;
			while (true)
			{
				system("cls");
				int m2 = Menu_2();
				if (m2 == 49)
				{
					Point p;
					std::cout << "Введите координаты точки" << std::endl;
					std::cin >> p.x >> p.y;
					try
					{
						line.AddToBegin(p);
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						std::cin.get();
						std::cin.get();
					}
				}
				if (m2 == 50)
				{
					Point p;
					std::cout << "Введите координаты точки" << std::endl;
					std::cin >> p.x >> p.y;
					try
					{
						line.AddToEnd(p);
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						std::cin.get();
						std::cin.get();
					}
				}
				if (m2 == 51)
				{
					int index = 0;
					std::cout << "Введите индекс координаты" << std::endl;
					std::cin >> index;
					try
					{
						std::cout << "(" << line[index].x << "," << line[index].y << ")" << std::endl;
					}
					catch (const char* err)
					{
						std::cout << err << std::endl;
						std::cin.get();
						std::cin.get();
					}
				}
				if (m2 == 52)
				{
					while(true)
					{
						system("cls");
						std::cout << line << std::endl;
						int m3 = Menu_3();
						if (m3 == 49)
						{

						}
						if (m3 == 50)
						{

						}
						if (m3 == 51)
						{
							std::cout << line.Length() << std::endl;
							std::cin.get();
							std::cin.get();							
						}
						if (m3 == 27)
						{
							break;
						}
					}				
				}
				if (m2 == 27) break;
			}
		}
		if (m1 == 27) break;
	}
	return 0;
}

