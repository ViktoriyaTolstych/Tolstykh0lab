#include "CKC.h"
#include "Cpipe.h"
#include "utility.h"
#include "lib.h"
#include "seti.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
string EnterName()
{
	string filename;
	cout << "\nПожалуйста введите имя KC: ";
	cin.ignore(1000, '\n');
	getline(cin, filename);
	return filename;
}

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
		cout « "Ошибка\n";
	}
	return res;
}

void EditOneKC(unordered_map<int, CKC>& kv)
{
	cout << "Введите ID Кс которую вы хотите редактировать: ";
	int k;
	k = Utility::proverka(1, CKC::GetCountKC());
	cout << "\n0. Добавить цех в работе\n1. Удалить работающий цех\n ";
	if (Utility::proverka(0, 1) == 0)
	{
		if (kv[k].Getkolvo_tsehov() > kv[k].Getkolvo_tsehov_v_rabote())
			kv[k].Getkolvo_tsehov_v_rabote() += 1;
	}
	else
	{
		if (kv[k].Getkolvo_tsehov_v_rabote() > 0)
			kv[k].Getkolvo_tsehov_v_rabote() -= 1;
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
		cout << "Введите idкоторый хотите редактировать: ";
		v.push_back(Utility::proverka(1, Cpipe::GetCountP()));
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
			pipes_p.erase(i);
		cout << "труба удалена";
	}
	else
	{
		cout << "ошибка\n";
	}
}

void DelKC(unordered_map <int, CKC>& kc_k, seti& network, unordered_map<int, Cpipe>& pv)
{
	if (kc_k.size() != 0)
	{
		cout << "Введите ID KC которую хоите удалить: ";
		int t = Utility::proverka(1, CKC::GetCountKC());
		network.deleteidks(t);
		for (auto& n : pv)
		{
			if (n.second.getinputks() == t)
				n.second.setinputks(0);
		}
		for (auto& n : pv)
		{
			if (n.second.getoutputks() == t)
				n.second.setoutputks(0);
		}
		kc_k.erase(t);
		cout << "Кс удалена";
	}
	else
	{
		cout << "Ошибка\n";
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
	unordered_map<int, Cpipe> pv;
	unordered_map<int, CKC> kv;

	seti network;
	vector<unsigned int> sortedmatrix;
	CKC k;
	Cpipe p;
	while (1)
	{
		PrintMenu();

		switch (Utility::proverka(0, 12))
		{
		case 1:
		{

			Cpipe p;
			cin >> p;
			pv.insert(pair<int, Cpipe>(p.getID(), p));
			break;
		}
		case 2:
		{
			CKC k;
			cin >> k;
			kv.insert(pair<int, CKC>(k.getID(), k));
			break;
		}
		case 3:

		{
			if (pv.size() > 0)

				for (const auto& p : pv)
				{
					cout << p.second << endl;
				}

			else
			{
				cout << "Нет информации о трубах \n ";
			}
			if (kv.size() > 0)
				for (const auto& k : kv)
				{
					cout << k.second <<endl;
				}
			else
			{
				cout << "Нет информации о КС\n ";
			}
			break;
		}
		case 4:

		{
			if (pv.size())
				EditPackPipeline(pv );
			else cout << "Нет информации о трубах \n ";
			break;
		}
		case 5:

		{if (kv.size())
		{
			cout << "Введите ID KC которую хотите редактировать ";
			int n;
			cin >> n;
			kv[n].RedaktKC();
		}
		else
			cout << "Нет информации о KC\n ";

		}break;

		case 6:


		{
			if ((pv.size() != 0) and (kv.size() != 0))
			{
				ofstream fout;
				string nameoffile;
				cout << "Введите имя файла";
				cin.ignore();
				getline(cin, nameoffile);
				fout.open(nameoffile, ios::out);
				if (fout.is_open())
				{
					fout << pv.size() << endl;
					fout << kv.size() << endl;
					for (const auto& p : pv)
					{
						fout << p.second;
					}
					for (const auto& k : kv)
					{
						fout << k.second;
					}
					fout.close();
				}break;
			}

			else
			{
				cout << "Ошибка\n ";
			}



		}

		case 7:

		{

			{
				ifstream fin;
				string nameoffile;
				cout << "Введите имя файла";
				cin.ignore();
				getline(cin, nameoffile);
				fin.open(nameoffile, ios::in);
				if (fin.is_open())

				{
					int count1;
					int count2;
					fin >> count1;
					fin >> count2;
					while (count1--)
					{
						Cpipe p;
						p.inputfilepipe(fin);
						fin >> p;
					}
					while (count2--)
					{
						CKC k;
						fin >> k;
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

				for (int i : FindItemsByFilter(kv, SearchByName, EnterName()))
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
		{ cout << "1.Трубы" << endl
			<< "2. KC" << endl
			<< "Пожалуйста выберите что хотите удалить: ";
		if (Utility::proverka(1, 2) == 1)
		{
			DelPipes(pv);
		}
		else
		{
			DelKC(kv, network, pv);
		}
		break;
		}
		case 10:
		{

			network.editnetwork(pv);
			break;

		}
		case 11:
		{
			sortedmatrix = network.tgtssort(pv);
			if (sortedmatrix.size() > 0)
			{
				int k = 1;
				for (auto& i : sortedmatrix)
				{
					cout << k << " ID :"<< i << endl;
					k += 1;
				}
			}
			else
				cout << "Это цикл\n";
			break;
		}
		case 12:
		{
			if (network.getidks().size() > 0 || network.getidt().size() > 0)
			{
				ofstream fout;
				fout.open("gts.txt", ios::out);
				if (fout.is_open())
				{
					sortedmatrix = network.tgtssort(pv);
					if (sortedmatrix.size() > 0)
					{
						int k = 1;
						for (auto& i : sortedmatrix)
						{

							fout << k << " ID :" << i << endl;
							k += 1;
						}

					}
					network.savefilenetwork(fout);
					fout.close();
				}
				break;
			}
			else
			{
				cout << "Нет сети\n";
				break;
			}

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
