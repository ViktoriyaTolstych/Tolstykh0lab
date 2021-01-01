#pragma once
#include "lib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
	class Cpipe
	{	
		static int CountP;
		int identificator;
		unsigned int inputks = 0;
		unsigned int outputks = 0;
	public:
		double dlina = 0;
		double diametr = 0;
		bool priznak = false;
		static int GetCountP();
		int Getidentificator() const;
		bool Getpriznak() const;
		void setinputks(unsigned int value);
		void setoutputks(unsigned int value);
		unsigned int getinputks();
		unsigned int getoutputks();
		void savefilepipe(std::ofstream& fout); // Сохранение информации о трубе
		void inputfilepipe(std::ifstream& fin);
		void RedaktPipeline();
		std::string checkRemont(const Cpipe& p);
		friend std::ostream& operator << (std::ostream& out, const Cpipe& x);
		friend std::istream& operator >> (std::istream& in, Cpipe& x);
		friend std::ofstream& operator << (std::ofstream& fout, const Cpipe& x);
		friend std::ifstream& operator >> (std::ifstream& fin, Cpipe& x);
		int getID()const;
	};



