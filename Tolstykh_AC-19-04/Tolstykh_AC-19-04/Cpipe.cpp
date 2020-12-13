#include "Cpipe.h"
#include <iostream>
#include <string>
#include "utility.h"
#include <list>

using namespace std;

int Cpipe::CountP = 0;

string Cpipe::checkRepair(Cpipe& p)
{
	return (p.priznak) ? "Не работает \n\n" : "В работе \n\n";
}

std::istream& Cpipe::operator>>(istream& in, Cpipe& p)
{
	std::cout << "\nВведите диаметр ( в мм) - ";
	p.diametr = proverka<double>(0, 10000);
	std::cout << "Введите длину (в м ) - ";
	p.dlina = proverka<double>(0, 10000);
	std::cout << endl;
	return in;
};
	

Cpipe::Cpipe()
{
	identificator = CountP++;
	cout << "ID для данной трубы = " << identificator << endl;
}


std::string checkRepair(const Cpipe& p)
{
	return (p.priznak) ? "Unworking \n\n" : "Working \n\n";

}

