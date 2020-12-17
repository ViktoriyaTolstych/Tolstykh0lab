#include "CKC.h"
#include "Cpipe.h"
#include "utility.h"
#include "lib.h"
#include <iostream>
#include <fstream>

using namespace std;

void menu()
{
	cout << "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Показать объекты" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Поиск по фильтру" << endl
		<< "7. Удалить объекты" << endl
		<< "8. Сохранить в файл" << endl
		<< "9. Загрузить из файла" << endl
		<< "0. Выход" << endl
		<< endl << "Выберите действие - ";

}
void EditPipe(unordered_map<int, Cpipe>&pipes)
{
	cout << "1. Изменить все существующие трубы\n2. Изменить одну трубу\nВыберите - ";
	if (Utility::proverka(1, 2) == 1)
	{
		cout << endl;
		Cpipe::EditAllPipes(pipes);
	}
	else
	{
		cout <<endl;
		Cpipe::EditOnePipe(pipes);
	}

}

 void EditCS(unordered_map<int,CKC>&cs)
{
	 cout << "1. Изменить все существующие КС\n2. Изменить одну КС\nВыберите - ";
	 if (Utility::proverka(1, 2) == 1)
	 {
		 cout << endl;
		 CKC::EditAllKC(cs);
	 }
	 else
	 {
		 cout << endl;
		 CKC::EditOneKC(cs);
	 }
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
template <typename N>
void FiltrationPipes(unordered_map<int, Cpipe>& vect, bool(*f)(Cpipe& p, N param), N param)
{
	for (auto& i : vect)
	{
		if (f(i.second, param))
		{
			cout << endl << "id трубы: " << i.second.identificator << std::endl << "диаметр: " << i.second.diametr << std::endl
				<< "длина: " << i.second.dlina << std::endl << "состояние трубы: " << i.second.checkRepair();
		}
	}
	cout << endl;
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
		FiltrationPipes(pipes, SearchByRepair, choice);
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
	 unordered_map <int,Cpipe> pipes;
	 unordered_map <int,CKC> cs;
	while (true)
	{
		menu();
		switch (Utility::proverka(0, 9))
		{
		case 1:
		{
			Cpipe p;
			p.send();
			pipes.insert(pair<int, Cpipe>(pipes.size(), p));
			break;
			
		}
		case 2:
		{
			CKC c;
			c.send();
			cs.insert(pair<int, CKC>(cs.size(), c));
				break;
		}
		case 3:
		{
			Viewall(pipes, cs);
			break;
		}
		case 4:
		{
			EditPipe(pipes);
			break;
		}
		case 5:
		{
			EditCS(cs);
			break;
		}
		case 6:
		{
			cout << "1. Поиск по трубам\n2. Поиск по КС\nSelect action - ";
			if (Utility::proverka(1, 2) == 1)
				SearchByFilterPipes(pipes);
			else
				SearchByFilterCs(cs);
			break;
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

