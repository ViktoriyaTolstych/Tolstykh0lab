#pragma once
#include <iostream>
#include <string>
	class Cpipe
	{	
	public:
		int identificator;
		float dlina = 0;
		float diametr = 0;
		bool priznak = false;
		static int CountP;
		friend std::string checkRepair(const Cpipe& p);
		Cpipe();
	};


