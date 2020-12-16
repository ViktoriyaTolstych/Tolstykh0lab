#pragma once
#include "lib.h"
	class Cpipe
	{	
	public:
		int identificator;
		float dlina = 0;
		float diametr = 0;
		bool priznak = false;
	public:
		static int CountP;
		static std::unordered_map<int, Cpipe> 
		EditOnePipe(std::unordered_map<int, Cpipe>& pipes);
		static void EditAllPipes(std::unordered_map<int, Cpipe>& pipes);
		std::string checkRepair();
		void send();
		Cpipe();
	};


