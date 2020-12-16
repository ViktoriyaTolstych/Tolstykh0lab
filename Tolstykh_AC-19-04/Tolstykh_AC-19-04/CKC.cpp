#include "CKC.h"
#include "utility.h"
using namespace std;

int CKC::CountKC = 0;

std::unordered_map<int, CKC> CKC::EditOneKC(std::unordered_map<int, CKC>& cs)
{
	cout << "Id КС которую вы хотите изменить: ";
	int k;
	cin >> k;
	cout <<"\n0. Начать работу цеха\n1. Остановить работу цеха\nSelect - ";
	if (Utility::proverka(0, 1) == 0)
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


void CKC::send()
{
	cout << "Пожалуйста введите имя КС n - ";
	cin.ignore();
	getline(cin, name);
	cout << "Введите количество цехов - ";
	kolvo_tsehov = Utility::proverka(0, 1000);
	cout <<"Введите количесво цехов в работе - ";
	kolvo_tsehov_v_rabote = Utility::proverka(0, kolvo_tsehov);

	effektivnost = 1. / (rand() % 10);
	cout <<endl;
}
std::unordered_map<int, CKC> CKC::EditAllKC(std::unordered_map<int, CKC>& cs)
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
	return cs;
}


CKC::CKC()
{
	identificator = CountKC;
	CountKC++;
	cout << "ID для данной КС = " << identificator << endl;
}




