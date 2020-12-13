#include "Cpipe.h"
#include <iostream>
#include <string>
#include "utility.h"
#include <list>

using namespace std;

int Cpipe::CountP = 0;

string Cpipe::checkRepair(Cpipe& p)
{
	return (p.priznak) ? "�� �������� \n\n" : "� ������ \n\n";
}

std::istream& Cpipe::operator>>(istream& in, Cpipe& p)
{
	std::cout << "\n������� ������� ( � ��) - ";
	p.diametr = proverka<double>(0, 10000);
	std::cout << "������� ����� (� � ) - ";
	p.dlina = proverka<double>(0, 10000);
	std::cout << endl;
	return in;
};
	

Cpipe::Cpipe()
{
	identificator = CountP++;
	cout << "ID ��� ������ ����� = " << identificator << endl;
}


std::string checkRepair(const Cpipe& p)
{
	return (p.priznak) ? "Unworking \n\n" : "Working \n\n";

}

