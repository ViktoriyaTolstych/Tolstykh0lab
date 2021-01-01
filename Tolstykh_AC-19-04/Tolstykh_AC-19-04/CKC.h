#pragma once
#include "lib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include"seti.h"
class CKC
{
int identificator;
	
	static int CountKC;
public:
	std::string name = " ";
	int kolvo_tsehov = 0;
	int kolvo_tsehov_v_rabote = 0;
	float effektivnost = 0;
	static int GetCountKC();
	int Getidentificator() const;

friend std::ostream& operator <<(std::ostream& out, const CKC& x);
	friend std::istream& operator >>(std::istream& in, CKC& x);
	friend std::ofstream& operator << (std::ofstream& fout, const CKC& x);
	friend std::ifstream& operator >> (std::ifstream& fin, CKC& x);

	int getID()const;
	void RedaktKC();
};



