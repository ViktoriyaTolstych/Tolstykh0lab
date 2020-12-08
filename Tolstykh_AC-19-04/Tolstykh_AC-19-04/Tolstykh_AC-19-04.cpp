#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include "CKC.h"
#include "Cpipe.h"
using namespace std;
template<typename T>
T proverka(T less, T more)
{
	T x;
	while ((cin >> x).fail() || x > more || x < less)
		{
		cout<<"Пожалуйста введите корректные данные"
			cin.clear();
			cin.ignore(10000, '\n');
		}
	return x;
}
std::istream& operator>>(std::istream& in, CKC& cs)
{
	cout << "Enter the name of the compressor station - ";
	cin.ignore();
	getline(cin, cs.name);

	cout << "Enter the number of workshops - ";
	cs.kolvo_tsehov = proverka(0, 1000);
	cout << "Enter the number of workshop workers - ";
	cs.kolvo_tsehov_v_rabote = proverka(0, cs.kolvo_tsehov);

	cs.effektivnost = 1. / (rand() % 10);
	cout << endl;
	return in;
}

std::istream& operator>> (std::istream& in, Cpipe& p)
{
	std::cout << "\nEnter the diameter in millimeters - ";
	p.diametr = proverka<double>(0, 10000);
	std::cout << "Enter the length in meters - ";
	p.dlina = proverka<double>(0, 10000);
	std::cout << endl;
	return in;
}
void menu()
{
	cout << "1. Add pipe" << endl
		<< "2. Add compressor station" << endl
		<< "3. Show objects" << endl
		<< "4. Edit pipe" << endl 
		<< "5. Edit compressor station" << endl 
		<< "6. Search by filter" << endl
		<< "7. Delete object" << endl 
		<< "8. Save to file" << endl
		<< "9. Download from file" << endl
		<< "0. Exit" << endl 
		<< endl << "Selected action - ";

}
template<typename C>
ostream& operator << (ostream& out, const vector<C>& object)// non pc
{
	for (const C& i : object)
	{
		out << i;
	}
	return out;
}
template<typename C>
ofstream& operator << (ofstream& fout, const vector<C>& object)
{
	for (const C& c : object)
	{
		fout << c;
	}
	return fout;
}
template <typename C>
ifstream& operator >> (ifstream& in, vector<C>& object)
{
	for (C& c : object)
	{
		in >> c;
	}
	return in;
}

