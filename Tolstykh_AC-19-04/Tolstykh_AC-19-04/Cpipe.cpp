#include "Cpipe.h"
#include <iostream>
#include <string>

using namespace std;

int Cpipe::CountP = 0;

Cpipe::Cpipe()
{
	identificator = CountP++;
}


std::string checkRepair(const Cpipe& p)
{
	return (p.priznak) ? "Unworking \n\n" : "Working \n\n";

}

