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

		cout << "�������������� ������ ��� ������������:--------------------------------------------------------------" << endl;
		cout << "0.  ������� ������ � �������" << endl;
		cout << "1.  ���������� ������������� ����� ���������� ���������" << endl;
		cout << "2.  �������������� ��������� (�� ���������, � ������ ���������; ��������� ����� ���������� 30 � 31)" << endl;
		cout << "�������� ������:-------------------------------------------------------------------------------------" << endl;
		cout << "3.  �������� �������" << endl;
		cout << "4.  ������� ������� �� �����" << endl;
		cout << "5.  ����� �� �����" << endl;
		cout << "6.  ������ �� ������/������" << endl;
		cout << "7.  ��������" << endl;
		cout << "8.  ���������� ����� � ������" << endl;
		cout << "9.  ��������� �� �������" << endl;
		cout << "������ ��������:-------------------------------------------------------------------------------------" << endl;
		cout << "10. ������� �������� ������ foreach (range based for)" << endl;
		cout << "11. ������� ���������, ����������� �� begin" << endl;
		cout << "12. ���������������� 1-�� �������� ++" << endl;
		cout << "13. ���������������� 2-�� �������� ++" << endl;
		cout << "14. ���������������� 1-�� �������� --" << endl;
		cout << "15. ���������������� 2-�� �������� --" << endl;
		cout << "16. ������������ 1-�� �������� *" << endl;
		cout << "17. ������������ 2-�� �������� *" << endl;
		cout << "18. �������� 1-�� � 2-�� ��������� � ������� ==" << endl;
		cout << "19. �������� 1-�� � 2-�� ��������� � ������� !=" << endl;
		cout << "�������� ��������:-----------------------------------------------------------------------------------" << endl;
		cout << "20. ������� ��� �������� ������ � �������������� ��������� ���������" << endl;
		cout << "21. ������� ���������, ����������� �� rbegin" << endl;
		cout << "22. ���������������� 1-�� �������� ++" << endl;
		cout << "23. ���������������� 2-�� �������� ++" << endl;
		cout << "24. ���������������� 1-�� �������� --" << endl;
		cout << "25. ���������������� 2-�� �������� --" << endl;
		cout << "26. ������������ 1-�� �������� *" << endl;
		cout << "27. ������������ 2-�� �������� *" << endl;
		cout << "28. �������� 1-�� � 2-�� ��������� � ������� ==" << endl;
		cout << "29. �������� 1-�� � 2-�� ��������� � ������� !=" << endl;
		cout << "�������������� ���������� ������:--------------------------------------------------------------------" << endl;
		cout << "30. ��������� ���������� ���������� c ���������� �������������� add(�������� rand(), ���� rand())" << endl;
		cout << "31. ��������� ����������� ������������������� for(i = 0; i < n; i++) add(�������� rand(), ���� i)" << endl;

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
							if (rbst.remove(key)) //���� ����� ����� ���� ����
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
				cout << "������ ������: " << rbst.size() << endl;
				cout << "������������� ������: " << 1.39 * (log((double)rbst.size()) / log(2.0)) << endl;
				cout << "����������������� ������ �������: " << labor_add / (quantity / 2) << endl;
				cout << "����������������� ������ ��������: " << labor_remove / (quantity / 2) << endl;
				cout << "����������������� ������ ������: " << labor_at / (quantity / 2) << endl;
				break;
			}
			case 3: {
				cout << "������� ����: ";
				K key;
				cin >> key;
				cout << "������� ��������: ";
				T value;
				cin >> value;
				rbst.add(value, key);
				keys.push_back(key);
				break;
			}
			case 4: {
				cout << "������� ����: ";
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
				cout << "������� ����: ";
				K key;
				cin >> key;
				cout << rbst.find(key) << endl;
				break;
			}
			case 6: {
				cout << "������� ����: ";
				K key;
				cin >> key;
				cout << rbst.at(key) << endl;
				cout << "�������� ��������? (�� - 1, ��� - 0)" << endl;
				bool b;
				cin >> b;
				if (b) {
					cout << "������� ����� ��������: ";
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
				cout << "������� ���������� ����� ���������: ";
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
				cout << "������� ���������� ����� ���������: ";
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
				cout << "�������� ����� �������" << endl;
				break;
			}
		}
		catch (exception ex) {
			cout << ex.what() << endl;
		}
		system("pause");
	}

}