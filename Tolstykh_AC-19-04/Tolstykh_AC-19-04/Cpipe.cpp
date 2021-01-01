#include "Cpipe.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int Cpipe::CountP = 0;
Cpipe::Cpipe()
{
	identificator = CountP++;
}
int Cpipe::GetCountP()
{
	return CountP;
}
int Cpipe::Getidentificator() const
{
	return identificator;
}
bool Cpipe::Getpriznak() const
{
	return priznak;
}
void Cpipe::setinputks(unsigned int value)
{
	inputks = value;
}
void Cpipe::setoutputks(unsigned int value)
{
	outputks = value;
}
unsigned int Cpipe::getinputks()
{
	return inputks;
}
unsigned int Cpipe::getoutputks()
{
	return outputks;
}
void Cpipe::savefilepipe(std::ofstream& fout)
{
	fout << identificator << endl;
	fout << inputks << endl;
	fout << outputks << endl;
	fout << dlina << endl;
	fout << diametr << endl;
	fout << priznak << endl;
}
void Cpipe::inputfilepipe(std::ifstream& fin)
{
	fin >> identificator;
	fin >> inputks;
	fin >> outputks;
	fin >> dlina;
	fin >> diametr;
	fin >> priznak;
}
void Cpipe::RedaktPipeline()
{
	priznak = !priznak;
	cout << "Статус трубы изменен";
}
std::string Cpipe::checkRemont(const Cpipe& p)
{
	return (p.priznak) ? "В ремонте \n\n" : "Работает \n\n"; 
}
int Cpipe::getID() const
{
	return 0;
}
std::ostream& operator<<(std::ostream& out, const Cpipe& x)
{
	out << "\tТрубы:\n";
	out << "ID трубы: " << x.identificator << endl;
	out << "Длина: " << x.dlina << endl;
	out << "Диаметр: " << x.diametr << endl;
	(x.priznak) ? out << "Труба не работает\n" : out <<" Труба работает\n";
	return out;
}

std::istream& operator>>(std::istream& in, Cpipe& x)
{
	x.identificator = ++Cpipe::CountP;
	std::cout <<" Введите длину(м):\n";
	x.dlina =Utility::proverka(0, 1000);
	std::cout << "Введите диаметр(мм): ";
	x.diametr = Utility::proverka(1, 1000);
	(x.priznak) ? cout << "Труба в ремонте\n" : cout << "Труба работает\n";
	return in;
}

std::ofstream& operator<<(std::ofstream& fout, const Cpipe& x)
{
	fout << x.identificator << endl << x.dlina << endl << x.diametr << endl << x.priznak << endl;
	return fout;
}

std::ifstream& operator>>(std::ifstream& fin, Cpipe& x)
{
	fin >> x.identificator >> x.dlina >> x.diametr >> x.priznak;
	return fin;
}
