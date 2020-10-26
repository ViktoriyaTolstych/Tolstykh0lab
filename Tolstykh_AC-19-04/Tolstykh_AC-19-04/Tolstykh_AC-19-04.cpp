#include <iostream> 
#include <fstream>
using namespace std;
struct pipe
{
	int identificator;
	float dlina;
	float diametr;
	bool priznak;

};
struct KC
{
	int identificator ;
	string name;
 int kolvo_tsehov;
 int kolvo_tsehov_v_rabote;
 float effektivnost;
};

pipe createpipe ()
{
	pipe p;
	p.identificator = 100;
	cout << "Введите пожалуйста длину трубы : " << endl ;
	cin >> p.dlina ; 
	cout << "Введите пожалуйста диаметр трубы" << endl;
	cin >> p.diametr;
	cout << "Введите пожалуйста признак трубы" << endl;
	cin >> p.priznak;
	return p;
};
KC createKC()
{
	KC k;
	k.identificator = 100;
	cout << "Введите пожалуйста наименование КС : " << endl;
	cin >> k.name;
	cout << "Введите пожалуйста количество цехов" << endl;
	cin >> k.kolvo_tsehov;
	cout << "Введите пожалуйста количество цехов в работе" << endl;
	cin >> k.kolvo_tsehov_v_rabote;
	cout << "Введите пожалуйста значение эффективности КС" << endl ;
	cin >> k.effektivnost;
	return k;
	

};
//pipe InputPipe()
//{
//	pipe p;
//	cout << "Type priznak:";
//	cin >> p.priznak ;
//	return p;
//}
//void printpipe(pipe p)
//{
//	cout << "Priznak:" << p.priznak
//		<< ""<<p.
//}
//int createKC(string name)
//{
//
//}
//void Editpipe(pipe p)
//{
//
//}
//void Savepipe(const pi & p)
//{
//	ofstream fout;
//	fout.open("data.txt", ios::out);
//	fout << p.name
//}
//int main()
//{
//	pipe p= InputPipe();
//	printpipe(p);
//	Editpipe(p);
//	printpipe(p);
//
//	return 0;
//}
//

