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
	cout << "������ ����� �������";
}
std::string Cpipe::checkRemont(const Cpipe& p)
{
	return (p.priznak) ? "� ������� \n\n" : "�������� \n\n"; 
}
int Cpipe::getID() const
{
	return 0;
}
std::ostream& operator<<(std::ostream& out, const Cpipe& x)
{
	out << "\t�����:\n";
	out << "ID �����: " << x.identificator << endl;
	out << "�����: " << x.dlina << endl;
	out << "�������: " << x.diametr << endl;
	(x.priznak) ? out << "����� �� ��������\n" : out <<" ����� ��������\n";
	return out;
}

std::istream& operator>>(std::istream& in, Cpipe& x)
{
	x.identificator = ++Cpipe::CountP;
	std::cout <<" ������� �����(�):\n";
	x.dlina =Utility::proverka(0, 1000);
	std::cout << "������� �������(��): ";
	x.diametr = Utility::proverka(1, 1000);
	(x.priznak) ? cout << "����� � �������\n" : cout << "����� ��������\n";
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
