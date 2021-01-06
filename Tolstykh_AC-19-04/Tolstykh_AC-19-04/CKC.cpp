#include "CKC.h"

using namespace std;

string name;
int kolvo_tsehov;
int kolvo_tsehov_v_rabote;
float effektivnost;
int CKC::KCMaxId = 0;

std::istream& operator>>(std::istream& in, CKC& cs)
{
	cout << "Введите имя КС n- \n";
	in.ignore();
	getline(in, cs.name);
	std::cout << " Введите число цехов- \n";
	cs.kolvo_tsehov = Utility::proverka(0, 1000);
	cout << "Введите число цехов в работе\n";
	cs.kolvo_tsehov_v_rabote = Utility::proverka(0, cs.kolvo_tsehov);
	cs.effektivnost = 1. / (rand() % 10); 
	return in;
}
ostream& operator<<(std::ostream& out, const CKC& cs)
{
	out << "Имя: " << cs.name << "\n"
		<< "Колво работающих цехов: " << cs.kolvo_tsehov_v_rabote <<"/"<< cs.kolvo_tsehov<< endl
		<< "Эффективность: " << cs.effektivnost << endl;
	return out;

}

void EditAllKC(unordered_map<int, CKC>& cs)
{
	cout << "\n0. Запустить цеха\n1. Остановить цеха\nВыберите - ";
	int choice = Utility::proverka(0, 1);
	cout << endl;
	for (auto& i : cs)
	{
		if (choice == 0 && (i.second.kolvo_tsehov > i.second.kolvo_tsehov_v_rabote))
		{
			i.second.kolvo_tsehov_v_rabote += 1;
		}
		else if (i.second.kolvo_tsehov_v_rabote > 0)
		{
			i.second.kolvo_tsehov_v_rabote -= 1;
		}
	}

}


void CKC::Save(ofstream& fout)
{
	fout << name << endl
		<< kolvo_tsehov << endl
		<< kolvo_tsehov_v_rabote << endl
		<< effektivnost << endl;
}

void CKC::Load(ifstream& fin)
{
	fin >> name
		>> kolvo_tsehov
		>> kolvo_tsehov_v_rabote
		>> effektivnost;
}

string CKC::Getname() const
{
	return name;
}

int CKC::Getkolvo_tsehov() const
{
	return kolvo_tsehov;
}

int CKC::Getkolvo_tsehov_v_rabote() const
{
	return kolvo_tsehov_v_rabote;
}

float CKC::Geteffektivnost() const
{
	return effektivnost;
}

void CKC::RedaktKC()
{
	cout << "\n0. Начать работу цеха\n1. Остановить работу цеха\nSelect - ";
	if (Utility::proverka(0, 1) == 0)
	{
		if (kolvo_tsehov > kolvo_tsehov_v_rabote)
			kolvo_tsehov_v_rabote += 1;
	}
	else
	{
		if (kolvo_tsehov_v_rabote > 0)
			kolvo_tsehov_v_rabote -= 1;
	}

}

CKC::CKC()
{
	string name = " ";
	int kolvo_tsehov = 0;
	int kolvo_tsehov_v_rabote = 0;
	float effektivnost = 0;

}








