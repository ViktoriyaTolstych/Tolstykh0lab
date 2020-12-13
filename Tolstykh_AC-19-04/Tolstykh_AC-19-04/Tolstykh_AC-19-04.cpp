#include <iostream> 
#include <fstream>
#include <string>
#include "CKC.h"
#include "Cpipe.h"
#include "utility.h"
#include <map>

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
//void EditAllPipes(const unordered_map<int, Cpipe>& p, const unordered_map<int, CKC>& c)
//{
//	std:: cout << "0. Труба в работе\n1. Труба не в работе\nВыберите - ";
//	int choice = proverka(0, 1);
//	std::cout << endl;
//	for (Cpipe& i : p)
//	{
//		i.priznak = choice;
//	}
//
//}
void EditOnePipe(map<int,Cpipe>& pipes)
{
	cout << "Введите id который вы хотите изменить: ";
	int k;
	cin >> k;

	cout << "0.Труба в работе \n1. Труба не в работе\nВыберите - " << endl;
	int choice = proverka(0, 1);

	pipes[k].priznak = choice;
}
void EditPipe(const unordered_map<int, Cpipe>& pipes)
{
	cout << "1. Изменить все существующие трубы\n2. Изменить одну трубу\nВыберите - ";
	if (proverka(1, 2) == 1)
	{
		cout << endl;
		EditAllPipes(pipes);
	}
	else
	{
		cout << endl;
		EditOnePipe(pipes);
	}
}

 int EditAllKC(const unordered_map<int, CKC>&  cs)
{
	std::cout << "\n0. Запустить цеха\n1. Остановить цеха\nВыберите - ";
	int choice = proverka(0, 1);
	std::cout << endl;
	for (CKC& i : cs)
	{
		if (choice == 0 && (i.kolvo_tsehov > i.kolvo_tsehov_v_rabote))
		{
			i.kolvo_tsehov_v_rabote += 1;
		}
		else if (i.kolvo_tsehov_v_rabote > 0)
		{
			i.kolvo_tsehov_v_rabote -= 1;
		}
	}
	return cs;
}
vector<int> EditOneKC(const unordered_map<int, CKC>& cs)
{
	cout << "Id КС которую вы хотите изменить: ";
	int k;
	cin >> k;
	cout << "\n0. Начать работу цеха\n1. Остановить работу цеха\nВыберите - ";
	if (proverka(0, 1) == 0)
	{
		if (cs[k].kolvo_tsehov > cs[k].kolvo_tsehov_v_rabote)
			cs[k].kolvo_tsehov_v_rabote += 1;
	}
	else
	{
		if (cs[k].kolvo_tsehov_v_rabote > 0)
			cs[k].kolvo_tsehov_v_rabote -= 1;
	}
	return cs;
}
void EditCS(const unordered_map<int, CKC>& cs)
{
	{
		std::cout << "1. Изменить КС\n2. Изменения КС больше не требуются\nВыберите - ";
		do
		{
			std::cout << endl;
			EditOneKC(cs);
		} while ((proverka(1, 2) == 2));

	}
	
void Viewall(const unordered_map <int, Cpipe>&pipes, const unordered_map <int,CKC>&c)
{
	cout << "1. Просмотр всего\n" << "2. Просмотр труб\n" << "3. Просмотр КС\nВыберите - ";
	switch (proverka(1, 3))
	{
	case 1:
	{
		cout << endl;
		for (Cpipe p : pipes)
		{
			cout << " id трубы: " << p.identificator << std::endl << "димаетр:: " << p.diametr << std::endl
				<< "длина: " << p.dlina << std::endl << "состояние трубы:: " << checkRepair(p);
		}
		for (CKC cs : c)
		{
			cout.precision(2);
			cout << "\nКС id: " << cs.identificator << endl << "Имя: " << cs.name
				<< endl << "Количество цехов: " << cs.kolvo_tsehov << endl
				<< "Количество цехов в работе: " << cs.kolvo_tsehov_v_rabote << endl
				<< "Эффективность: " << cs.effektivnost << endl << endl;
		}
		break;
	}
	case 2:
	{
		cout << "Выберите id который вы хотите вывести: ";
		int OutPipe;
		cin >> OutPipe;
		cout << " id трубы : " << pipes[OutPipe].identificator << endl << "диаметр: " << pipes[OutPipe].diametr << endl
			<< "длина: " << pipes[OutPipe].dlina << endl << "состояние трубы: " << checkRepair(pipes[OutPipe]);
		break;
	}
	case 3:
	{
		cout << "Выберите id который вы хотите вывести: ";
		int OutKC;
		cin >> OutKC;
		cout.precision(2);
		cout << "\nКС id: " << c[OutKC].identificator << endl << "Имя: " << c[OutKC].name
			<< endl << "Количесвто цехов: " << c[OutKC].kolvo_tsehov << endl
			<< "Количество цехов в работе: " << c[OutKC].kolvo_tsehov_v_rabote << endl
			<< "Эффективность: " << c[OutKC].effektivnost << endl << endl;;
		break;
	}
	}
}
void SaveAll(const unordered_map<int,Cpipe>& p, const unordered_map<int,CKC>& i)
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
			for (const auto& p : pipes)
			{
				fout << p.identificator << endl << p.diametr << endl 
					<< p.dlina << endl << p.priznak << endl << endl;
			}
			for (const auto& i : cs)
			{
				/*fout.precision(2);*/
				fout << i.identificator << endl << i.name << endl << i.kolvo_tsehov << endl
					<< i.kolvo_tsehov_v_rabote << endl << i.effektivnost << endl << endl;
			}
			cout << "Сохранено\n\n";
		}
		fout.close();
	}
}
void LoadAll(const unordered_map<int, Cpipe>& p, const unordered_map<int, CKC>& cs)
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
		pipes.resize(lenpipe);
		cs.resize(lencs);
		for (Cpipe& p : pipes)
		{
			fin >> p.identificator;
			fin >> p.diametr;
			fin >> p.dlina;
			fin >> p.priznak;
		}
		for (CKC& c : cs)
		{
			fin >> c.identificator;
			fin >> c.name;
			fin >> c.kolvo_tsehov;
			fin >> c.kolvo_tsehov_v_rabote;
			fin >> c.effektivnost;
		}
		fin.close();
		cout << "Data downloaded\n\n";
	}
}
bool SearchById(Cpipe& p, int param)
{
	return p.identificator == param;
}
bool SearchByRepair(Cpipe& p, int param)
{
	return p.priznak == param - 1;
}
bool SearchByName(CKC& cs, string name)
{
	return cs.name == name;
}
bool SearchByPercent(CKC& cs, int param)
{
	return 100 * (1 - (1. * cs.kolvo_tsehov_v_rabote) / cs.kolvo_tsehov) >= param;
}
template <typename N>
void FiltrationPipes(list<Cpipe>& vect, bool(*f)(Cpipe& p, N param), N param)
{
	for (Cpipe& i : vect)
	{
		if (f(i, param))
		{
			cout << endl << "id трубы: " << i.identificator << std::endl << "диаметр: " << i.diametr << std::endl
				<< "длина: " << i.dlina << std::endl << "состояние трубы: " << checkRepair(i);
		}
	}
	cout << endl;
}
template <typename N>
void FiltrationCs( list<CKC>& map, bool(*f)(CKC& p, N param), N param)
{
	for (CKC& i : vect)
	{
		if (f(i, param))
		{
			cout.precision(2);
			cout << "\nКС id: " << i.identificator << endl << "Имя: " << i.name
				<< endl << "Количество цехов: " << i.kolvo_tsehov << endl
				<< "Количество цехов в работе: " << i.kolvo_tsehov_v_rabote << endl
				<< "Эффективность: " << i.effektivnost << endl << endl;
		}
	}
	cout << endl;
}
void SearchByFilterPipes(const unordered_map<Cpipe>& pipes)
{
	cout << "\n1. По ID\n2. По состоянию\nВыберите действие - ";
	if (proverka(1, 2) == 1)
	{
		cout << "Введите ID: ";
		int ch = proverka(0, 100);
		FiltrationPipes(pipes, SearchById, ch);
	}
	else
	{
		cout << "\n1. В работе\n2. Не в работе\nВыберите действие - ";
		int choice = proverka(1, 2);
		FiltrationPipes(pipes, SearchByRepair, choice);
	}
}
void SearchByFilterCs(const unordered_map<CKC>& cs)
{
	cout << "\n1. По имени\n" << "2. По проценту неиспользованных цехов\nSelect action - ";
	if (proverka(1, 2) == 1)
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
		int choice = proverka(0, 100);
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
		switch (proverka(0, 9))
		{
		case 1:
		{
			while (1) {
				Cpipe pipe;
				cin >> p;
				pipes.insert({ p.Getid(), p });
				cout << "Добавить еще?" << endl << "\t 0. Нет" << endl << "\t 1. Да" << endl;
				if (get_value(0, 1) == 0)
					break;
			
		}
		case 2:
		{
			CKC c;
			cin >> c;
			cs.insert({ c.Getid(), c });
			cout << "Добавить еще?" << endl << "\t 0. Нет" << endl << "\t 1. Да" << endl;
			if (get_value(0, 1) == 0)
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
			if (proverka(1, 2) == 1)
				SearchByFilterPipes(pipes);
			else
				SearchByFilterCs(cs);
			break;
		}
		case 7:
		{
			DeleteObject(pipes, cs);
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

