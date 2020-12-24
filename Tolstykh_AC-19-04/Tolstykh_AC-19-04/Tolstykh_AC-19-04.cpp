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

void menu()
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
		<<"10.Соединить КС с трубой"<< endl 
		<<"11. Топологическая сортировка"<< endl
		<<"12. Сохранить сеть"<< endl
		<< "0. Выход" << endl
		<< endl << "Выберите действие - ";

}
string EnterName()
{
	string filename;
	cout << "\nПожалуйста введите имя для KC: ";
	cin.ignore(1000, '\n');
	getline(cin, filename);
	return filename;
}
bool SearchById(Cpipe& p, int param)
{
	return p.Getidentificator() == param;
}
bool SearchByRepair(Cpipe& p, int param)
{
	return p.Getpriznak() == param - bool(1);
}
bool SearchByName(CKC& cs, string name)
{
	return cs.Getname() == name;
}
bool SearchByPercent(CKC& cs, int param)
{
	return 100 * (1 - (1. * cs.Getkolvo_tsehov_v_rabote()) / cs.Getkolvo_tsehov()) >= param;

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

void Viewall(unordered_map<int, Cpipe>& pipes, unordered_map<int, CKC>& c)
{
	cout << "1. Просмотр всего\n" << "2. Просмотр труб\n" << "3. Просмотр КС\nВыберите - ";
	switch (Utility::proverka(1, 3))
	{
	case 1:
	{
		cout << endl;
		for (auto p : pipes)
		{
			cout << " id трубы: " << p.second.Getidentificator() << std::endl << "димаетр:: " << p.second.Getdiametr() << std::endl
				<< "длина: " << p.second.Getdlina() << std::endl << "состояние трубы:: " << p.second.checkRepair();
		}
		for (auto cs : c)
		{
			cout.precision(2);
			cout << "\nКС id: " << cs.second.Getidentificator() << endl << "Имя: " << cs.second.Getname()
				<< endl << "Количество цехов: " << cs.second.Getkolvo_tsehov() << endl
				<< "Количество цехов в работе: " << cs.second.Getkolvo_tsehov_v_rabote() << endl
				<< "Эффективность: " << cs.second.Geteffektivnost() << endl << endl;
		}
		break;
	}
	case 2:
	{
		cout << "Выберите id который вы хотите вывести: ";
		int OutPipe;
		cin >> OutPipe;
		cout << " id трубы : " << pipes[OutPipe].Getidentificator() << endl << "диаметр: " << pipes[OutPipe].Getdiametr() << endl
			<< "длина: " << pipes[OutPipe].Getdlina() << endl << "состояние трубы: " << pipes[OutPipe].checkRepair();
		break;
	}
	case 3:
	{
		cout << "Выберите id который вы хотите вывести: ";
		int OutKC;
		cin >> OutKC;
		cout.precision(2);
		cout << "\nКС id: " << c[OutKC].Getidentificator() << endl << "Имя: " << c[OutKC].Getname()
			<< endl << "Количесвто цехов: " << c[OutKC].Getkolvo_tsehov() << endl
			<< "Количество цехов в работе: " << c[OutKC].Getkolvo_tsehov_v_rabote() << endl
			<< "Эффективность: " << c[OutKC].Geteffektivnost() << endl << endl;;
		break;
	}
	}
}
void SaveAll(unordered_map<int,Cpipe>& pipes, const unordered_map<int,CKC>& cs)
{
	ofstream fout;
	string name;
	cout << "Введите имя файла: ";
	getline(cin,name);
	cin >> name;
	fout.open(name, ios::out);
	if (fout.is_open())
	{
		fout << pipes.size() << endl;
		fout << cs.size() << endl;
		fout << endl;

		if (pipes.size() != 0 || cs.size() != 0)
		{
			for (auto& p : pipes)
			{
				fout << p.second.Getidentificator() << endl << p.second.Getdiametr() << endl 
					<< p.second.Getdlina() << endl << p.second.Getpriznak() << endl << endl;
			}
			for (const auto& i : cs)
			{
				/*fout.precision(2);*/
				fout << i.second.Getidentificator() << endl << i.second.Getname() << endl << i.second.Getkolvo_tsehov() << endl
					<< i.second.Getkolvo_tsehov_v_rabote() << endl << i.second.Geteffektivnost() << endl << endl;
			}
			cout << "Сохранено\n\n";
		}
		fout.close();
	}
}
void LoadAll(unordered_map<int, Cpipe>& pipes, unordered_map<int, CKC>& cs)
{
	ifstream fin;
	string name;
	cout << "Введите имя файла: ";
	getline(cin, name);
	cin >> name;
	fin.open(name, ios::in);

	if (fin.is_open())
	{
		int lenpipe, lencs;
		fin >> lenpipe;
		fin >> lencs;
		for (int i = 0; i < lenpipe; i++)
		{
			Cpipe p;
			fin >> p.Getidentificator();
			fin >> p.Getdiametr();
			fin >> p.Getdlina();
			fin >> p.Getpriznak();
			pipes.insert(pair<int, Cpipe>(pipes.size(), p));
		}
		for (int i = 0; i < lencs; i++)
		{
			CKC c;
			fin >> c.Getidentificator();
			fin >> c.Getname();
			fin >> c.Getkolvo_tsehov();
			fin >> c.Getkolvo_tsehov_v_rabote();
			fin >> c.Geteffektivnost();
			cs.insert(pair<int, CKC>(cs.size(), c));
		}
		fin.close();
		cout << "Data downloaded\n\n";
	}
}
void Cpipe::EditAllPipes(unordered_map<int, Cpipe>& pipes)
{
	cout << "Выберите трубы для редактирования" << endl;
	cout << "\n1. Трубы в работе \n2. Трубы остановленные\n3.По ID";
	switch (Utility::proverka(1, 3))
	{
	case 1:
	{
		for (int i : FindItemsByFilter(pipes, SearchByRepair, 0))
			pipes.find(i)->second.EditPipe();
	}
	case 2:
	{
		for (int i : FindItemsByFilter(pipes, SearchByRepair, 1))
			pipes.find(i)->second.EditPipe();
	}
	case 3:
	{vector<int> v;
	while (1)
	{
		cout << "Введите id для редактирования: ";
		v.push_back(Utility::proverka(1, Cpipe::Getidentificator()));
		cout << "Вы хотите еще отредактировать трубы? " << endl << "\t0.Да\n1.Нет";
		if (Utility::proverka(0, 1) == 1)
			break;
	} for (auto i : v)
	{
		if (pipes.find(i) != pipes.end())
			pipes.find(i)->second.EditPipe();
	}
	break;
	}
	}
}

void DelPipes(unordered_map<int, Cpipe>& pipes_p)
{
	if (pipes_p.size() != 0)
	{
		cout << "Введите ID трубы которую вы хотите удалить: ";
		int i;
		cin >> i;
		if (pipes_p.find(i) != pipes_p.end())
			pipes_p.erase(i);
		cout << "Труба удалена";
	}
	else
	{
		cout << "Ошибка\n";
	}
}

void DelKC(unordered_map <int, CKC>& kc_k, eti& network, unordered_map<int, Cpipe>& pv)
{
	if (kc_k.size() != 0)
	{
		cout << "Введите ID KC которую вы хотите удалить : ";
		int t = Utility::proverka(1, CKC::Getidentificator());
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
		cout << "KC удалена";
	}
	else
	{
		cout << "Ошибка\n";
	}
}
template <typename N>
void FiltrationCs(unordered_map<int, CKC>& vect, bool(*f)(CKC& p, N param), N param)
{
	for (auto& i : vect)
	{
		if (f(i.second, param))
		{
			cout.precision(2);
			cout << "\nКС id: " << i.second.Getidentificator() << endl << "Имя: " << i.second.Getname()
				<< endl << "Количество цехов: " << i.second.Getkolvo_tsehov() << endl
				<< "Количество цехов в работе: " << i.second.Getkolvo_tsehov_v_rabote() << endl
				<< "Эффективность: " << i.second.Geteffektivnost() << endl << endl;
		}
	}
	cout << endl;
}
void SearchByFilterPipes(unordered_map<int, Cpipe>& pipes)
{
	cout << "\n1. По ID\n2. По состоянию\nВыберите действие - ";
	if (Utility::proverka(1, 2) == 1)
	{
		cout << "Введите ID: ";
		int ch = Utility::proverka(0, 100);
		FiltrationPipes(pipes, SearchById, ch);
	}
	else
	{
		cout << "\n1. В работе\n2. Не в работе\nВыберите действие - ";
		int choice = Utility::proverka(1, 2);
		FiltrationPipe(pipes, SearchByRepair, choice);
	}
}
void SearchByFilterCs(unordered_map<int, CKC>& cs)
{
	cout << "\n1. По имени\n" << "2. По проценту неиспользованных цехов\nSelect action - ";
	if (Utility::proverka(1, 2) == 1)
	{
		int counter = 0;
		cout << "\nВведите имя : ";
		string name;
		getline(cin, name);
		cin >> name;
		FiltrationCs(cs, SearchByName, name);
	}
	else
	{
		cout << "\nВведите процент - ";
		int choice = Utility::proverka(0, 100);
		FiltrationCs(cs, SearchByPercent, choice);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	 unordered_map <int,Cpipe> pv;
	 unordered_map <int,CKC> kv;
	 seti network;
	while (true)
	{
		menu();
		switch (Utility::proverka(0, 12))
		{
		case 1:
		{
			Cpipe p;
			cin >> p;
			pv.insert(pair<int, Cpipe>(p.getID(), p));
			
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
			{
				if (pv.size() > 0)

					for (const auto& p : pv)
					{
						cout << p.second << endl;
					}

				else
				{
					cout <<"Здесь нет информации о трубах \n ";
				}
				if (kv.size() > 0)
					for (const auto& k : kv)
					{
						cout << k.second << endl;
					}
				else
				{
					cout << "Здесь нет информации о KC, не возможно создать сеть\n ";
				}
				break;
			}
			break;
		}
		case 4:
		{
			{
				if (pv.size())
					EditAllPipes(pv);
				else cout « "Здесь нет информации о трубах \n ";
			break;
		}
		case 5:
		{
			{if (kv.size())
			{
				cout << "Пожалуйста введите ID KC которую вы хотите отредактировать: ";
				int n;
				cin >> n;
				kv[n].REdaktKC();
			}
			else
				cout << "Здесь нет информации о KC\n ";

			}
			break;
		}
		case 6:
		{
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
					cout <<  "Здесь нет труб и KC\n ";
				}

			}
			
		}
		case 7:
		{
			cout<< "1. Удалить трубу\n2. Удалить КС\nSelect action - ";
			int choice = Utility::proverka(1, 2);
			if (choice == 1)
			{
				Utility::DeleteObject(pipes);
			}
			else
			{
				Utility::DeleteObject(cs);
			}

			break;
		}
		case 8:
		{
			SaveAll(pipes, cs);
			break;
		}
		case 9:
		{
			LoadAll(pipes, cs);
			break;
		}
		case 0:
		{
			return 0;
			break;
		}
		}
	}
	return 0;
}

