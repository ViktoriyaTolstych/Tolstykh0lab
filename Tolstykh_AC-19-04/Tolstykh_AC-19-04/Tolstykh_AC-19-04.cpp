﻿#include "CKC.h"
#include "Cpipe.h"
#include "utility.h"
#include "seti.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

bool SearchByRepair(const Cpipe& p, int param)
{
	return p.Getpriznak() == param - 1;
}
bool SearchByName(const CKC& k, string name)
{
	return k.Getname() == name;
}
bool SearchByPercent(const CKC& kv, double param)
{
	return 100 * (1 - (1. * kv.Getkolvo_tsehov_v_rabote()) / kv.Getkolvo_tsehov()) >= param;
}
template <typename W, typename T>
using Filter = bool(*)(const W& o, T param);

template <typename W, typename T>
vector<int> FindItemsByFilter(const unordered_map <int, W>& g, Filter <W, T> f, T param)
{
	vector<int>res;
	int i = 0;
	for (const auto& obj : g)
	{
		if (f(obj.second, param))
			res.push_back(i);
		i++;
	}
	if (res.size() == 0)
	{
		cout << "Ошибка\n";
	}
	return res;
}

//void EditOneKC(unordered_map<int, CKC>& kv)
//{
//	cout << "Введите ID Кс которую вы хотите редактировать: ";
//	int k;
//	k = Utility::proverka(1, CKC::GetCountKC());
//	cout << "\n0. Добавить цех в работе\n1. Удалить работающий цех\n ";
//	if (Utility::proverka(0, 1) == 0)
//	{
//		if (kv[k].Getkolvo_tsehov() > kv[k].Getkolvo_tsehov_v_rabote())
//			kv[k].Getkolvo_tsehov_v_rabote() += 1;
//	}
//	else
//	{
//		if (kv[k].Getkolvo_tsehov_v_rabote() > 0)
//			kv[k].Getkolvo_tsehov_v_rabote() -= 1;
//	}
//
//}
template <typename T>
int GetId(const unordered_map<int, T>& mapp)
{
	int id;
	while (true)
	{
		cout << "Введите id (больше 0): ";
		cin >> id;
		if (id == 0)
		{
			cout << endl << "Выход..." << endl;
			return -1;
		}
		else if (mapp.count(id))
		{
			return id;
		}
		cout << endl << "Такого id нет. Введите ещё раз" << endl;
	}
}

void EditPackPipeline(unordered_map<int, Cpipe>& pv)
{
	cout << "Выберите" << endl;
	cout << "\n1. Трубы в работе \n2. Трубы в ремонте\n3.По ID";
	switch (Utility::proverka(1, 3))
	{
	case 1:
	{
		for (int i : FindItemsByFilter(pv, SearchByRepair, 0))
			pv.find(i)->second.RedaktPipeline();
	}
	case 2:
	{
		for (int i : FindItemsByFilter(pv, SearchByRepair, 1))
			pv.find(i)->second.RedaktPipeline();
	}
	case 3:
	{vector<int> v;
	while (1)
	{
		cout << "Введите id который хотите редактировать: ";
		v.push_back(Utility::proverka(1, Cpipe::MaxId));
		cout << "Хотите ли вы отредактировать что-либо еще? " << endl << "\t0.Да\n1.Нет";
		if (Utility::proverka(0, 1) == 1)
			break;
	} for (auto i : v)
	{
		if (pv.find(i) != pv.end())
			pv.find(i)->second.RedaktPipeline();
	}
	break;
	}
	}
}

void DelPipes(unordered_map<int, Cpipe>& pipes_p)
{
	if (pipes_p.size() != 0)
	{
		cout << "введите ID трубы которую хотите удалить: ";
		int i;
		cin >> i;
		if (pipes_p.find(i) != pipes_p.end())
		{
			pipes_p.erase(i);
			cout << "труба удалена";
		}
	}
	else
	{
		cout << "ошибка\n";
	}
}

void DelKC(unordered_map <int, CKC>& cs)
{
	if (cs.size() != 0)
	{
		cout << "Введите ID KC которую хотите удалить: ";
		int i;
		cin >> i;
		if (cs.find(i) != cs.end())
		{
			cs.erase(i);
			cout << "КС удалена";
		}
	}
	else
	{
		cout << "ошибка\n";
	}
}


