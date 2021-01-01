#include "CKC.h"
#include "utility.h"
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std;

int CKC::CountKC = 0;
static int CountKC;

int CKC::GetCountKC()
{
	return CountKC;
}

int CKC::Getidentificator() const
{
	return identificator;
}
int CKC::getID() const
{
	return identificator;
}
std::istream& operator>>(std::istream& in, CKC& y)
{
	y.identificator = ++CKC::CountKC;
	std::cout << "������� ��� �� \n";
	cin.ignore();
	getline(cin, y.name);
	std::cout << " ������� ���� ����� \n";
	y.kolvo_tsehov = Utility::proverka(0, 1000);
	std::cout << "������� ����� ����� � �������\n";
	y.kolvo_tsehov_v_rabote = Utility::proverka(1, y.kolvo_tsehov);
	std::cout << "������� ������������� (1-10)\n";
	y.effektivnost = Utility::proverka(1, 10);
	return in;
}
std::ostream& operator<<(std::ostream& out, const CKC& y)
{
	out << "\tKC\n";
	out << " ID KC: " << y.identificator << endl
		<< "����� �����: " << y.kolvo_tsehov << endl
		<< "����� ���������� �����: " << y.kolvo_tsehov_v_rabote << endl
		<< "�������������: " << y.effektivnost << endl;
	return out;

}
std::ofstream& operator<<(std::ofstream& fout, const CKC& y)
{
	fout << y.identificator << endl
		<< y.kolvo_tsehov << endl
		<< y.kolvo_tsehov_v_rabote << endl
		<< y.effektivnost << endl;
	return fout;
}

std::ifstream& operator>>(std::ifstream& fin, CKC& y)
{
	fin >> y.identificator >> y.kolvo_tsehov >> y.kolvo_tsehov_v_rabote >> y.effektivnost;
	return fin;
}


void CKC::RedaktKC()
{
	cout << "�� ������ �������� ����� ���������� �����?\n";
	char i;
	cin >> i;
	while (i != '��' && i != '���')
	{
		cout << " ������� �� ��� ���: ";
		cin >> i;
	}
	switch (i)
	{
	case '��':
	{
		cout << "������� ����� ���������� �����: ";
		int vsego = kolvo_tsehov;
		kolvo_tsehov_v_rabote = Utility::proverka(0, vsego);
		cout << "���������� �������� \n";
		break;
	}
	case '���':
	{
		break;
	}
	}
}








