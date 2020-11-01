#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
using namespace std;
template<typename T>
T proverka(T min, T max, string h)
{
	T x;
	cout << h;
	while ((cin >> x).fail() || x > max || x < min)
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << h;
		}
	return x;
}
struct pipe 
{
	int identificator;
	float dlina;
	float diametr;
	bool priznak;
	bool is_pipe;

};
struct KC
{   int identificator;
	string name;
	int kolvo_tsehov;
	int kolvo_tsehov_v_rabote;
	float effektivnost;
	bool is_KC;
};
 bool isNumber(char Symbol) 
 {if (Symbol >= '0' && Symbol <= '9')
		return true;
	return false;

};
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
					for ()
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


