#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;
	class Cpipe
	{	
		int identificator;
		float dlina = 0;
		float diametr = 0;
		bool priznak = false;
	public:
		static int CountP;
		string checkRepair(const Cpipe& p);
		istream& operator>> (istream& in, Cpipe& p);
		Cpipe();
	};


