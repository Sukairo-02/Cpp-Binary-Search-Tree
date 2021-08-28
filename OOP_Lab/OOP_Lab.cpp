#include <iostream>
#include <string>
#include <vector>
#include "bTree.h"

using namespace LAB;

void mOut()
{
	std::cout <<
		"\nВыберите желаемое действие:\n" <<
		"1.Добавить элемент\n" <<
		"2.In order\n" <<
		"3.Pre order\n" <<
		"4.Post order\n" <<
		"5.Сбалансировать дерево\n" <<
		"6.Найти элемент\n" <<
		"7.Удалить последний найденый элемент\n" <<
		"8.Удалить ветку последнего найденого элемента\n" <<
		"9.Очистить дерево\n" <<
		"0.Выход\n";
}

void cinClear()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cerr << "Некорректный ввод!\n";
}

int main()
{
	system("chcp 1251");
	srchTree<int> tree;
	srchTree<int>::tNode<int>* found = nullptr;
	unsigned short int mOpt = 255;
	int nElem;
	std::vector<int> tmpV;

	while (mOpt)
	{
		mOut();
		if (std::cin >> mOpt)
		{
			if (mOpt < 10)
			{
				switch (mOpt)
				{
				case 1:
					std::cout << "\nВведите добавляемое значение: ";
					std::cin >> nElem;
					tree({ nElem });
					break;

				case 2:
					std::cout << "\nIn order: ";
					std::cout << tree;
					break;

				case 3:
					std::cout << "\nPost order: ";
					tmpV.clear();
					tree.Post_order(tmpV);
					for (int& e : tmpV)
					{
						std::cout << e << ' ';
					}
					std::cout << std::endl;
					break;

				case 4:
					std::cout << "\nPre order: ";
					tmpV.clear();
					tree.Pre_order(tmpV);
					for (int& e : tmpV)
					{
						std::cout << e << ' ';
					}
					std::cout << std::endl;
					break;

				case 5:
					tree.Balance();
					break;

				case 6:
					std::cout << "\nВведите искомый ключ: ";
					std::cin >> nElem;
					found = tree.Find(nElem);
					break;

				case 7:
					tree.Delete(found);
					break;

				case 8:
					tree.killBranch(found);
					break;


				case 9:
					tree.Clear();
					break;
				}
			}
			else
			{
				std::cerr << "Некорректный ввод!\n";
			}
		}
		else
		{
			cinClear();
			mOpt = 255;
		}
	}
	return 0;
}