void PrintMenu()
{
	cout << "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Показать объекты" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Сохранить в файл" << endl
		<< "7. Загрузить из файла " << endl
		<< "8. Поиск по фильтру" << endl
		<< "9. Удалить трубу или КС" << endl
		<< "10.Соединить КС с трубой" << endl
		<< "11. Топологическая сортировка" << endl
		<< "12. Сохранить сеть" << endl
		<< "0. Выход" << endl
		<< endl << "Выберите действие - ";

}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	unordered_map<int, Cpipe> pv;
	unordered_map<int, CKC> kv;
	int edgeCount = 0;
	
	while (1)
	{
		PrintMenu();

		switch (Utility::proverka(0, 12))
		{
		case 1:
		{
            Cpipe p;
			cin >> p;
			pv.insert(pair<int, Cpipe>(++Cpipe::MaxId, p));
			break;
		}
		case 2:
		{
			CKC k;
			cin >> k;
			kv.insert(pair<int, CKC>(++CKC::KCMaxId, k));
			break;
		}
		case 3:

		{
			if (pv.size() > 0)
			{
				cout << "Трубы:" << endl;

				for (const auto& p : pv)
				{
					cout << p.first << ':' << p.second << endl;
				}
			}
			else
			{
				cout << "Нет информации о трубах \n ";
			}
			if (kv.size() > 0)
			{
				cout << "KC:" << endl;
				for (const auto& k : kv)
				{
					cout << k.first << ':' << k.second << endl;
				}
			}
			else
			{
				cout << "Нет информации о КС\n ";
			}
			break;
		}
		case 4:

		{
			if (pv.size() > 0)
			{
				cout << "Введите ID который вы хотите изменить: ";
				int k = GetId(pv);
				if (k != -1)
					pv[k].RedaktPipeline();
			}
			else
			{
				cout << "Нет информации о трубах \n ";
			}
			break;
		}
		case 5:

		{
			if (kv.size()>0)
		{
			cout << "Введите ID KC которую хотите редактировать ";
			int k = GetId(kv);
			if (k != -1)
			kv[k].RedaktKC();
		}
		else
			cout << "Нет информации о KC\n ";

		}break;

		case 6:
		{
			if ((pv.size() != 0) && (kv.size() != 0))
			{
				ofstream fout;
				string nameoffile;
				cout << "Введите имя файла.txt";
				cin.ignore();
				getline(cin, nameoffile);
				fout.open(nameoffile +".txt", ios::out);
				if (fout.is_open())
				{
					fout << pv.size() << endl;
					fout << kv.size() << endl
					<< Cpipe::MaxId << endl
						<< CKC::KCMaxId << endl
						<< edgeCount << endl;
					for (auto& p : pv)
					{
						fout << p.first << endl;
						p.second.Save(fout); 
					}
					for (auto& k : kv)
					{
						fout << k.first << endl;
						k.second.Save(fout);
					}
					fout.close();
				}
			}

			else
			{
				cout << "Ошибка\n ";
			}
			break;
		}

		case 7:
		{
			{
				ifstream fin;
				string nameoffile;
				cout << "Введите имя файла";
				cin.ignore();
				getline(cin, nameoffile);
				fin.open(nameoffile + ".txt", ios::in);
				if (fin.is_open())

				{
					pv.clear();
					kv.clear();
					int count1;
					int count2;
					fin >> count1;
					fin >> count2;
					fin >> Cpipe::MaxId;
					fin >> CKC::KCMaxId;
					fin >> edgeCount;
					while (count1--)
					{
						int id;
						fin >> id;
						Cpipe p;
						p.Load(fin);
						pv.insert(make_pair(id, p)); 
					}
					while (count2--)
					{
						int id;
						fin >> id;
						CKC k;
						k.Load(fin);
						kv.insert(make_pair(id, k)); 
					}

				}
				else cout << "файл не найден\n";
				fin.close();
			}

			break;
		}


		case 8:
		{
			cout << "Выберите \n1.трубы по статусу\n2.KC";
			if (Utility::proverka(1, 2) == 1)
			{
				cout << "1. В работе" << endl
					<< "2. В ремонте" << endl;
				if (Utility::proverka(1, 2) == 1) {
					for (int i : FindItemsByFilter(pv, SearchByRepair, 0))
						cout << pv[i + 1];
				}
				else
				{
					for (int i : FindItemsByFilter(pv, SearchByRepair, 1))
						cout << pv[i + 1];
				}
			}
			else
				cout << "\ncВыберите\n1.По имени\n" << "2.Процент неиспользованных цехов в работе";
			if (Utility::proverka(1, 2) == 1)
			{
				string name;
				cout << "\nПожалуйста введите имя KC: ";
				cin.ignore(1000, '\n');
				getline(cin, name);
				for (int i : FindItemsByFilter(kv, SearchByName, name))
					cout << kv[i + 1];
		
			}
			else
			{
				cout << "\nВведите процент - ";
				for (int i : FindItemsByFilter(kv, SearchByPercent, Utility::proverka(0.00, 100.0)))
					cout << kv[i + 1];
			}
			break;
		}
		case 9:
		{
			DelPipes(pv);
		break;
		}
		case 10:
		{
			DelKC(kv);
			break;
		}
		case 11:
		{
			if (pv.size())
			{
				int id = GetId(pv);
				if (id != -1)
				{
					cout << "КС откуда выходит труба:";
					int in = GetId(kv);
					cout << "КС куда входит труба:";
					int out = GetId(kv);
					if (in != out)
					{
						pv[id].Svyazat(in, out);
						edgeCount++;
					}
					else
						cout << "ошибка" << endl;
				}
			}
			break;
		}
		case 12:
		{
			if (pv.size() > 0 && kv.size() > 1)
			{
				for (const pair<int, Cpipe>& p : pv)
					if (p.second.CanIspolzovat())
						p.second.ShowSvyaz(p.first);
			}
			break;
		}
		case 13:
		{
			seti net(edgeCount);
			for (const pair<int, Cpipe>& p : pv)
				if (p.second.CanIspolzovat())
					net.addEdge(p.second.out - 1, p.second.in - 1);
			net.topologicalSort();
			break;
		}
		case 0:
		{
			return 0;

		}

		default:
		{cout << "Ошибка" << endl; }
		}
	}

	return 0;
}
