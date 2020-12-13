#include "CKC.h"
#include "utility.h"
#include <list>
using namespace std;

int CKC::CountKC = 0;


std::istream& CKC::operator>>(std::istream& in, CKC& cs)
{
	cout << "���������� ������� ��� �� n - ";
	cin.ignore();
	getline(cin, cs.name);
	cout << "������� ���������� ����� - ";
	cs.kolvo_tsehov = proverka(0, 1000);
	cout << "������� ��������� ����� � ������ - ";
	cs.kolvo_tsehov_v_rabote = proverka(0, cs.kolvo_tsehov);

	cs.effektivnost = 1. / (rand() % 10);
	cout << endl;
	return in;
}

CKC::CKC()
{
	identificator = CountKC;
	CountKC++;
	cout << "ID ��� ������ �� = " << identificator << endl;
}
