#pragma once
#include <iostream>
#include <string>
	class Cpipe
	{
	public:
		int identificator;
		float dlina;
		float diametr;
		bool priznak = false;
		static int CountP;
		friend std::string checkRepair(const Cpipe& p);
		Cpipe();
	};