string checkRepair(Cpipe& p)//rename and class
{
	return (p.priznak) ? "Unworking \n\n" : "Working \n\n";
}
void EditAllPipes(vector<Cpipe>& pipes)
{
	cout << "0. Pipes working\n1. Pipes in repair\nChoose - ";
	int choice = proverka(0, 1);
	cout << endl;
	for (Cpipe& i : pipes)
	{
		i.priznak = choice;
	}
}
vector<Cpipe> EditOnePipe(vector<Cpipe>& pipes)
{
	cout << "Select id you want to edit: ";
	int k;
	cin >> k;
	cout << "0. Pipe working\n1. Pipe in repair\nChoose - ";
	int choice = proverka(0, 1);
	pipes[k].priznak = choice;
	cout << endl;
	return pipes;
}
void EditPipe(vector<Cpipe>& pipes)
{
	cout << "1. Edit all existing ones\n2. Edit one pipe\nSelect - ";
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

vector<CKC> EditAllKC(vector<CKC>& cs)
{
	cout << "\n0. Start the workshop\n1. Stop the workshop\nSelect - ";
	int choice = proverka(0, 1);
	cout << endl;
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
vector<CKC> EditOneKC(vector<CKC>& cs)
{
	cout << "Id of the compressor station you want to edit: ";
	int k;
	cin >> k;
	cout << "\n0. Start the workshop\n1. Stop the workshop\nSelect - ";
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
void EditCS(vector<CKC>& cs)
{
	cout << "1. Edit all existing ones\n2. Edit one cs\nSelect - ";
	if (proverka(1, 2) == 1)
	{
		cout << endl;
		EditAllKC(cs);
	}
	else
	{
		cout << endl;
		EditOneKC(cs);
	}

}
void Viewall(vector<Cpipe> pipes, vector<CKC> c)
{
	cout << "1. View all\n" << "2. View pipe\n" << "3. View compressor stations\nSelect - ";
	switch (proverka(1, 3))
	{
	case 1:
	{
		cout << endl;
		for (Cpipe p : pipes)
		{
			cout << "Pipe id: " << p.identificator << std::endl << "diametr: " << p.diametr << std::endl
				<< "length: " << p.dlina << std::endl << "pipe condition: " << checkRepair(p);
		}
		for (CKC cs : c)
		{
			cout.precision(2);
			cout << "\nCS id: " << cs.identificator << endl << "Name: " << cs.name
				<< endl << "Quantity of workshops: " << cs.kolvo_tsehov << endl
				<< "Quantity of workshop workers: " << cs.kolvo_tsehov_v_rabote << endl
				<< "Efficiency: " << cs.effectivnost << endl << endl;
		}
		break;
	}
	case 2:
	{
		cout << "Select id you want to output: ";
		int OutPipe;
		cin >> OutPipe;
		cout << "Pipe id: " << pipes[OutPipe].identificator << endl << "diametr: " << pipes[OutPipe].diametr << endl
			<< "length: " << pipes[OutPipe].dlina << endl << "pipe condition: " << checkRepair(pipes[OutPipe]);
		break;
	}
	case 3:
	{
		cout << "Select id you want to output: ";
		int OutKC;
		cin >> OutKC;
		cout.precision(2);
		cout << "\nCS id: " << c[OutKC].identificator << endl << "Name: " << c[OutKC].name
			<< endl << "Quantity of workshops: " << c[OutKC].kolvo_tsehov << endl
			<< "Quantity of workshop workers: " << c[OutKC].kolvo_tsehov_v_rabote << endl
			<< "Efficiency: " << c[OutKC].effektivnost << endl << endl;;
		break;
	}
	}
}
void SaveAll(vector<Cpipe>& pipes, vector<CKC>& cs)
{
	ofstream fout;
	string name;
	cout << "Enter name file: ";
	cin >> name;
	fout.open(name, ios::out);
	if (fout.is_open())
	{
		fout << pipes.size() << endl;
		fout << cs.size() << endl;
		fout << endl;

		if (pipes.size() != 0 || cs.size() != 0)
		{
			for (const Cpipe& p : pipes)
			{
				fout << p.identificator << endl << p.diametr << endl
					<< p.dlina << endl << p.priznak << endl << endl;
			}
			for (const CKC& i : cs)
			{
				fout.precision(2);
				fout << i.identificator << endl << i.name << endl << i.kolvo_tsehov << endl
					<< i.kolvo_tsehov_v_rabote << endl << i.effektivnost << endl << endl;
			}
			cout << "Saved\n\n";
		}
		fout.close();
	}
}
void LoadAll(vector<Cpipe>& pipes, vector<CKC>& cs)
{
	ifstream fin;
	string name;
	cout << "Enter name file: ";
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

pipe createpipe ()
{
	pipe p;
	p.is_pipe == true;
	p.identificator = 100;
	p.priznak = proverka (0,1, "\n'Введите пожалуйста значения признака (в ремонте) : ");
	p.dlina = proverka(1, 1000, "\n'Введите пожалуйста длину трубы(>0) : ");
   p.diametr= proverka(1, 1000, "\n'Введите пожалуйста диамтер трубы(>0) : ");
	return p;
};
KC createKC()
{
	KC k;
	k.is_KC == true;
	k.identificator = 100;
	cout << "Введите пожалуйста наименование КС : " << endl;
	getline(cin, k.name);
	cin >> k.name;
	 k.effektivnost= proverka(1,100,"\'Введите пожалуйста значение эффективности:");
	k.kolvo_tsehov=proverka(1,10000, "Введите пожалуйста количество цехов(>=1)");
	 k.kolvo_tsehov_v_rabote=proverka(1,k.kolvo_tsehov, "Введите пожалуйста количество цехов в работе");

   return k;	
};
void Viewpipe(const pipe& p)
{
	
		cout << "\nidentificator:" << p.identificator << endl;
		cout << "dlina:" << p.dlina << endl;
		cout << "diametr:" << p.diametr << endl;
		cout << "priznak:" << p.priznak << endl;
	}
void ViewKC(const KC& k)
{
		cout << "\nidentificator:" << k.identificator << endl;
		cout << "name:" << k.name << endl;
		cout << "kolvo_tsehov:" << k.kolvo_tsehov << endl;
		cout << "kolvo_tsehov_v_rabote:" << k.kolvo_tsehov_v_rabote << endl;
		cout << "effektivnost:" << k.effektivnost << endl;
}
void viewall(int v, const pipe& pi,const KC & st)
{
	switch (v)
	{
	case 1:
		Viewpipe(pi);
		break;
	case 2:
		ViewKC(st);
		break;
	}
	
}

void Editpipe(pipe& p)

{
	if (p.priznak == 1)
	{
		p.priznak = 0;
		cout << "\nТруба не в ремонте";
	}
	else
	{
		p.priznak = 1;
		cout << "\nТруба в ремонте";
	}
};

void EditKC(KC& k)
{
	cout << "\n1.Цех в работе";
	cout << "\n2.Цех не в работе";
	cout << "\n3.Необходимо выбрать:";
	int choice;
	cin >> choice;
	do {
		if (choice == 1)
		{
			k.kolvo_tsehov_v_rabote += 1;
		}
		else
		{
			k.kolvo_tsehov_v_rabote -= 1;
		}
	} while (cin.fail() || isNumber(int(choice)));

}; 
void Savepipe(const pipe& p)
{
	ofstream fout;
	fout.open("datapipe.txt", ios::out);
	if (fout.is_open())
	{

		fout << "Identificator:" << p.identificator << endl;
		fout << "Dlina:" << p.dlina << endl;
		fout << "Diametr" << p.diametr << endl;
		fout << "Priznak" << p.priznak << endl;
		fout.close();
	}
}
void SaveKC(const KC& k)
{
	ofstream fout;
	fout.open("dataKC.txt", ios::out);
	if (fout.is_open())
	{
		fout << "Identificator:" << k.identificator << endl;
		fout << "Name:" << k.name << endl;
		fout << "Kolvo tsehov:" << k.kolvo_tsehov << endl;
		fout << "Kolvo tsehov v rabote:" << k.kolvo_tsehov_v_rabote << endl;
		fout << "Effektivnost:" << k.effektivnost << endl;
		fout.close();
	}
}
void save(const pipe& p, const KC& k)
{
	ofstream fout;
	fout.open("dataall.txt", ios::out);
	if (fout.is_open())
	{
		fout << "Identificator:" << p.identificator << endl;
		fout << "Dlina:" << p.dlina << endl;
		fout << "Diametr" << p.diametr << endl;
		fout << "Priznak" << p.priznak << endl;
		fout << "Identificator:" << k.identificator << endl;
		fout << "Dlina:" << p.dlina << endl;
		fout << "Diametr" << p.diametr << endl;
		fout << "Priznak" << p.priznak << endl;
		fout.close();
	}

	}
void saveall(int s, const pipe& pi, const KC& st)
{
	switch (s)
	{
	case 1:
		Savepipe(pi);
		break;
	case 2:
		SaveKC(st);
		break;
	case 3:
		save(pi, st);
	}
}

pipe Loadpipe()
     {pipe p;
		ifstream fin;
		fin.open("datapipe.txt", ios::in);
		if (fin.is_open())
		{
			fin >> p.dlina;
			fin >> p.diametr;
			fin >> p.priznak;
			fin.close();
			return p;
		}
	};

KC LoadKC()
{
	KC k;
	ifstream fin;
	fin.open("dataKC.txt", ios::in);
	if (fin.is_open())
	{
		fin >> k.name;
		fin >> k.kolvo_tsehov;
		fin >> k.kolvo_tsehov_v_rabote;
		fin >> k.effektivnost;
		fin.close();
		return k;
	}
}
void Load(pipe& p, KC& k)
{
	ifstream fin;
	fin.open("dataall.txt", ios::in);
	if (fin.is_open())
	{
		fin >> p.dlina;
		fin >> p.diametr;
		fin >> p.priznak;
		fin >> k.name;
		fin >> k.kolvo_tsehov;
		fin >> k.kolvo_tsehov_v_rabote;
		fin >> k.effektivnost;
	}
	fin.close();
}

void loadall(pipe&p, KC&k)
{
	switch (proverka(1,3,"\nВыберите 1-труба,2-КС,3-вместе :  "))
	{
	case 1:
		Viewpipe(Loadpipe());
		break;
	case 2:
		ViewKC(LoadKC());
		break;
	case 3:
		Load(p,k);
		break;
	}
}


	void PrintMenu()
{
	cout << "1.Труба" << endl
		<< "2.Компрессорная станция" << endl
		<< "3.Просмотреть" << endl
		<< "4.Редактирование трубы" << endl
		<< "5.Редактирование КС" << endl
		<<"6.Сохранить"<< endl
		<< "7.Загрузить"<< endl
		<< "0.Выйти" << endl;
}
	pipe& Selectpipe(vector<pipe>&g1)
	{
		unsigned int index = proverka(0u, g1.size(), "Введите индекс для трубы: ");
		return g1[index - 1];
	}
	KC& SelectKC(vector<KC>& g2)
	{
		unsigned int index = proverka(0u, g2.size(), "Введите индекс для КС: ");
		return g2[index - 1];
	}

	int main()
	{
		setlocale(LC_ALL, "Russian");
		vector  <pipe> group1;
		vector <KC> group2;
		/*pipe pi;
		KC st;*/
		bool is_pipe = 0;
		bool is_KC =0;
		while (1)
		{
			PrintMenu();

			switch (proverka(0, 7, "Меню:"))
			{
			case 1:
			{
				pipe pi;
				pi = createpipe();
				group1.push_back(pi);
				is_pipe == true;
				break;
			}
			case 2:
			{
				KC st;
				st = createKC();
				is_KC == true;
				break;
			}
		
			case 3:
				if (is_pipe == true && is_KC == true )
				{
					{
						cout << "Выберите пожалуйста нужный вариант. 1-pipe, 2- KC ";
						int v = 0;
						cin >> v;
						viewall(v, pi, st);
						break;
					}
				}
				else
				{
					cout << "Введите пожалуйста данные для пунктов 1,2";
				}

			case 4:
			{
				if (is_pipe == true)
				{
					Editpipe(Selectpipe(group1));
					break;
				}
			}
			case 5:
			{
				if (is_KC == true)
				{
					EditKC(SelectKC(group2));
					break;
				}
			}
			case 6:
			{
				if (is_pipe == true && is_KC == true)
				{
					cout << "Выберите поджалуйста нужное :1-pipe, 2- KC, 3-all : ";
					int s = 0;
					cin >> s;
					for ();
					saveall(s, pi, st);
					break;
				}
	
			}
			case 7:
			{
				if (is_pipe == true && is_KC == true)
				{
				loadall(pi,st);
				break;
				}
				
			}
			case 0:
			{
				return 0;
			}
			default:
			{
				cout << "Возникла ошибка" << endl;
			}

			}
		}

		return 0;
	}


