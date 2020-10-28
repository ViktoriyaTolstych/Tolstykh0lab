#include <iostream> 
#include <fstream>
using namespace std;
struct pipe 
{
	int identificator;
	float dlina;
	float diametr;
	bool priznak;

};
struct KC
{   int identificator;
	string name;
	int kolvo_tsehov;
	int kolvo_tsehov_v_rabote;
	float effektivnost;
};
int proverka(int min, int max)
{
int p = 0;
do
{
	cin.clear();
	cin.ignore(10000, '\n');
	cout << "Введите пожалуйста коррректные данные: " << endl;
} while (!(cin >> p) || p > max || p < min);

	return p;
}

bool isNumber(char Symbol)
{
	if (Symbol >= '0' && Symbol <= '9')
		return true;
	return false;

};
pipe createpipe ()
{
	pipe p;
	p.identificator = 100;
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Определите пожалуйста признак в ремонте(1-в ремонте или 0-не в ремонте): " << endl;
		cin >> p.priznak;
	} 
	while (cin.fail()|| isNumber(p.priznak));
	
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите пожалуйста длину трубы(>0) : " << endl;
	    cin>> p.dlina;
	}
	while (cin.fail() || p.dlina <= 0||isNumber(p.dlina)); 

	do
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Введите пожалуйста диаметр трубы(>0)" << endl;
		cin >> p.diametr;
	} 
	while (cin.fail() || p.diametr <=
		0|| isNumber(p.diametr));
	return p;
};
KC createKC()
{
	KC k;
	k.identificator = 100;
	k.effektivnost =(float(k.kolvo_tsehov) - float(k.kolvo_tsehov_v_rabote)) / float((k.kolvo_tsehov));
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите пожалуйста наименование КС : " << endl;
		cin >> k.name;
	}
		while (cin.fail());
	do
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите пожалуйста количество цехов(>=1)" << endl;
		cin >> k.kolvo_tsehov;
	}
	while (cin.fail()|| k.kolvo_tsehov<1||isNumber(k.kolvo_tsehov));
	do
	{
		cout << "Введите пожалуйста количество цехов в работе" << endl;
		cin >> k.kolvo_tsehov_v_rabote;
	}
	while (cin.fail() || k.kolvo_tsehov_v_rabote > k.kolvo_tsehov||isNumber(k.kolvo_tsehov_v_rabote));
	
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
		cout<<"Труба не в ремонте\n'";
	}
	else
	{
		p.priznak = 1;
		cout << "Труба в ремонте\n'";
	}
}
void EditKC(KC& k)
{
	cout << "\n1.Цех в работе";
	cout << "\n2.Цех не в работе";
	cout << "\n3.Необходимо выбрать:";
	int choice;
	cin >> choice;
	if (choice == 1)
	{
		k.kolvo_tsehov_v_rabote += 1;
	}
	else
	{
		k.kolvo_tsehov_v_rabote -= 1;
	}
}
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
	fout.open("datapipe.txt", ios::out);
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
void saveall(int s, const pipe& pi, const KC&st)
{
	switch (s)
	{
	case 1:
		Savepipe(pi);
		break;
	case 2:
		SaveKC(st);
		break;
	case 3 :
		save(pi, st);
	}
}

pipe Loadpipe()
{
	pipe p;
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
}
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
void loadall(int l)
{
	switch (l)
	{
	case 1:
		Viewpipe(Loadpipe());
		break;
	case 2:
		ViewKC(LoadKC());
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

	int main()
	{
		setlocale(LC_ALL, "Russian");
		pipe pi;
		KC st;
		while (1)
		{
			PrintMenu();

			switch (proverka(0, 7))
			{
			case 1:
			{
				pi = createpipe();
				break;
			}
			case 2:
			{
				st = createKC();
				break;
			}
			case 3:
			{
				cout << "Выберите пожалуйста нужный вариант. 1-pipe, 2- KC ";
				int v = 0;
				cin >> v;
				viewall(v, pi, st);
				break;
			}

			case 4:
			{
				Editpipe(pi);
				break;
			}
			case 5:
			{
				EditKC(st);
				break;
			}
			case 6:
			{
				cout << "Выберите поджалуйста нужное :1-pipe, 2- KC, 3-all ";
				int s = 0;
				cin >> s;
				saveall(s, pi, st);
				break;
			}
			case 7:
			{
				cout << "Выберите пожалуйста нужный вариант. 1 - pipe, 2 - KC";
				int l = 0;
				cin >> l;
				loadall(l);
				break;
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


