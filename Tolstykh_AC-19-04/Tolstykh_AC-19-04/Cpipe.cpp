#include "Cpipe.h"
#include <iostream>
#include <string>
#include "utility.h"

using namespace std;

int Cpipe::CountP = 0;

Cpipe::Cpipe()
{
	identificator = CountP++;
	cout << "ID ��� ������ ����� = " << identificator << endl;
}


std::string checkRepair(const Cpipe& p)
{
	return (p.priznak) ? "Unworking \n\n" : "Working \n\n";

}

