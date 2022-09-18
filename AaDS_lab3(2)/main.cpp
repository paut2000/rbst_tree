#include <iostream>
#include <ctime>
#include <vector>
#include "RBST.h"

using namespace std;

template <typename T, typename K>
int Menu();

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	return Menu< int, int >();
}

template <typename T, typename K>
int Menu() {

	RBST<T, K> rbst;
	vector <K> keys;
	typename RBST<T, K>::iterator it1 = rbst.begin();
	typename RBST<T, K>::iterator it2 = rbst.begin();
	typename RBST<T, K>::reverse_iterator rit1 = rbst.rbegin();
	typename RBST<T, K>::reverse_iterator rit2 = rbst.rbegin();

	for (;;) {

		cout << "Дополнительные методы для тестирования:--------------------------------------------------------------" << endl;
		cout << "0.  Вывести дерево в консоль" << endl;
		cout << "1.  Количество просмотренных узлов предыдущей операцией" << endl;
		cout << "2.  Протестировать коллекцию (не заполняет, а только тестирует; заполнить можно операциями 30 и 31)" << endl;
		cout << "Основные методы:-------------------------------------------------------------------------------------" << endl;
		cout << "3.  Добавить элемент" << endl;
		cout << "4.  Удалить элемент по ключу" << endl;
		cout << "5.  Найти по ключу" << endl;
		cout << "6.  Доступ по чтению/записи" << endl;
		cout << "7.  Очистить" << endl;
		cout << "8.  Количество узлов в дереве" << endl;
		cout << "9.  Проверить на пустоту" << endl;
		cout << "Прямой итератор:-------------------------------------------------------------------------------------" << endl;
		cout << "10. Вывести элементы циклом foreach (range based for)" << endl;
		cout << "11. Создать итераторы, указывающие на begin" << endl;
		cout << "12. Инкрементировать 1-ый итератор ++" << endl;
		cout << "13. Инкрементировать 2-ой итератор ++" << endl;
		cout << "14. Декрементировать 1-ый итератор --" << endl;
		cout << "15. Декрементировать 2-ой итератор --" << endl;
		cout << "16. Разыменовать 1-ый итератор *" << endl;
		cout << "17. Разыменовать 2-ой итератор *" << endl;
		cout << "18. Сравнить 1-ый и 2-ой итераторы с помощью ==" << endl;
		cout << "19. Сравнить 1-ый и 2-ой итераторы с помощью !=" << endl;
		cout << "Обратный итератор:-----------------------------------------------------------------------------------" << endl;
		cout << "20. Вывести все элементы циклом с использованием обратного итератора" << endl;
		cout << "21. Создать итераторы, указывающие на rbegin" << endl;
		cout << "22. Инкрементировать 1-ый итератор ++" << endl;
		cout << "23. Инкрементировать 2-ой итератор ++" << endl;
		cout << "24. Декрементировать 1-ый итератор --" << endl;
		cout << "25. Декрементировать 2-ой итератор --" << endl;
		cout << "26. Разыменовать 1-ый итератор *" << endl;
		cout << "27. Разыменовать 2-ой итератор *" << endl;
		cout << "28. Сравнить 1-ый и 2-ой итераторы с помощью ==" << endl;
		cout << "29. Сравнить 1-ый и 2-ой итераторы с помощью !=" << endl;
		cout << "Автоматическое заполнение дерева:--------------------------------------------------------------------" << endl;
		cout << "30. Заполнить случайными значениями c нормальным распределением add(значение rand(), ключ rand())" << endl;
		cout << "31. Заполнить вырожденной последовательностью for(i = 0; i < n; i++) add(значение rand(), ключ i)" << endl;

		int n;
		cin >> n;

		try {
			switch (n)
			{
			case 0:
				rbst.out();
				break;
			case 1:
				cout << rbst.get_visited_node_quantity() << endl;
				break;
			case 2: {
				double labor_at = 0;
				double labor_add = 0;
				double labor_remove = 0;
				int quantity = rbst.size();
				for (int i = 0; i < quantity / 2; i++) {
					if (i % 10 == 0) {
						try {
							int key = rand();
							if (rbst.remove(key)) //если вдруг такой ключ есть
								for (int i = 0; i < keys.size(); i++)
									if (key == keys[i])
										keys.erase(keys.begin() + i);
							labor_remove += rbst.get_visited_node_quantity();
						}
						catch (exception ex) {}
						try {
							rbst.add(keys[rand() % keys.size()], 1);
							labor_add += rbst.get_visited_node_quantity();
						}
						catch (exception ex) {}
						try {
							rbst.at(rand());
							labor_at += rbst.get_visited_node_quantity();
						}
						catch (exception ex) {
							labor_at += rbst.get_visited_node_quantity();
						}
					}
					else {
						try {
							int key = keys[rand() % keys.size()];
							rbst.remove(key);
							labor_remove += rbst.get_visited_node_quantity();
							for (int i = 0; i < keys.size(); i++)
								if (key == keys[i])
									keys.erase(keys.begin() + i);
						}
						catch (exception ex) {}
						try {
							int key = rand();
							rbst.add(key, 1);
							labor_add += rbst.get_visited_node_quantity();
							keys.push_back(key);
						}
						catch (exception ex) {}
						try {
							rbst.at(keys[rand() % keys.size()]);
							labor_at += rbst.get_visited_node_quantity();
						}
						catch (exception ex) {
							labor_at += rbst.get_visited_node_quantity();
						}
					}
				}
				cout << "Размер дерева: " << rbst.size() << endl;
				cout << "Теоретическая оценка: " << 1.39 * (log((double)rbst.size()) / log(2.0)) << endl;
				cout << "Экспериментальная оценка вставки: " << labor_add / (quantity / 2) << endl;
				cout << "Экспериментальная оценка удаления: " << labor_remove / (quantity / 2) << endl;
				cout << "Экспериментальная оценка поиска: " << labor_at / (quantity / 2) << endl;
				break;
			}
			case 3: {
				cout << "Введите ключ: ";
				K key;
				cin >> key;
				cout << "Введите значение: ";
				T value;
				cin >> value;
				rbst.add(value, key);
				keys.push_back(key);
				break;
			}
			case 4: {
				cout << "Введите ключ: ";
				K key;
				cin >> key;
				bool b = rbst.remove(key);
				cout << b << endl;
				if (b)
					for (int i = 0; i < keys.size(); i++) {
						if (key == keys[i]) keys.erase(keys.begin() + i);
					}
				break;
			}
			case 5: {
				cout << "Введите ключ: ";
				K key;
				cin >> key;
				cout << rbst.find(key) << endl;
				break;
			}
			case 6: {
				cout << "Введите ключ: ";
				K key;
				cin >> key;
				cout << rbst.at(key) << endl;
				cout << "Изменить значение? (Да - 1, нет - 0)" << endl;
				bool b;
				cin >> b;
				if (b) {
					cout << "Введите новое значение: ";
					T value;
					cin >> value;
					rbst.at(key) = value;
				}
				break;
			}
			case 7:
				rbst.clean();
				keys.clear();
				break;
			case 8:
				cout << rbst.size() << endl;
				break;
			case 9:
				cout << rbst.empty() << endl;
				break;
			case 10:
				for (T i : rbst)
					cout << i << ' ';
				cout << endl;
				break;
			case 11:
				it1 = rbst.begin();
				it2 = rbst.begin();
				break;
			case 12:
				it1++;
				break;
			case 13:
				it2++;
				break;
			case 14:
				it1--;
				break;
			case 15:
				it2--;
				break;
			case 16:
				cout << *it1 << endl;
				break;
			case 17:
				cout << *it2 << endl;
				break;
			case 18:
				cout << (it1 == it2) << endl;
				break;
			case 19:
				cout << (it1 != it2) << endl;
				break;
			case 20:
				for (typename RBST<T, K>::reverse_iterator rit = rbst.rbegin(); rit != rbst.rend(); rit++)
					cout << *rit << ' ';
				cout << endl;
				break;
			case 21:
				rit1 = rbst.rbegin();
				rit2 = rbst.rbegin();
				break;
			case 22:
				rit1++;
				break;
			case 23:
				rit2++;
				break;
			case 24:
				rit1--;
				break;
			case 25:
				rit2--;
				break;
			case 26:
				cout << *rit1 << endl;
				break;
			case 27:
				cout << *rit2 << endl;
				break;
			case 28:
				cout << (rit1 == rit2) << endl;
				break;
			case 29:
				cout << (rit1 != rit2) << endl;
				break;
			case 30: {
				cout << "Введите количество новых элементов: ";
				int n;
				cin >> n;
				for (int i = 0; i < n; i++)
					try {
					int key = rand();
					rbst.add(rand(), key);
					keys.push_back(key);
				}
				catch (exception ex) {
					cout << ex.what() << endl;
				}
				break;
			}
			case 31: {
				cout << "Введите количество новых элементов: ";
				int n;
				cin >> n;
				for (int i = 0; i < n; i++)
					try {
					rbst.add(rand(), i);
					keys.push_back(i);
				}
				catch (exception ex) {
					cout << ex.what() << endl;
				}
				break;
			}
			default:
				cout << "Неверный номер команды" << endl;
				break;
			}
		}
		catch (exception ex) {
			cout << ex.what() << endl;
		}
		system("pause");
	}

}