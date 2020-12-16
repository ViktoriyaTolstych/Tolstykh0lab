#include "Cpipe.h"
#include "Utility.h"

using namespace std;

int Cpipe::CountP = 0;
Cpipe::Cpipe()
{
	identificator = CountP++;
}
std::unordered_map<int, Cpipe> Cpipe::EditOnePipe(std::unordered_map<int, Cpipe>& pipes)
{
	cout << "Введите id который вы хотите изменить: ";
	int k;
	cin >> k;
	cout << "0.Труба в работе \n1. Труба не в работе\nВыберите - ";
	int choice = Utility::proverka(0, 1);
	pipes[k].priznak = choice;
	cout << endl;
	return pipes;

}
void Cpipe::EditAllPipes(std::unordered_map<int, Cpipe>& pipes)
{
	cout << "0. Труба в работе\n1. Труба не в работе\nВыберите - ";
	int choice = Utility::proverka(0, 1);
	cout << endl;
	for (auto& i : pipes)
	{
		i.second.priznak = choice;
	}
}



void Cpipe::send()
{
	std::cout << "\nВведите диаметр ( в мм) - ";
	diametr = Utility::proverka<double>(0, 10000);
	std::cout << "Введите длину (в м ) - ";
	dlina = Utility::proverka<double>(0, 10000);
	std::cout << endl;
}
std::string Cpipe::checkRepair()
{
	return (priznak) ? "Не в работе \n\n" : "В работе \n\n";
}







